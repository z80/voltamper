// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_SELECTOR_F_H
#define ICEE_SELECTOR_F_H

namespace IceInternal
{

enum SocketStatus
{
    Finished,
    NeedConnect,
    NeedRead,
    NeedWrite
};

template<class T> class Selector;

};

#endif
