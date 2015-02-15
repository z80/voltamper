// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_SERVANT_MANAGER_F_H
#define ICEE_SERVANT_MANAGER_F_H

#include <IceE/Handle.h>
#include <IceE/Shared.h>

namespace IceInternal
{

class ServantManager;
IceUtil::Shared* upCast(ServantManager*);
typedef Handle<ServantManager> ServantManagerPtr;

}

#endif
