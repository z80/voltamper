// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_INCOMING_H
#define ICEE_INCOMING_H

#include <IceE/InstanceF.h>
#include <IceE/ConnectionIF.h>
#include <IceE/ServantManagerF.h>
#include <IceE/BasicStream.h>
#include <IceE/Current.h>

namespace IceInternal
{

class ICE_API Incoming : private IceUtil::noncopyable
{
public:

    Incoming(Instance*, Ice::ConnectionI*, const Ice::ObjectAdapterPtr&);

    void setAdapter(const Ice::ObjectAdapterPtr&);
    const Ice::ObjectAdapterPtr& getAdapter() const { return _adapter; }

    void startOver();

    void invoke(bool, Ice::Int);

    // Inlined for speed optimization.
    BasicStream* os() { return &_os; }
    BasicStream* is() { return &_is; }

    const Ice::Current& getCurrent();

protected:
    
    void __warning(const Ice::Exception&) const;
    void __warning(const std::string&) const;

    BasicStream _os;
    BasicStream _is;
    Ice::ConnectionI* _connection;
    Ice::ObjectAdapterPtr _adapter;
    ServantManager* _servantManager;
    Ice::Current _current;
    bool _response;
    Ice::Byte* _inParamPos;
};

}

#endif
