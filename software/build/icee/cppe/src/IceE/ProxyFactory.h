// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_PROXY_FACTORY_H
#define ICEE_PROXY_FACTORY_H

#include <IceE/ProxyFactoryF.h>
#include <IceE/InstanceF.h>
#include <IceE/ReferenceF.h>
#include <IceE/ProxyF.h>
#include <IceE/Shared.h>
#include <IceE/OutgoingAsyncF.h>

namespace Ice
{

class LocalException;

}

namespace IceInternal
{

class BasicStream;

class ProxyFactory : public IceUtil::Shared
{
public:
    
    Ice::ObjectPrx stringToProxy(const std::string&) const;
    std::string proxyToString(const Ice::ObjectPrx&) const;

    Ice::ObjectPrx propertyToProxy(const std::string&) const;

    Ice::ObjectPrx streamToProxy(BasicStream*) const;
    void proxyToStream(const Ice::ObjectPrx&, BasicStream*) const;

    Ice::ObjectPrx referenceToProxy(const ReferencePtr&) const;

#ifndef ICEE_HAS_AMI
    void checkRetryAfterException(const Ice::LocalException&, const ReferencePtr&, int&) const;
#else
    void checkRetryAfterException(const Ice::LocalException&, const ReferencePtr&, OutgoingAsync*, int&) const;
#endif

private:

    ProxyFactory(const InstancePtr&);
    virtual ~ProxyFactory();
    friend class Instance;

    InstancePtr _instance;
    std::vector<int> _retryIntervals;
};

}

#endif
