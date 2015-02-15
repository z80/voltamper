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

#include <IceE/Identity.h>
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

bool
Ice::Identity::operator==(const Identity& __rhs) const
{
    if(this == &__rhs)
    {
        return true;
    }
    if(name != __rhs.name)
    {
        return false;
    }
    if(category != __rhs.category)
    {
        return false;
    }
    return true;
}

bool
Ice::Identity::operator<(const Identity& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    if(category < __rhs.category)
    {
        return true;
    }
    else if(__rhs.category < category)
    {
        return false;
    }
    return false;
}

void
Ice::Identity::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(name);
    __os->write(category);
}

void
Ice::Identity::__read(::IceInternal::BasicStream* __is)
{
    __is->read(name);
    __is->read(category);
}
