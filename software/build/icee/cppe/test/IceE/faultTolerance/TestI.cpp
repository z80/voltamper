// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include <TestCommon.h>
#include <TestI.h>

#if !defined(_WIN32_WCE)
#if defined(_WIN32)
#   include <process.h> // For _getpid()
#else
#   include <unistd.h> // For getpid()
#endif
#endif

TestI::TestI(const Ice::ObjectAdapterPtr& adapter) :
    _adapter(adapter)
{
}

void
TestI::shutdown(const Ice::Current&)
{
    _adapter->getCommunicator()->shutdown();
}

void
TestI::abort(const Ice::Current&)
{
    exit(0);
}

void
TestI::idempotentAbort(const Ice::Current&)
{
    exit(0);
}

Ice::Int
TestI::pid(const Ice::Current&)
{
#if defined(_WIN32)
    return _getpid();
#else
    return getpid();
#endif
}
