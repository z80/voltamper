// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <Slice/Preprocessor.h>
#include <Slice/Util.h>
#include <IceUtil/StringUtil.h>
#include <IceUtil/FileUtil.h>
#include <IceUtil/UUID.h>
#include <IceUtil/Unicode.h>
#include <algorithm>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

#ifndef _WIN32
#   include <sys/wait.h>
#endif

using namespace std;
using namespace Slice;

//
// mcpp defines
//
namespace Slice
{

enum Outdest
{
    Out=0, Err=1, Dbg=2, Num_Outdest=3
}; 

};

extern "C" int   mcpp_lib_main(int argc, char** argv);
extern "C" void  mcpp_use_mem_buffers(int tf);
extern "C" char* mcpp_get_mem_buffer(Outdest od);

Slice::Preprocessor::Preprocessor(const string& path, const string& fileName, const vector<string>& args) :
    _path(path),
    _fileName(fileName),
    _args(args),
    _cppHandle(0)
{
}

Slice::Preprocessor::~Preprocessor()
{
    close();
}

string
Slice::Preprocessor::getBaseName()
{
    string base(_fileName);
    string suffix;
    string::size_type pos = base.rfind('.');
    if(pos != string::npos)
    {
        base.erase(pos);
    }
    return base;
}

string
Slice::Preprocessor::addQuotes(const string& arg)
{
    //
    // Add quotes around the given argument to ensure that arguments
    // with spaces will be preserved as a single argument. We also
    // escape the "\" character to ensure that we don't end up with a
    // \" at the end of the string.
    //
    return "\"" + IceUtilInternal::escapeString(arg, "\\") + "\"";
}

string
Slice::Preprocessor::normalizeIncludePath(const string& path)
{
    string result = path;

    replace(result.begin(), result.end(), '\\', '/');

    string::size_type pos;
    while((pos = result.find("//")) != string::npos)
    {
        result.replace(pos, 2, "/");
    }

    if(result == "/" || (result.size() == 3 && isalpha(static_cast<unsigned char>(result[0])) && result[1] == ':' &&
       result[2] == '/'))
    {
	return result;
    }
    
    if(result.size() > 1 && result[result.size() - 1] == '/')
    {
	result.erase(result.size() - 1);
    }

    return result;
}

FILE*
Slice::Preprocessor::preprocess(bool keepComments)
{
    if(!checkInputFile())
    {
        return 0;
    }

    //
    // Build arguments list.
    //
    vector<string> args = _args;
    if(keepComments)
    {
        args.push_back("-C");
    }
    args.push_back(_fileName);

    const char** argv = new const char*[args.size() + 1];
    argv[0] = "mcpp";
    for(unsigned int i = 0; i < args.size(); ++i)
    {
        argv[i + 1] = args[i].c_str();
    }

    //
    // Call mcpp using memory buffer.
    //
    mcpp_use_mem_buffers(1);
    int status = mcpp_lib_main(static_cast<int>(args.size()) + 1, const_cast<char**>(argv));
    delete[] argv;

    //
    // Print errors to stderr.
    //
    char* err = mcpp_get_mem_buffer(Err);
    if(err)
    {
        ::fputs(err, stderr);
    }

    if(status == 0)
    {
        //
        // Write output to temporary file.
        //
        char* buf = mcpp_get_mem_buffer(Out);

        //
        // First try to open temporay file in tmp directory.
        //
#ifdef _WIN32
        wchar_t* name = _wtempnam(NULL, L".preprocess");
        if(name)
        {
            _cppFile = wstring(name);
            free(name);
            _cppHandle = ::_wfopen(_cppFile.c_str(), L"w+");
        }
#else
        _cppHandle = tmpfile();
#endif
        
        //
        // If that fails try to open file in current directory.
        //
        if(_cppHandle == 0)
        {
#ifdef _WIN32
            _cppFile = L".preprocess." + IceUtil::stringToWstring(IceUtil::generateUUID());
            _cppHandle = ::_wfopen(_cppFile.c_str(), L"w+");
#else
            _cppFile = ".preprocess." + IceUtil::generateUUID();
            _cppHandle = ::fopen(_cppFile.c_str(), "w+");
#endif
        }

        if(_cppHandle != 0)
        {
            if(buf)
            {
                ::fwrite(buf, strlen(buf), 1, _cppHandle);
            }
            ::rewind(_cppHandle);
        }
        else
        {
            cerr << "Could not open temporary file: ";
#ifdef _WIN32
            cerr << IceUtil::wstringToString(_cppFile);
#else
            cerr << _cppFile;
#endif
            cerr << endl;
        }
    }

    //
    // Calling this again causes the memory buffers to be freed.
    //
    mcpp_use_mem_buffers(1);

    return _cppHandle;
}

void
Slice::Preprocessor::printMakefileDependencies(Language lang, const vector<string>& includePaths)
{
    if(!checkInputFile())
    {
        return;
    }

    //
    // Build arguments list.
    //
    vector<string> args = _args;
    args.push_back("-M");
    args.push_back(_fileName);

    const char** argv = new const char*[args.size() + 1];
    for(unsigned int i = 0; i < args.size(); ++i)
    {
        argv[i + 1] = args[i].c_str();
    }
    
    //
    // Call mcpp using memory buffer.
    //
    mcpp_use_mem_buffers(1);
    int status = mcpp_lib_main(static_cast<int>(args.size() + 1), const_cast<char**>(argv));
    delete[] argv;

    //
    // Print errors to stderr.
    //
    char* err = mcpp_get_mem_buffer(Err);
    if(err)
    {
        ::fputs(err, stderr);
    }

    if(status != 0)
    {
        //
        // Calling this again causes the memory buffers to be freed.
        //
        mcpp_use_mem_buffers(1);
        return;
    }

    //
    // Get mcpp output.
    //
    string unprocessed;
    char* buf = mcpp_get_mem_buffer(Out);
    if(buf)
    {
        unprocessed = string(buf);
    }

    //
    // Calling this again causes the memory buffers to be freed.
    //
    mcpp_use_mem_buffers(1);

    //
    // We now need to massage the result to get the desired output.
    // First make it a single line.
    //
    string::size_type pos;
    while((pos = unprocessed.find("\\\n")) != string::npos)
    {
        unprocessed.replace(pos, 2, "");
    }

    //
    // Get the main output file name.
    //
#ifdef _WIN32
     string suffix = ".obj:";
#else
     string suffix = ".o:";
#endif
    pos = unprocessed.find(suffix) + suffix.size();
    string result = unprocessed.substr(0, pos);

    vector<string> fullIncludePaths;
    vector<string>::const_iterator p;
    for(p = includePaths.begin(); p != includePaths.end(); ++p)
    {
        fullIncludePaths.push_back(fullPath(*p));
    }
    string absoluteFileName = fullPath(_fileName);

    //
    // Process each dependency.
    //
    string::size_type end;
    while((end = unprocessed.find(".ice", pos)) != string::npos)
    {
        end += 4;
        string file = IceUtilInternal::trim(unprocessed.substr(pos, end - pos));
        if(IceUtilInternal::isAbsolutePath(file))
        {
            if(file == absoluteFileName)
            {
                file = _fileName;
            }
            else
            {
                //
                // Transform back full paths generated by mcpp to paths relative to the specified
                // include paths.
                //
                string newFile = file;
                for(vector<string>::const_iterator p = fullIncludePaths.begin(); p != fullIncludePaths.end(); ++p)
                {
                    if(file.compare(0, p->length(), *p) == 0)
                    {
                        string s = includePaths[p - fullIncludePaths.begin()] + file.substr(p->length());
                        if(IceUtilInternal::isAbsolutePath(newFile) || s.size() < newFile.size())
                        {
                            newFile = s;
                        }
                    }
                }
                file = newFile;
            }
        }

        //
        // Escape spaces in the file name.
        //
        string::size_type space = 0;
        while((space = file.find(" ", space)) != string::npos)
        {
            file.replace(space, 1, "\\ ");
            space += 2;
        }

        //
        // Add to result
        //
        result += " \\\n " + file;
        pos = end;
    }
    result += "\n";

    /*
     * icecpp emits dependencies in any of the following formats, depending on the
     * length of the filenames:
     *
     * x.o[bj]: /path/x.ice /path/y.ice
     *
     * x.o[bj]: /path/x.ice \ 
     *  /path/y.ice
     *
     * x.o[bj]: /path/x.ice /path/y.ice \ 
     *  /path/z.ice
     *
     * x.o[bj]: \ 
     *  /path/x.ice
     *
     * x.o[bj]: \ 
     *  /path/x.ice \ 
     *  /path/y.ice
     *
     * Spaces embedded within filenames are escaped with a backslash. Note that
     * Windows filenames may contain colons.
     *
     */
    switch(lang)
    {
        case CPlusPlus:
        {
            //
            // Change .o[bj] suffix to .cpp suffix.
            //
            string::size_type pos;
            while((pos = result.find(suffix)) != string::npos)
            {
                result.replace(pos, suffix.size() - 1, ".cpp");
            }
            break;
        }
        case Java:
        {
            //
            // We want to shift the files left one position, so that
            // "x.cpp: x.ice y.ice" becomes "x.ice: y.ice".
            //

            //
            // Remove the first file.
            //
            string::size_type start = result.find(suffix);
            assert(start != string::npos);
            start = result.find_first_not_of(" \t\r\n\\", start + suffix.size()); // Skip to beginning of next file.
            assert(start != string::npos);
            result.erase(0, start);

            //
            // Find end of next file.
            //
            string::size_type pos = 0;
            while((pos = result.find_first_of(" :\t\r\n\\", pos + 1)) != string::npos)
            {
                if(result[pos] == ':')
                {
                    result.insert(pos, 1, '\\'); // Escape colons.
                    ++pos;
                }
                else if(result[pos] == '\\') // Ignore escaped characters.
                {
                    ++pos;
                }
                else
                {
                    break;
                }
            }

            if(pos == string::npos)
            {
                result.append(":");
            }
            else
            {
                result.insert(pos, 1, ':');
            }
            break;
        }
        case CSharp:
        {
            //
            // Change .o[bj] suffix to .cs suffix.
            //
            string::size_type pos;
            while((pos = result.find(suffix)) != string::npos)
            {
                result.replace(pos, suffix.size() - 1, ".cs");
            }
            break;
        }
        default:
        {
            abort();
            break;
        }
    }

    //
    // Output result
    //
    fputs(result.c_str(), stdout);
}

bool
Slice::Preprocessor::close()
{
    if(_cppHandle != 0)
    {
        int status = fclose(_cppHandle);
        _cppHandle = 0;

        if(_cppFile.size() != 0)
        {
#ifdef _WIN32
            _wunlink(_cppFile.c_str());
#else
            unlink(_cppFile.c_str());
#endif
        }

        if(status != 0)
        {
            return false;
        }
    }
    
    return true;
}

bool
Slice::Preprocessor::checkInputFile()
{
    string base(_fileName);
    string suffix;
    string::size_type pos = base.rfind('.');
    if(pos != string::npos)
    {
        suffix = IceUtilInternal::toLower(base.substr(pos));
    }
    if(suffix != ".ice")
    {
        cerr << _path << ": input files must end with `.ice'" << endl;
        return false;
    }
    
    ifstream test(_fileName.c_str());
    if(!test)
    {
        cerr << _path << ": can't open `" << _fileName << "' for reading" << endl;
        return false;
    }
    test.close();

    return true;
}
