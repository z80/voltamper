// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `Identity.ice'

#ifndef __IceE_Identity_h__
#define __IceE_Identity_h__

#include <IceE/ProxyF.h>
#include <IceE/ObjectF.h>
#include <IceE/Exception.h>
#include <IceE/ScopedArray.h>
#include <IceE/UndefSysMacros.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

#ifndef ICE_API
#   ifdef ICE_API_EXPORTS
#       define ICE_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Ice
{

struct Identity
{
    ::std::string name;
    ::std::string category;

    ICE_API bool operator==(const Identity&) const;
    ICE_API bool operator<(const Identity&) const;
    bool operator!=(const Identity& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const Identity& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Identity& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Identity& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_API void __write(::IceInternal::BasicStream*) const;
    ICE_API void __read(::IceInternal::BasicStream*);
};

}

#endif
