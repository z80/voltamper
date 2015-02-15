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

#include <IceE/BuiltinSequences.h>
#include <IceE/BasicStream.h>
#include <IceE/Object.h>
#include <IceE/Iterator.h>
#include <IceE/DisableWarnings.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

void
Ice::__writeObjectProxySeq(::IceInternal::BasicStream* __os, const ::Ice::ObjectPrx* begin, const ::Ice::ObjectPrx* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        __os->write(begin[i]);
    }
}

void
Ice::__readObjectProxySeq(::IceInternal::BasicStream* __is, ::Ice::ObjectProxySeq& v)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 2);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        __is->read(v[i]);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}
