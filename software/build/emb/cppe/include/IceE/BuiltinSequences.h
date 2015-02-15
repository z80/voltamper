// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `BuiltinSequences.ice'

#ifndef __IceE_BuiltinSequences_h__
#define __IceE_BuiltinSequences_h__

#include <IceE/ProxyF.h>
#include <IceE/ObjectF.h>
#include <IceE/Exception.h>
#include <IceE/ScopedArray.h>
#include <IceE/Proxy.h>
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

typedef ::std::vector<bool> BoolSeq;

typedef ::std::vector< ::Ice::Byte> ByteSeq;

typedef ::std::vector< ::Ice::Short> ShortSeq;

typedef ::std::vector< ::Ice::Int> IntSeq;

typedef ::std::vector< ::Ice::Long> LongSeq;

typedef ::std::vector< ::Ice::Float> FloatSeq;

typedef ::std::vector< ::Ice::Double> DoubleSeq;

typedef ::std::vector< ::std::string> StringSeq;

typedef ::std::vector< ::Ice::ObjectPrx> ObjectProxySeq;
ICE_API void __writeObjectProxySeq(::IceInternal::BasicStream*, const ::Ice::ObjectPrx*, const ::Ice::ObjectPrx*);
ICE_API void __readObjectProxySeq(::IceInternal::BasicStream*, ObjectProxySeq&);

}

#endif
