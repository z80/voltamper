// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_ICE
#define TEST_ICE

module Test
{

interface TestIntf
{
    ["ami"] string getAdapterName();
};

interface RemoteObjectAdapter
{
    TestIntf* getTestIntf();
    
    void deactivate();
};

interface RemoteCommunicator
{
    RemoteObjectAdapter* createObjectAdapter(string name, string endpoints);

    void deactivateObjectAdapter(RemoteObjectAdapter* adapter);

    void shutdown();
};

};

#endif
