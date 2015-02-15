// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Slice/CsUtil.h>
#include <Slice/DotNetNames.h>
#include <IceUtil/Functional.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

using namespace std;
using namespace Slice;
using namespace IceUtil;
using namespace IceUtilInternal;

//
// TODO: Temporary work-around for Mono compiler bug: "global::" does not work for generic classes.
//

static string
global()
{
    return "\n#if !__MonoCS__    \nglobal::\n#endif\n";
}

static string
lookupKwd(const string& name, int baseTypes, bool mangleCasts = false)
{
    //
    // Keyword list. *Must* be kept in alphabetical order.
    //
    static const string keywordList[] =
    {
        "abstract", "as", "base", "bool", "break", "byte", "case", "catch", "char", "checked", "class", "const",
        "continue", "decimal", "default", "delegate", "do", "double", "else", "enum", "event", "explicit", "extern",
        "false", "finally", "fixed", "float", "for", "foreach", "goto", "if", "implicit", "in", "int", "interface",
        "internal", "is", "lock", "long", "namespace", "new", "null", "object", "operator", "out", "override",
        "params", "private", "protected", "public", "readonly", "ref", "return", "sbyte", "sealed", "short",
        "sizeof", "stackalloc", "static", "string", "struct", "switch", "this", "throw", "true", "try", "typeof",
        "uint", "ulong", "unchecked", "unsafe", "ushort", "using", "virtual", "void", "volatile", "while"
    };
    bool found = binary_search(&keywordList[0],
                               &keywordList[sizeof(keywordList) / sizeof(*keywordList)],
                               name,
                               Slice::CICompare());
    if(found)
    {
        return "@" + name;
    }
    if(mangleCasts && (name == "checkedCast" || name == "uncheckedCast"))
    {
        return string(DotNet::manglePrefix) + name;
    }
    return Slice::DotNet::mangleName(name, baseTypes);
}

//
// Split a scoped name into its components and return the components as a list of (unscoped) identifiers.
//
static StringList
splitScopedName(const string& scoped)
{
    assert(scoped[0] == ':');
    StringList ids;
    string::size_type next = 0;
    string::size_type pos;
    while((pos = scoped.find("::", next)) != string::npos)
    {
        pos += 2;
        if(pos != scoped.size())
        {
            string::size_type endpos = scoped.find("::", pos);
            if(endpos != string::npos)
            {
                ids.push_back(scoped.substr(pos, endpos - pos));
            }
        }
        next = pos;
    }
    if(next != scoped.size())
    {
        ids.push_back(scoped.substr(next));
    }
    else
    {
        ids.push_back("");
    }

    return ids;
}

//
// If the passed name is a scoped name, return the identical scoped name,
// but with all components that are C# keywords replaced by
// their "@"-prefixed version; otherwise, if the passed name is
// not scoped, but a C# keyword, return the "@"-prefixed name;
// otherwise, check if the name is one of the method names of baseTypes;
// if so, prefix it with _Ice_; otherwise, return the name unchanged.
//
string
Slice::CsGenerator::fixId(const string& name, int baseTypes, bool mangleCasts)
{
    if(name.empty())
    {
        return name;
    }
    if(name[0] != ':')
    {
        return lookupKwd(name, baseTypes, mangleCasts);
    }
    StringList ids = splitScopedName(name);
    StringList newIds;
    for(StringList::const_iterator i = ids.begin(); i != ids.end(); ++i)
    {
        newIds.push_back(lookupKwd(*i, baseTypes));
    }
    stringstream result;
    for(StringList::const_iterator j = newIds.begin(); j != newIds.end(); ++j)
    {
        if(j != newIds.begin())
        {
            result << '.';
        }
        result << *j;
    }
    return result.str();
}

string
Slice::CsGenerator::fixId(const ContainedPtr& cont, int baseTypes, bool mangleCasts)
{
    ContainerPtr container = cont->container();
    ContainedPtr contained = ContainedPtr::dynamicCast(container);
    if(contained && contained->hasMetaData("clr:property"))
    {
        return cont->name() + "_prop";
    }
    else
    {
        return fixId(cont->name(), baseTypes, mangleCasts);
    }
}

string
Slice::CsGenerator::typeToString(const TypePtr& type)
{
    if(!type)
    {
        return "void";
    }

    static const char* builtinTable[] =
    {
        "byte",
        "bool",
        "short",
        "int",
        "long",
        "float",
        "double",
        "string",
        "Ice.Object",
        "Ice.ObjectPrx",
        "_System.Object"
    };

    BuiltinPtr builtin = BuiltinPtr::dynamicCast(type);
    if(builtin)
    {
        return builtinTable[builtin->kind()];
    }

    ProxyPtr proxy = ProxyPtr::dynamicCast(type);
    if(proxy)
    {
        return fixId(proxy->_class()->scoped() + "Prx");
    }

    SequencePtr seq = SequencePtr::dynamicCast(type);
    if(seq)
    {
        if(seq->hasMetaData("clr:collection"))
        {
            return fixId(seq->scoped());
        }

        string prefix = "clr:generic:";
        string meta;
        if(seq->findMetaData(prefix, meta))
        {
            string type = meta.substr(prefix.size());
            if(type == "List" || type == "LinkedList" || type == "Queue" || type == "Stack")
            {
                return "_System.Collections.Generic." + type + "<" + typeToString(seq->type()) + ">";
            }
            else
            {
                return global() + type + "<" + typeToString(seq->type()) + ">";
            }
        }

        return typeToString(seq->type()) + "[]";
    }

    DictionaryPtr d = DictionaryPtr::dynamicCast(type);
    if(d)
    {
        if(d->hasMetaData("clr:collection"))
        {
            return fixId(d->scoped());
        }

        string prefix = "clr:generic:";
        string meta;
        string typeName;
        if(d->findMetaData(prefix, meta))
        {
            typeName = meta.substr(prefix.size());
        }
        else
        {
            typeName = "Dictionary";
        }
        return "_System.Collections.Generic." + typeName
                + "<" + typeToString(d->keyType()) + ", " + typeToString(d->valueType()) + ">";
    }

    ContainedPtr contained = ContainedPtr::dynamicCast(type);
    if(contained)
    {
        return fixId(contained->scoped());
    }

    return "???";
}

bool
Slice::CsGenerator::isValueType(const TypePtr& type)
{
    BuiltinPtr builtin = BuiltinPtr::dynamicCast(type);
    if(builtin)
    {
        switch(builtin->kind())
        {
            case Builtin::KindString:
            case Builtin::KindObject:
            case Builtin::KindObjectProxy:
            case Builtin::KindLocalObject:
            {
                return false;
                break;
            }
            default:
            {
                return true;
                break;
            }
        }
    }
    StructPtr s = StructPtr::dynamicCast(type);
    if(s)
    {
        if(s->hasMetaData("clr:class"))
        {
            return false;
        }
        DataMemberList dm = s->dataMembers();
        for(DataMemberList::const_iterator i = dm.begin(); i != dm.end(); ++i)
        {
            if(!isValueType((*i)->type()))
            {
                return false;
            }
        }
        return true;
    }
    if(EnumPtr::dynamicCast(type))
    {
        return true;
    }
    return false;
}

void
Slice::CsGenerator::writeMarshalUnmarshalCode(Output &out,
                                              const TypePtr& type,
                                              const string& param,
                                              bool marshal,
                                              bool streamingAPI,
                                              bool isOutParam,
                                              const string& patchParams)
{
    string stream;

    if(marshal)
    {
        stream = streamingAPI ? "outS__" : "os__";
    }
    else
    {
        stream = streamingAPI ? "inS__" : "is__";
    }

    BuiltinPtr builtin = BuiltinPtr::dynamicCast(type);
    if(builtin)
    {
        switch(builtin->kind())
        {
            case Builtin::KindByte:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeByte(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readByte()" << ';';
                }
                break;
            }
            case Builtin::KindBool:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeBool(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readBool()" << ';';
                }
                break;
            }
            case Builtin::KindShort:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeShort(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readShort()" << ';';
                }
                break;
            }
            case Builtin::KindInt:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeInt(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readInt()" << ';';
                }
                break;
            }
            case Builtin::KindLong:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeLong(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readLong()" << ';';
                }
                break;
            }
            case Builtin::KindFloat:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeFloat(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readFloat()" << ';';
                }
                break;
            }
            case Builtin::KindDouble:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeDouble(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readDouble()" << ';';
                }
                break;
            }
            case Builtin::KindString:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeString(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readString()" << ';';
                }
                break;
            }
            case Builtin::KindObject:
            {
                if(marshal)
                {
                    out << nl << stream << ".writeObject(" << param << ");";
                }
                else
                {
                    if(isOutParam)
                    {
                        out << nl << "IceInternal.ParamPatcher<Ice.Object> " << param
                            << "_PP = new IceInternal.ParamPatcher<Ice.Object>(\"::Ice::Object\");";
                        out << nl << stream << ".readObject(";
                        if(streamingAPI)
                        {
                            out << "(Ice.ReadObjectCallback)";
                        }
                        out << param << "_PP);";
                    }
                    else
                    {
                        out << nl << stream << ".readObject(";
                        if(streamingAPI)
                        {
                            out <<  "(Ice.ReadObjectCallback)";
                        }
                        out << "new Patcher__(\"::Ice::Object\", " << patchParams << "));";
                    }
                }
                break;
            }
            case Builtin::KindObjectProxy:
            {
                string typeS = typeToString(type);
                if(marshal)
                {
                    out << nl << stream << ".writeProxy(" << param << ");";
                }
                else
                {
                    out << nl << param << " = " << stream << ".readProxy()" << ';';
                }
                break;
            }
            case Builtin::KindLocalObject:
            {
                assert(false);
                break;
            }
        }
        return;
    }

    ProxyPtr prx = ProxyPtr::dynamicCast(type);
    if(prx)
    {
        string typeS = typeToString(type);
        if(marshal)
        {
            out << nl << typeS << "Helper.write";
            if(!streamingAPI)
            {
                out << "__";
            }
            out << "(" << stream << ", " << param << ");";
        }
        else
        {
            out << nl << param << " = " << typeS << "Helper.read";
            if(!streamingAPI)
            {
                out << "__";
            }
            out << "(" << stream << ");";
        }
        return;
    }

    ClassDeclPtr cl = ClassDeclPtr::dynamicCast(type);
    if(cl)
    {
        if(marshal)
        {
            out << nl << stream << ".writeObject(" << param << ");";
        }
        else
        {
            if(isOutParam)
            {
                out << nl << "IceInternal.ParamPatcher<" << typeToString(type) << ">" << param
                    << "_PP = new IceInternal.ParamPatcher<" << typeToString(type) << ">(\""
                    << cl->scoped() << "\");";
                out << nl << stream << ".readObject(";
                if(streamingAPI)
                {
                    out << "(Ice.ReadObjectCallback)";
                }
                out << param << "_PP);";
            }
            else
            {
                out << nl << stream << ".readObject(";
                if(streamingAPI)
                {
                    out << "(Ice.ReadObjectCallback)";
                }
                out << "new Patcher__(\"" << cl->scoped() << "\", " << patchParams << "));";
            }
        }
        return;
    }

    StructPtr st = StructPtr::dynamicCast(type);
    if(st)
    {
        if(marshal)
        {
            if(!isValueType(st))
            {
                out << nl << "if(" << param << " == null)";
                out << sb;
                string typeS = typeToString(st);
                out << nl << typeS << " " << "tmp__ = new " << typeS << "();";
                out << nl << "tmp__.";
                out << (streamingAPI ? "ice_write" : "write__") << "(" << stream << ");";
                out << eb;
                out << nl << "else";
                out << sb;
                out << nl << param << "." << (streamingAPI ? "ice_write" : "write__") << "(" << stream << ");";
                out << eb;
            }
            else
            {
                if(streamingAPI)
                {
                    out << nl << param << ".ice_write(" << stream << ");";
                }
                else
                {
                    out << nl << param << ".write__(" << stream << ");";
                }
            }
        }
        else
        {
            if(!isValueType(st))
            {
                out << nl << "if(" << param << " == null)";
                out << sb;
                out << nl << param << " = new " << typeToString(type) << "();";
                out << eb;
            }
            if(streamingAPI)
            {
                out << nl << param << ".ice_read(" << stream << ");";
            }
            else
            {
                out << nl << param << ".read__(" << stream << ");";
            }
        }
        return;
    }

    EnumPtr en = EnumPtr::dynamicCast(type);
    if(en)
    {
        string func;
        string cast;
        size_t sz = en->getEnumerators().size();
        if(sz <= 0x7f)
        {
            func = marshal ? "writeByte" : "readByte";
            cast = marshal ? string("(byte)") : "(" + fixId(en->scoped()) + ")";
        }
        else if(sz <= 0x7fff)
        {
            func = marshal ? "writeShort" : "readShort";
            cast = marshal ? string("(short)") : "(" + fixId(en->scoped()) + ")";
        }
        else
        {
            func = marshal ? "writeInt" : "readInt";
            cast = marshal ? string("(int)") : "(" + fixId(en->scoped()) + ")";
        }
        if(marshal)
        {
            if(streamingAPI)
            {
                out << nl << "if((int)" << param << " < 0 || (int)" << param << " >= " << sz << ")";
                out << sb;
                out << nl << "throw new Ice.MarshalException(\"enumerator out of range\");";
                out << eb;
            }
            out << nl << stream << '.' << func << '(' << cast << param;
            if(!streamingAPI)
            {
                out << ", " << sz;
            }
            out << ");";
        }
        else
        {
            out << nl << param << " = " << cast << stream << '.' << func << "(";
            if(!streamingAPI)
            {
                out << sz;
            }
            out << ")" << ';';
            if(streamingAPI)
            {
                out << nl << "if((int)" << param << " < 0 || (int)" << param << " >= " << sz << ")";
                out << sb;
                out << nl << "throw new Ice.MarshalException(\"enumerator out of range\");";
                out << eb;
            }
        }
        return;
    }

    SequencePtr seq = SequencePtr::dynamicCast(type);
    if(seq)
    {
        writeSequenceMarshalUnmarshalCode(out, seq, param, marshal, streamingAPI);
        return;
    }

    assert(ConstructedPtr::dynamicCast(type));
    string typeS;
    DictionaryPtr d = DictionaryPtr::dynamicCast(type);
    if(d)
    {
        typeS = fixId(d->scope()) + d->name();
    }
    else
    {
        typeS = typeToString(type);
    }
    if(marshal)
    {
        out << nl << typeS << "Helper.write(" << stream << ", " << param << ");";
    }
    else
    {
        out << nl << param << " = " << typeS << "Helper.read(" << stream << ')' << ';';
    }
}

void
Slice::CsGenerator::writeSequenceMarshalUnmarshalCode(Output& out,
                                                      const SequencePtr& seq,
                                                      const string& param,
                                                      bool marshal,
                                                      bool streamingAPI)
{
    string stream;
    if(marshal)
    {
        stream = streamingAPI ? "outS__" : "os__";
    }
    else
    {
        stream = streamingAPI ? "inS__" : "is__";
    }

    TypePtr type = seq->type();
    string typeS = typeToString(type);

    string genericPrefix = "clr:generic:";
    string genericType;
    string addMethod = "Add";
    bool isGeneric = seq->findMetaData(genericPrefix, genericType);
    bool isStack = false;
    bool isList = false;
    bool isLinkedList = false;
    bool isCustom = false;
    if(isGeneric)
    {
        genericType = genericType.substr(genericPrefix.size());
        if(genericType == "LinkedList")
        {
            addMethod = "AddLast";
            isLinkedList = true;
        }
        else if(genericType == "Queue")
        {
            addMethod = "Enqueue";
        }
        else if(genericType == "Stack")
        {
            addMethod = "Push";
            isStack = true;
        }
        else if(genericType == "List")
        {
            isList = true;
        }
        else
        {
            isCustom = true;
        }
    }
    bool isArray = !isGeneric && !seq->hasMetaData("clr:collection");
    string limitID = isArray ? "Length" : "Count";

    BuiltinPtr builtin = BuiltinPtr::dynamicCast(type);
    if(builtin)
    {
        switch(builtin->kind())
        {
            case Builtin::KindObject:
            case Builtin::KindObjectProxy:
            {
                if(marshal)
                {
                    out << nl << "if(" << param << " == null)";
                    out << sb;
                    out << nl << stream << ".writeSize(0);";
                    out << eb;
                    out << nl << "else";
                    out << sb;
                    out << nl << stream << ".writeSize(" << param << '.' << limitID << ");";
                    if(isGeneric && !isList)
                    {
                        if(isStack)
                        {
                            //
                            // If the collection is a stack, write in bottom-to-top order. Stacks
                            // cannot contain Ice.Object.
                            //
                            out << nl << "Ice.ObjectPrx[] " << param << "_tmp = " << param << ".ToArray();";
                            out << nl << "for(int ix__ = " << param << "_tmp.Length - 1; ix__ >= 0; --ix__)";
                            out << sb;
                            out << nl << stream << ".writeProxy(" << param << "_tmp[ix__]);";
                            out << eb;
                        }
                        else
                        {
                            out << nl << "_System.Collections.Generic.IEnumerator<" << typeS
                                << "> e__ = " << param << ".GetEnumerator();";
                            out << nl << "while(e__.MoveNext())";
                            out << sb;
                            string func = builtin->kind() == Builtin::KindObject ? "writeObject" : "writeProxy";
                            out << nl << stream << '.' << func << "(e__.Current);";
                            out << eb;
                        }
                    }
                    else
                    {
                        out << nl << "for(int ix__ = 0; ix__ < " << param << '.' << limitID << "; ++ix__)";
                        out << sb;
                        string func = builtin->kind() == Builtin::KindObject ? "writeObject" : "writeProxy";
                        out << nl << stream << '.' << func << '(' << param << "[ix__]);";
                        out << eb;
                    }
                    out << eb;
                }
                else
                {
                    out << nl << "int " << param << "_lenx = " << stream << ".readSize();";
                    if(!streamingAPI)
                    {
                        if(builtin->isVariableLength())
                        {
                            out << nl << stream << ".startSeq(" << param << "_lenx, "
                                << static_cast<unsigned>(builtin->minWireSize()) << ");";
                        }
                        else
                        {
                            out << nl << stream << ".checkFixedSeq(" << param << "_lenx, "
                                << static_cast<unsigned>(builtin->minWireSize()) << ");";
                        }
                    }
                    out << nl << param << " = new ";
                    if(builtin->kind() == Builtin::KindObject)
                    {
                        if(isArray)
                        {
                            out << "Ice.Object[" << param << "_lenx];";
                        }
                        else if(isCustom)
                        {
                            out << global() << genericType << "<Ice.Object>();";
                        }
                        else if(isGeneric)
                        {
                            out << "_System.Collections.Generic." << genericType << "<Ice.Object>(";
                            if(!isLinkedList)
                            {
                                out << param << "_lenx";
                            }
                            out << ");";
                        }
                        else
                        {
                            out << typeToString(seq) << "(" << param << "_lenx);";
                        }
                        out << nl << "for(int ix__ = 0; ix__ < " << param << "_lenx; ++ix__)";
                        out << sb;
                        out << nl << stream << ".readObject(";
                        if(streamingAPI)
                        {
                            out << "(ReadObjectCallback)";
                        }
                        string patcherName;
                        if(isCustom)
                        {
                            patcherName = "CustomSeq";
                        }
                        else if(isList)
                        {
                            patcherName = "List";
                        }
                        else if(isArray)
                        {
                            patcherName = "Array";
                        }
                        else
                        {
                            patcherName = "Sequence";
                        }
                        out << "new IceInternal." << patcherName << "Patcher<Ice.Object>(\"::Ice::Object\", "
                            << param << ", ix__));";
                    }
                    else
                    {
                        if(isArray)
                        {
                            out << "Ice.ObjectPrx[" << param << "_lenx];";
                        }
                        else if(isGeneric)
                        {
                            out << "_System.Collections.Generic." << genericType << "<Ice.ObjectPrx>(";
                            if(!isLinkedList)
                            {
                                out << param << "_lenx";
                            }
                            out << ");";
                        }
                        else
                        {
                            out << typeToString(seq) << "(" << param << "_lenx);";
                        }
                        out << nl << "for(int ix__ = 0; ix__ < " << param << "_lenx; ++ix__)";
                        out << sb;
                        if(isArray)
                        {
                            out << nl << param << "[ix__] = " << stream << ".readProxy();";
                        }
                        else
                        {
                            out << nl << "Ice.ObjectPrx val__ = new Ice.ObjectPrxHelperBase();";
                            out << nl << "val__ = " << stream << ".readProxy();";
                            out << nl << param << "." << addMethod << "(val__);";
                        }
                    }
                    if(!streamingAPI && builtin->isVariableLength())
                    {
                        out << nl << stream << ".checkSeq();";
                        out << nl << stream << ".endElement();";
                    }
                    out << eb;
                    if(!streamingAPI && builtin->isVariableLength())
                    {
                        out << nl << stream << ".endSeq(" << param << "_lenx);";
                    }
                }
                break;
            }
            default:
            {
                typeS[0] = toupper(static_cast<unsigned char>(typeS[0]));
                if(marshal)
                {
                    out << nl << stream << ".write" << typeS << "Seq(";
                    if(isArray)
                    {
                        out << param << ");";
                    }
                    else if(!isGeneric)
                    {
                        out << param << " == null ? null : " << param << ".ToArray());";
                    }
                    else
                    {
                        out << param << " == null ? 0 : " << param << ".Count, " << param << ");";
                    }
                }
                else
                {
                    if(isArray)
                    {
                        out << nl << param << " = " << stream << ".read" << typeS << "Seq();";
                    }
                    else if(isCustom)
                    {
                        out << sb;
                        out << nl << param << " = new " << global() << genericType << "<"
                            << typeToString(type) << ">();";
                        out << nl << "int szx__ = " << stream << ".readSize();";
                        out << nl << "for(int ix__ = 0; ix__ < szx__; ++ix__)";
                        out << sb;
                        out << nl << param << ".Add(" << stream << ".read" << typeS << "());";
                        out << eb;
                        out << eb;
                    }
                    else if(isGeneric)
                    {
                        out << nl << stream << ".read" << typeS << "Seq(out " << param << ");";
                    }
                    else
                    {
                        out << nl << param << " = new " << fixId(seq->scoped())
                            << '(' << stream << ".read" << typeS << "Seq());";
                    }
                }
                break;
            }
        }
        return;
    }

    ClassDeclPtr cl = ClassDeclPtr::dynamicCast(type);
    if(cl)
    {
        if(marshal)
        {
            out << nl << "if(" << param << " == null)";
            out << sb;
            out << nl << stream << ".writeSize(0);";
            out << eb;
            out << nl << "else";
            out << sb;
            out << nl << stream << ".writeSize(" << param << '.' << limitID << ");";
            if(isGeneric && !isList)
            {
                //
                // Stacks cannot contain class instances, so there is no need to marshal a
                // stack bottom-up here.
                //
                out << nl << "_System.Collections.Generic.IEnumerator<" << typeS
                    << "> e__ = " << param << ".GetEnumerator();";
                out << nl << "while(e__.MoveNext())";
                out << sb;
                out << nl << stream << ".writeObject(e__.Current);";
                out << eb;
            }
            else
            {
                out << nl << "for(int ix__ = 0; ix__ < " << param << '.' << limitID << "; ++ix__)";
                out << sb;
                out << nl << stream << ".writeObject(" << param << "[ix__]);";
                out << eb;
            }
            out << eb;
        }
        else
        {
            out << sb;
            out << nl << "int szx__ = " << stream << ".readSize();";
            if(!streamingAPI)
            {
                if(type->isVariableLength())
                {
                    out << nl << stream << ".startSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
                }
                else
                {
                    out << nl << stream << ".checkFixedSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
                }
            }
            out << nl << param << " = new ";
            if(isArray)
            {
                out << toArrayAlloc(typeS + "[]", "szx__");
            }
            else if(isCustom)
            {
                out << global() << genericType << "<" << typeS << ">()";
            }
            else if(isGeneric)
            {
                out << "_System.Collections.Generic." << genericType << "<" << typeS << ">(";
                if(!isLinkedList)
                {
                    out << "szx__";
                }
                out << ")";
            }
            else
            {
                out << fixId(seq->scoped()) << "(szx__)";
            }
            out << ';';
            out << nl << "for(int ix__ = 0; ix__ < szx__; ++ix__)";
            out << sb;

            string patcherName;
            if(isCustom)
            {
                patcherName = "CustomSeq";
            }
            else if(isList)
            {
                patcherName = "List";
            }
            else if(isArray)
            {
                patcherName = "Array";
            }
            else
            {
                patcherName = "Sequence";
            }
            string scoped = ContainedPtr::dynamicCast(type)->scoped();
            out << nl << "IceInternal." << patcherName << "Patcher<" << typeS << "> spx = new IceInternal."
                << patcherName << "Patcher<" << typeS << ">(\"" << scoped << "\", " << param << ", ix__);";
            out << nl << stream << ".readObject(";
            if(streamingAPI)
            {
                out << "(Ice.ReadObjectCallback)";
            }
            out << "spx);";
            if(!streamingAPI && type->isVariableLength())
            {
                out << nl << stream << ".checkSeq();";
                out << nl << stream << ".endElement();";
            }
            out << eb;
            if(!streamingAPI && type->isVariableLength())
            {
                out << nl << stream << ".endSeq(szx__);";
            }
            out << eb;
        }
        return;
    }

    StructPtr st = StructPtr::dynamicCast(type);
    if(st)
    {
        if(marshal)
        {
            out << nl << "if(" << param << " == null)";
            out << sb;
            out << nl << stream << ".writeSize(0);";
            out << eb;
            out << nl << "else";
            out << sb;
            out << nl << stream << ".writeSize(" << param << '.' << limitID << ");";
            if(isGeneric && !isList)
            {
                //
                // Stacks are marshaled bottom-up.
                //
                if(isStack)
                {
                    out << nl << typeS << "[] " << param << "_tmp = " << param << ".ToArray();";
                    out << nl << "for(int ix__ = " << param << "_tmp.Length - 1; ix__ >= 0; --ix__)";
                }
                else
                {
                    out << nl << "_System.Collections.Generic.IEnumerator<" << typeS
                        << "> e__ = " << param << ".GetEnumerator();";
                    out << nl << "while(e__.MoveNext())";
                }
            }
            else
            {
                out << nl << "for(int ix__ = 0; ix__ < " << param << '.' << limitID << "; ++ix__)";
            }
            out << sb;
            string call;
            if(isGeneric && !isList && !isStack)
            {
                if(isValueType(type))
                {
                    call = "e__.Current";
                }
                else
                {
                    call = "(e__.Current == null ? new ";
                    call += typeS + "() : e__.Current)";
                }
            }
            else
            {
                if(isValueType(type))
                {
                    call = param;
                    if(isStack)
                    {
                        call += "_tmp";
                    }
                }
                else
                {
                    call = "(";
                    call += param;
                    if(isStack)
                    {
                        call += "_tmp";
                    }
                    call += " == null ? new " + typeS + "() : " + param;
                    if(isStack)
                    {
                        call += "_tmp";
                    }
                }
                call += "[ix__]";
                if(!isValueType(type))
                {
                    call += ")";
                }
            }
            call += ".";
            call += streamingAPI ? "ice_write" : "write__";
            call += "(" + stream + ");";
            out << nl << call;
            out << eb;
            out << eb;
        }
        else
        {
            out << sb;
            out << nl << "int szx__ = " << stream << ".readSize();";
            if(!streamingAPI)
            {
                if(type->isVariableLength())
                {
                    out << nl << stream << ".startSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
                }
                else
                {
                    out << nl << stream << ".checkFixedSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
                }
            }
            out << nl << param << " = new ";
            if(isArray)
            {
                out << toArrayAlloc(typeS + "[]", "szx__") << ";";
            }
            else if(isCustom)
            {
                out << global() << genericType << "<" << typeS << ">();";
            }
            else if(isGeneric)
            {
                out << "_System.Collections.Generic." << genericType << "<" << typeS << ">(";
                if(!isLinkedList)
                {
                    out << "szx__";
                }
                out << ");";
            }
            else
            {
                out << fixId(seq->scoped()) << "(szx__);";
            }
            out << nl << "for(int ix__ = 0; ix__ < szx__; ++ix__)";
            out << sb;
            if(isArray)
            {
                if(!isValueType(st))
                {
                    out << nl << param << "[ix__] = new " << typeS << "();";
                }
                if(streamingAPI)
                {
                    out << nl << param << "[ix__].ice_read(" << stream << ");";
                }
                else
                {
                    out << nl << param << "[ix__].read__(" << stream << ");";
                }
            }
            else
            {
                out << nl << typeS << " val__ = new " << typeS << "();";
                if(streamingAPI)
                {
                    out << nl << "val__.ice_read(" << stream << ");";
                }
                else
                {
                    out << nl << "val__.read__(" << stream << ");";
                }
                out << nl << param << "." << addMethod << "(val__);";
            }
            if(!streamingAPI && type->isVariableLength())
            {
                out << nl << stream << ".checkSeq();";
                out << nl << stream << ".endElement();";
            }
            out << eb;
            if(!streamingAPI && type->isVariableLength())
            {
                out << nl << stream << ".endSeq(szx__);";
            }
            out << eb;
        }
        return;
    }

    EnumPtr en = EnumPtr::dynamicCast(type);
    if(en)
    {
        size_t sz = en->getEnumerators().size();
        string dataType;
        string func = marshal ? "write" : "read";
        if(sz <= 0x7f)
        {
            func += "Byte";
            dataType = "byte";
        }
        else if(sz <= 0x7fff)
        {
            func += "Short";
            dataType = "short";
        }
        else
        {
            func += "Int";
            dataType = "int";
        }
        if(marshal)
        {
            out << nl << "if(" << param << " == null)";
            out << sb;
            out << nl << stream << ".writeSize(0);";
            out << eb;
            out << nl << "else";
            out << sb;
            out << nl << stream << ".writeSize(" << param << '.'<< limitID << ");";
            if(isGeneric && !isList)
            {
                //
                // Stacks are marshaled bottom-up.
                //
                if(isStack)
                {
                    out << nl << typeS << "[] " << param << "_tmp = " << param << ".ToArray();";
                    out << nl << "for(int ix__ = " << param << "_tmp.Length - 1; ix__ >= 0; --ix__)";
                    out << sb;
                    out << nl << stream << '.' << func << "((" << dataType << ")" << param << "_tmp[ix__]";
                    if(!streamingAPI)
                    {
                        out << ", " << sz;
                    }
                    out << ");";
                    out << eb;
                }
                else
                {
                    out << nl << "_System.Collections.Generic.IEnumerator<" << typeS
                        << "> e__ = " << param << ".GetEnumerator();";
                    out << nl << "while(e__.MoveNext())";
                    out << sb;
                    out << nl << stream << '.' << func << "((" << dataType << ")e__.Current";
                    if(!streamingAPI)
                    {
                        out << ", " << sz;
                    }
                    out << ");";
                    out << eb;
                }
            }
            else
            {
                out << nl << "for(int ix__ = 0; ix__ < " << param << '.' << limitID << "; ++ix__)";
                out << sb;
                out << nl << stream << '.' << func << "((" << dataType << ")" << param << "[ix__]";
                if(!streamingAPI)
                {
                    out << ", " << sz;
                }
                out << ");";
                out << eb;
            }
            out << eb;
        }
        else
        {
            out << sb;
            out << nl << "int szx__ = " << stream << ".readSize();";
            if(!streamingAPI)
            {
                out << nl << stream << ".checkFixedSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
            }
            out << nl << param << " = new ";
            if(isArray)
            {
                out << toArrayAlloc(typeS + "[]", "szx__") << ";";
            }
            else if(isCustom)
            {
                out << global() << genericType << "<" << typeS << ">();";
            }
            else if(isGeneric)
            {
                out << "_System.Collections.Generic." << genericType << "<" << typeS << ">(";
                if(!isLinkedList)
                {
                    out << "szx__";
                }
                out << ");";
            }
            else
            {
                out << fixId(seq->scoped()) << "(szx__);";
            }
            out << nl << "for(int ix__ = 0; ix__ < szx__; ++ix__)";
            out << sb;
            if(isArray)
            {
                out << nl << param << "[ix__] = (" << typeS << ')' << stream << "." << func << "(";
                if(!streamingAPI)
                {
                    out << sz;
                }
                out << ");";
            }
            else
            {
                out << nl << param << "." << addMethod << "((" << typeS << ')' << stream << "." << func << "(";
                if(!streamingAPI)
                {
                    out << sz;
                }
                out << "));";
            }
            out << eb;
            out << eb;
        }
        return;
    }

    string helperName;
    if(ProxyPtr::dynamicCast(type))
    {
        helperName = fixId(ProxyPtr::dynamicCast(type)->_class()->scoped() + "PrxHelper");
    }
    else
    {
        helperName = fixId(ContainedPtr::dynamicCast(type)->scoped() + "Helper");
    }

    string func;
    if(marshal)
    {
        func = "write";
        if(!streamingAPI && ProxyPtr::dynamicCast(type))
        {
           func += "__";
        }
        out << nl << "if(" << param << " == null)";
        out << sb;
        out << nl << stream << ".writeSize(0);";
        out << eb;
        out << nl << "else";
        out << sb;
        out << nl << stream << ".writeSize(" << param << '.' << limitID << ");";
        if(isGeneric && !isList)
        {
            //
            // Stacks are marshaled bottom-up.
            //
            if(isStack)
            {
                out << nl << typeS << "[] " << param << "_tmp = " << param << ".ToArray();";
                out << nl << "for(int ix__ = " << param << "_tmp.Length - 1; ix__ >= 0; --ix__)";
                out << sb;
                out << nl << helperName << '.' << func << '(' << stream << ", " << param << "_tmp[ix__]);";
                out << eb;
            }
            else
            {
                out << nl << "_System.Collections.Generic.IEnumerator<" << typeS
                    << "> e__ = " << param << ".GetEnumerator();";
                out << nl << "while(e__.MoveNext())";
                out << sb;
                out << nl << helperName << '.' << func << '(' << stream << ", e__.Current);";
                out << eb;
            }
        }
        else
        {
            out << nl << "for(int ix__ = 0; ix__ < " << param << '.' << limitID << "; ++ix__)";
            out << sb;
            out << nl << helperName << '.' << func << '(' << stream << ", " << param << "[ix__]);";
            out << eb;
        }
        out << eb;
    }
    else
    {
        func = "read";
        if(!streamingAPI && ProxyPtr::dynamicCast(type))
        {
           func += "__";
        }
        out << sb;
        out << nl << "int szx__ = " << stream << ".readSize();";
        if(!streamingAPI)
        {
            if(type->isVariableLength())
            {
                out << nl << stream << ".startSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
            }
            else
            {
                out << nl << stream << ".checkFixedSeq(szx__, " << static_cast<unsigned>(type->minWireSize()) << ");";
            }
        }
        out << nl << param << " = new ";
        if(isArray)
        {
            out << toArrayAlloc(typeS + "[]", "szx__") << ";";
        }
        else if(isCustom)
        {
            out << global() << genericType << "<" << typeS << ">();";
        }
        else if(isGeneric)
        {
            out << "_System.Collections.Generic." << genericType << "<" << typeS << ">();";
        }
        else
        {
            out << fixId(seq->scoped()) << "(szx__);";
        }
        out << nl << "for(int ix__ = 0; ix__ < szx__; ++ix__)";
        out << sb;
        if(isArray)
        {
            out << nl << param << "[ix__] = " << helperName << '.' << func << '(' << stream << ");";
        }
        else
        {
            out << nl << param << "." << addMethod << "(" << helperName << '.' << func << '(' << stream << "));";
        }
        if(!streamingAPI && type->isVariableLength())
        {
            if(!SequencePtr::dynamicCast(type))
            {
                out << nl << stream << ".checkSeq();";
            }
            out << nl << stream << ".endElement();";
        }
        out << eb;
        if(!streamingAPI && type->isVariableLength())
        {
            out << nl << stream << ".endSeq(szx__);";
        }
        out << eb;
    }

    return;
}

string
Slice::CsGenerator::toArrayAlloc(const string& decl, const string& sz)
{
    int count = 0;
    string::size_type pos = decl.size();
    while(pos > 1 && decl.substr(pos - 2, 2) == "[]")
    {
        ++count;
        pos -= 2;
    }
    assert(count > 0);

    ostringstream o;
    o << decl.substr(0, pos) << '[' << sz << ']' << decl.substr(pos + 2);
    return o.str();
}

void
Slice::CsGenerator::validateMetaData(const UnitPtr& u)
{
    MetaDataVisitor visitor;
    u->visit(&visitor, true);
}

Slice::CsGenerator::MetaDataVisitor::MetaDataVisitor()
    : _globalMetaDataDone(false)
{
}

bool
Slice::CsGenerator::MetaDataVisitor::visitModuleStart(const ModulePtr& p)
{
    if(!_globalMetaDataDone)
    {
        //
        // Validate global metadata.
        //
        DefinitionContextPtr dc = p->definitionContext();
        assert(dc);
        StringList globalMetaData = dc->getMetaData();
        string file = dc->filename();
        static const string prefix = "cs:";
        for(StringList::const_iterator q = globalMetaData.begin(); q != globalMetaData.end(); ++q)
        {
            string s = *q;
            if(_history.count(s) == 0)
            {
                if(s.find(prefix) == 0)
                {
                    static const string attributePrefix = "cs:attribute:";
                    if(s.find(attributePrefix) != 0 || s.size() == attributePrefix.size())
                    {
                        cout << file << ": warning: ignoring invalid global metadata `" << s << "'" << endl;
                    }
                }
                _history.insert(s);
            }
        }
        _globalMetaDataDone = true;
    }
    validate(p);
    return true;
}

void
Slice::CsGenerator::MetaDataVisitor::visitModuleEnd(const ModulePtr&)
{
}

void
Slice::CsGenerator::MetaDataVisitor::visitClassDecl(const ClassDeclPtr& p)
{
    validate(p);
}

bool
Slice::CsGenerator::MetaDataVisitor::visitClassDefStart(const ClassDefPtr& p)
{
    validate(p);
    return true;
}

void
Slice::CsGenerator::MetaDataVisitor::visitClassDefEnd(const ClassDefPtr&)
{
}

bool
Slice::CsGenerator::MetaDataVisitor::visitExceptionStart(const ExceptionPtr& p)
{
    validate(p);
    return true;
}

void
Slice::CsGenerator::MetaDataVisitor::visitExceptionEnd(const ExceptionPtr&)
{
}

bool
Slice::CsGenerator::MetaDataVisitor::visitStructStart(const StructPtr& p)
{
    validate(p);
    return true;
}

void
Slice::CsGenerator::MetaDataVisitor::visitStructEnd(const StructPtr&)
{
}

void
Slice::CsGenerator::MetaDataVisitor::visitOperation(const OperationPtr& p)
{
    if(p->hasMetaData("UserException"))
    {
        ClassDefPtr cl = ClassDefPtr::dynamicCast(p->container());
        if(!cl->isLocal())
        {
            cout << p->definitionContext()->filename() << ":" << p->line()
                 << ": warning: metdata directive `UserException' applies only to local operations "
                 << "but enclosing " << (cl->isInterface() ? "interface" : "class") << "`" << cl->name()
                 << "' is not local" << endl;
        }
    }
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitParamDecl(const ParamDeclPtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitDataMember(const DataMemberPtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitSequence(const SequencePtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitDictionary(const DictionaryPtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitEnum(const EnumPtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::visitConst(const ConstPtr& p)
{
    validate(p);
}

void
Slice::CsGenerator::MetaDataVisitor::validate(const ContainedPtr& cont)
{
    const string msg = "ignoring invalid metadata";

    DefinitionContextPtr dc = cont->definitionContext();
    assert(dc);
    string file = dc->filename();

    StringList localMetaData = cont->getMetaData();

    StringList::const_iterator p;

    for(p = localMetaData.begin(); p != localMetaData.end(); ++p)
    {
        string s = *p;

        string prefix = "clr:";
        if(_history.count(s) == 0)
        {
            if(s.find(prefix) == 0)
            {
                SequencePtr seq = SequencePtr::dynamicCast(cont);
                if(seq)
                {
                    if(s.substr(prefix.size()) == "collection")
                    {
                        continue;
                    }
                    if(s.substr(prefix.size(), 8) == "generic:")
                    {
                        string type = s.substr(prefix.size() + 8);
                        if(type == "LinkedList" || type == "Queue" || type == "Stack")
                        {
                            ClassDeclPtr cd = ClassDeclPtr::dynamicCast(seq->type());
                            BuiltinPtr builtin = BuiltinPtr::dynamicCast(seq->type());
                            if(!cd && !(builtin && builtin->kind() == Builtin::KindObject))
                            {
                                continue;
                            }
                        }
                        else if(!type.empty())
                        {
                            continue; // Custom type or List<T>
                        }
                    }
                }
                else if(StructPtr::dynamicCast(cont))
                {
                    if(s.substr(prefix.size()) == "class")
                    {
                        continue;
                    }
                    if(s.substr(prefix.size()) == "property")
                    {
                        continue;
                    }
                }
                else if(ClassDefPtr::dynamicCast(cont))
                {
                    if(s.substr(prefix.size()) == "property")
                    {
                        continue;
                    }
                }
                else if(DictionaryPtr::dynamicCast(cont))
                {
                    if(s.substr(prefix.size()) == "collection")
                    {
                        continue;
                    }
                    if(s.substr(prefix.size(), 8) == "generic:")
                    {
                        string type = s.substr(prefix.size() + 8);
                        if(type == "SortedDictionary" ||  type == "SortedList")
                        {
                            continue;
                        }
                    }
                }
                cout << file << ":" << cont->line() << ": warning: " << msg << " `" << s << "'" << endl;
            }
            _history.insert(s);
        }

        prefix = "cs:";
        if(_history.count(s) == 0)
        {
            if(s.find(prefix) == 0)
            {
                if(s.substr(prefix.size()) == "attribute:")
                {
                    continue;
                }
                cout << file << ":" << cont->line() << ": warning: " << msg << " `" << s << "'" << endl;
            }
            _history.insert(s);
        }
    }
}
