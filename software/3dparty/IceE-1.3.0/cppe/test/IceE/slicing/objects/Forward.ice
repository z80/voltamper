// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef FORWARD_ICE
#define FORWARD_ICE

module Test
{

class Forward;

class Hidden
{
    Forward f;
};

class Forward
{
    Hidden h;
};

};

#endif
