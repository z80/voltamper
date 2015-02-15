// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_I_H
#define TEST_I_H

#include <Test.h>

class TestI : public Test::TestIntf
{
public:

    TestI(const Ice::ObjectAdapterPtr&);

    virtual void shutdown(const Ice::Current&);
    virtual void abort(const Ice::Current&);
    virtual void idempotentAbort(const Ice::Current&);
    virtual Ice::Int pid(const Ice::Current&);

private:

    Ice::ObjectAdapterPtr _adapter;
};

#endif
