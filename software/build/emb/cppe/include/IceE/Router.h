// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice-E version 1.3.0
// Generated from file `Router.ice'

#ifndef __IceE_Router_h__
#define __IceE_Router_h__

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
#include <IceE/BuiltinSequences.h>
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

class Router;

}

}

namespace Ice
{

class Router;
ICE_API bool operator==(const Router&, const Router&);
ICE_API bool operator<(const Router&, const Router&);

}

namespace IceInternal
{

ICE_API ::Ice::Object* upCast(::Ice::Router*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Router*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Router> RouterPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Router> RouterPrx;

ICE_API void __read(::IceInternal::BasicStream*, RouterPrx&);
ICE_API void __patch__RouterPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

}

namespace Ice
{

class ICE_API Router : virtual public ::Ice::Object
{
public:

    typedef RouterPrx ProxyType;
    typedef RouterPtr PointerType;
    

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::ObjectPrx getClientProxy(const ::Ice::Current& = ::Ice::Current()) const = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___getClientProxy(::IceInternal::Incoming&, const ::Ice::Current&) const;
#endif // ICEE_PURE_CLIENT

    virtual ::Ice::ObjectPrx getServerProxy(const ::Ice::Current& = ::Ice::Current()) const = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___getServerProxy(::IceInternal::Incoming&, const ::Ice::Current&) const;
#endif // ICEE_PURE_CLIENT

    ICE_DEPRECATED_API virtual void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___addProxy(::IceInternal::Incoming&, const ::Ice::Current&);
#endif // ICEE_PURE_CLIENT

    virtual ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
#ifndef ICEE_PURE_CLIENT
    ::Ice::DispatchStatus ___addProxies(::IceInternal::Incoming&, const ::Ice::Current&);
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

class ICE_API AMI_Router_getClientProxy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::RouterPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Router_getClientProxy> AMI_Router_getClientProxyPtr;
#endif
#ifdef ICEE_HAS_AMI

class ICE_API AMI_Router_addProxies : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectProxySeq&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::RouterPrx&, const ::Ice::ObjectProxySeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Router_addProxies> AMI_Router_addProxiesPtr;
#endif

}

namespace IceProxy
{

namespace Ice
{

class Router : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::ObjectPrx getClientProxy()
    {
        return getClientProxy(0);
    }
    ::Ice::ObjectPrx getClientProxy(const ::Ice::Context& __ctx)
    {
        return getClientProxy(&__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx getClientProxy(const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    ICE_API bool getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr&);
    ICE_API bool getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr&, const ::Ice::Context&);
    #endif

    ::Ice::ObjectPrx getServerProxy()
    {
        return getServerProxy(0);
    }
    ::Ice::ObjectPrx getServerProxy(const ::Ice::Context& __ctx)
    {
        return getServerProxy(&__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx getServerProxy(const ::Ice::Context*);
    
public:

    ICE_DEPRECATED_API void addProxy(const ::Ice::ObjectPrx& proxy)
    {
        addProxy(proxy, 0);
    }
    ICE_DEPRECATED_API void addProxy(const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        addProxy(proxy, &__ctx);
    }
    
private:

    ICE_API void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq& proxies)
    {
        return addProxies(proxies, 0);
    }
    ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq& proxies, const ::Ice::Context& __ctx)
    {
        return addProxies(proxies, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Context*);
    
public:
    #ifdef ICEE_HAS_AMI
    ICE_API bool addProxies_async(const ::Ice::AMI_Router_addProxiesPtr&, const ::Ice::ObjectProxySeq&);
    ICE_API bool addProxies_async(const ::Ice::AMI_Router_addProxiesPtr&, const ::Ice::ObjectProxySeq&, const ::Ice::Context&);
    #endif
    
    ::IceInternal::ProxyHandle<Router> ice_context(const ::Ice::Context& __context) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_context(__context).get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_secure(bool __secure) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    }
    
#ifdef ICEE_HAS_ROUTER
    ::IceInternal::ProxyHandle<Router> ice_router(const ::Ice::RouterPrx& __router) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_router(__router).get());
    }
#endif // ICEE_HAS_ROUTER
    
#ifdef ICEE_HAS_LOCATOR
    ::IceInternal::ProxyHandle<Router> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_adapterId(const std::string& __id) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    }
#endif // ICEE_HAS_LOCATOR
    
    ::IceInternal::ProxyHandle<Router> ice_twoway() const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_twoway().get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_oneway() const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_oneway().get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_batchOneway() const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_datagram() const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_datagram().get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_batchDatagram() const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    }
    
    ::IceInternal::ProxyHandle<Router> ice_timeout(int __timeout) const
    {
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    }
    
    ICE_API static const ::std::string& ice_staticId();
    
private:
    
    ICE_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

#endif
