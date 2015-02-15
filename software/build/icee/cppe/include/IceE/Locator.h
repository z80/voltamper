// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `Locator.ice'

#ifndef __IceE_Locator_h__
#define __IceE_Locator_h__

#include <IceE/ProxyF.h>
#include <IceE/ObjectF.h>
#include <IceE/Exception.h>
#include <IceE/ScopedArray.h>
#include <IceE/Proxy.h>
#include <IceE/Object.h>
#ifndef ICEE_PURE_CLIENT
#  include <IceE/Incoming.h>
#endif
#include <IceE/Outgoing.h>
#ifdef ICEE_HAS_AMI
#   include <IceE/OutgoingAsync.h>
#endif
#include <IceE/UserExceptionFactory.h>
#include <IceE/FactoryTable.h>
#include <IceE/Identity.h>
#include <IceE/UndefSysMacros.h>

#ifndef ICEE_IGNORE_VERSION
#   if ICEE_INT_VERSION / 100 != 103
#       error IceE version mismatch!
#   endif
#   if ICEE_INT_VERSION % 100 < 0
#       error IceE patch level mismatch!
#   endif
#endif

#ifndef ICE_API
#   ifdef ICE_API_EXPORTS
#       define ICE_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace Ice
{

class LocatorRegistry;

class Locator;

}

}

namespace Ice
{

class LocatorRegistry;
ICE_API bool operator==(const LocatorRegistry&, const LocatorRegistry&);
ICE_API bool operator<(const LocatorRegistry&, const LocatorRegistry&);

class Locator;
ICE_API bool operator==(const Locator&, const Locator&);
ICE_API bool operator<(const Locator&, const Locator&);

}

namespace IceInternal
{

ICE_API ::Ice::Object* upCast(::Ice::LocatorRegistry*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::LocatorRegistry*);

ICE_API ::Ice::Object* upCast(::Ice::Locator*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Locator*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::LocatorRegistry> LocatorRegistryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::LocatorRegistry> LocatorRegistryPrx;

ICE_API void __read(::IceInternal::BasicStream*, LocatorRegistryPrx&);
ICE_API void __patch__LocatorRegistryPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Ice::Locator> LocatorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Locator> LocatorPrx;

ICE_API void __read(::IceInternal::BasicStream*, LocatorPrx&);
ICE_API void __patch__LocatorPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

class ICE_API AdapterNotFoundException : public ::Ice::UserException
{
public:

    AdapterNotFoundException() {}
    virtual ~AdapterNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

static AdapterNotFoundException __AdapterNotFoundException_init;

class ICE_API InvalidReplicaGroupIdException : public ::Ice::UserException
{
public:

    InvalidReplicaGroupIdException() {}
    virtual ~InvalidReplicaGroupIdException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class ICE_API AdapterAlreadyActiveException : public ::Ice::UserException
{
public:

    AdapterAlreadyActiveException() {}
    virtual ~AdapterAlreadyActiveException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class ICE_API ObjectNotFoundException : public ::Ice::UserException
{
public:

    ObjectNotFoundException() {}
    virtual ~ObjectNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class ICE_API ServerNotFoundException : public ::Ice::UserException
{
public:

    ServerNotFoundException() {}
    virtual ~ServerNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

}

namespace Ice
{

class ICE_API Locator : virtual public ::Ice::Object
{
public:

    typedef LocatorPrx ProxyType;
    typedef LocatorPtr PointerType;
    

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) const = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___findObjectById(::IceInternal::Incoming&, const ::Ice::Current&) const;
#endif // ICEE_PURE_CLIENT

    virtual ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___findAdapterById(::IceInternal::Incoming&, const ::Ice::Current&) const;
#endif // ICEE_PURE_CLIENT

    virtual ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Current& = ::Ice::Current()) const = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___getRegistry(::IceInternal::Incoming&, const ::Ice::Current&) const;
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

class ICE_API LocatorRegistry : virtual public ::Ice::Object
{
public:

    typedef LocatorRegistryPrx ProxyType;
    typedef LocatorRegistryPtr PointerType;
    

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setAdapterDirectProxy(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___setReplicatedAdapterDirectProxy(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
};

}

namespace Ice
{
#ifdef ICEE_HAS_AMI

class ICE_API AMI_Locator_findObjectById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorPrx&, const ::Ice::Identity&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Locator_findObjectById> AMI_Locator_findObjectByIdPtr;
#endif
#ifdef ICEE_HAS_AMI

class ICE_API AMI_Locator_findAdapterById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Locator_findAdapterById> AMI_Locator_findAdapterByIdPtr;
#endif

}

namespace IceProxy
{

namespace Ice
{

class Locator : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::ObjectPrx findObjectById(const ::Ice::Identity& id)
    {
        return findObjectById(id, 0);
    }
    ::Ice::ObjectPrx findObjectById(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        return findObjectById(id, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    ICE_API bool findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr&, const ::Ice::Identity&);
    ICE_API bool findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Context&);
    #endif

    ::Ice::ObjectPrx findAdapterById(const ::std::string& id)
    {
        return findAdapterById(id, 0);
    }
    ::Ice::ObjectPrx findAdapterById(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return findAdapterById(id, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    ICE_API bool findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr&, const ::std::string&);
    ICE_API bool findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr&, const ::std::string&, const ::Ice::Context&);
    #endif

    ::Ice::LocatorRegistryPrx getRegistry()
    {
        return getRegistry(0);
    }
    ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context& __ctx)
    {
        return getRegistry(&__ctx);
    }
    
private:

    ICE_API ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Locator> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_secure(bool __secure) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<Locator> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<Locator> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<Locator> ice_twoway() const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_oneway() const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_batchOneway() const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_datagram() const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_batchDatagram() const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ICE_API static const ::std::string& ice_staticId();
    
private:
    
    ICE_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class LocatorRegistry : virtual public ::IceProxy::Ice::Object
{
public:

    void setAdapterDirectProxy(const ::std::string& id, const ::Ice::ObjectPrx& proxy)
    {
        setAdapterDirectProxy(id, proxy, 0);
    }
    void setAdapterDirectProxy(const ::std::string& id, const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        setAdapterDirectProxy(id, proxy, &__ctx);
    }
    
private:

    ICE_API void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    void setReplicatedAdapterDirectProxy(const ::std::string& adapterId, const ::std::string& replicaGroupId, const ::Ice::ObjectPrx& proxy)
    {
        setReplicatedAdapterDirectProxy(adapterId, replicaGroupId, proxy, 0);
    }
    void setReplicatedAdapterDirectProxy(const ::std::string& adapterId, const ::std::string& replicaGroupId, const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        setReplicatedAdapterDirectProxy(adapterId, replicaGroupId, proxy, &__ctx);
    }
    
private:

    ICE_API void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_secure(bool __secure) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_twoway() const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_oneway() const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_batchOneway() const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_datagram() const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_batchDatagram() const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_timeout(int __timeout) const
    {
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ICE_API static const ::std::string& ice_staticId();
    
private:
    
    ICE_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
