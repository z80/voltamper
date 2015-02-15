// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_UNICODE_H
#define ICEE_UNICODE_H

#include <IceE/Config.h>
#include <IceE/Exception.h>

namespace IceUtil
{

#if defined(_MSC_VER)

//
// With Visual C++ 7.x, wchar_t is either a typedef unsigned short or a 
// native type (when /Zc:wchar_t is used).
// Since wstring is a typedef basic_string<wchar_t>, its type is also 
// different depending on whether /Zc:wchar_t is used or not.
//
// With Visual C++ 7.x, the default is typedef; with Visual C++ 8.0,
// the default is native type.
//
// Ice is always built with the default, but provides wstringToString() 
// and stringToWstring() implementations for both flavors of wstring.
//

#   if defined(_NATIVE_WCHAR_T_DEFINED)

ICE_API std::string wstringToString(const std::wstring&);

//
// Building or using with VC8
//
ICE_API std::wstring stringToWstring(const std::string&);
ICE_API std::string wstringToString(const std::basic_string<unsigned short>&);
ICE_API std::basic_string<unsigned short> stringToTypedefWstring(const std::string&);

#   else

ICE_API std::string wstringToString(const std::wstring&);

//
// Using a VC8.x build the non-default /Zc
//
ICE_API std::wstring stringToTypedefWstring(const std::string&);
inline std::wstring 
stringToWstring(const std::string& str)
{
    return stringToTypedefWstring(str);
}

#   endif

#else

ICE_API std::string wstringToString(const std::wstring&);
ICE_API std::wstring stringToWstring(const std::string&);

#endif

enum ConversionFlags 
{
    strictConversion = 0,
    lenientConversion
};

typedef unsigned char Byte;

ICE_API bool
isLegalUTF8Sequence(const Byte* source, const Byte* end);

enum ConversionError
{
    partialCharacter,
    badEncoding
};

//
// UTFConversionException is raised by wstringToString() or stringToWstring()
// to report a conversion error 
//
class ICE_API UTFConversionException : public Exception
{
public:
    
    UTFConversionException(const char*, int, ConversionError);
    virtual std::string ice_name() const;
    virtual std::string toString() const;
    virtual Exception* ice_clone() const;
    virtual void ice_throw() const;

    ConversionError conversionError() const;
private:

    const ConversionError _conversionError;
    static const char* _name;    
};

}

namespace IceUtilInternal
{

//
// Converts UTF-8 byte-sequences to and from UTF-16 or UTF-32 (with native
// endianness) depending on sizeof(wchar_t).
//
// These are thin wrappers over the UTF8/16/32 converters provided by 
// unicode.org
//
//
// TODO: provide the same support for /Zc:wchar_t as the functions above
//

enum ConversionResult
{
        conversionOK,           /* conversion successful */
        sourceExhausted,        /* partial character in source, but hit end */
        targetExhausted,        /* insuff. room in target for conversion */
        sourceIllegal           /* source sequence is illegal/malformed */
};

ICE_API ConversionResult 
convertUTFWstringToUTF8(const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
                        IceUtil::Byte*& targetStart, IceUtil::Byte* targetEnd, IceUtil::ConversionFlags flags);

ICE_API ConversionResult
convertUTF8ToUTFWstring(const IceUtil::Byte*& sourceStart, const IceUtil::Byte* sourceEnd, 
                        wchar_t*& targetStart, wchar_t* targetEnd, IceUtil::ConversionFlags flags);

ICE_API ConversionResult 
convertUTF8ToUTFWstring(const IceUtil::Byte*& sourceStart, const IceUtil::Byte* sourceEnd, 
                        std::wstring& target, IceUtil::ConversionFlags flags);

}

namespace IceUtil
{


}

#endif
