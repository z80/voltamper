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

#include <IceE/Router.h>
#include <IceE/LocalException.h>
#include <IceE/ObjectFactory.h>
#include <IceE/BasicStream.h>
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

static const ::std::string __Ice__Router__getClientProxy_name = "getClientProxy";

static const ::std::string __Ice__Router__getServerProxy_name = "getServerProxy";

static const ::std::string __Ice__Router__addProxy_name = "addProxy";

static const ::std::string __Ice__Router__addProxies_name = "addProxies";

::Ice::Object* IceInternal::upCast(::Ice::Router* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Ice::Router* p) { return p; }

void
Ice::__read(::IceInternal::BasicStream* __is, ::Ice::RouterPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Ice::Router;
        v->__copyFrom(proxy);
    }
}

static const ::std::string __Ice__Router_ids[2] =
{
    "::Ice::Object",
    "::Ice::Router"
};

bool
Ice::Router::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Ice__Router_ids, __Ice__Router_ids + 2, _s);
}

::std::vector< ::std::string>
Ice::Router::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Ice__Router_ids[0], &__Ice__Router_ids[2]);
}

const ::std::string&
Ice::Router::ice_id(const ::Ice::Current&) const
{
    return __Ice__Router_ids[1];
}

const ::std::string&
Ice::Router::ice_staticId()
{
    return __Ice__Router_ids[1];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Router::___getClientProxy(::IceInternal::Incoming& __inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::ObjectPrx __ret = getClientProxy(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Router::___getServerProxy(::IceInternal::Incoming& __inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::ObjectPrx __ret = getServerProxy(__current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Router::___addProxy(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    addProxy(proxy, __current);
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Router::___addProxies(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::ObjectProxySeq proxies;
    ::Ice::__readObjectProxySeq(__is, proxies);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::ObjectProxySeq __ret = addProxies(proxies, __current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::Ice::__writeObjectProxySeq(__os, &__ret[0], &__ret[0] + __ret.size());
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Ice__Router_all[] =
{
    "addProxies",
    "addProxy",
    "getClientProxy",
    "getServerProxy",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Ice::Router::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Ice__Router_all, __Ice__Router_all + 8, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Ice__Router_all)
    {
        case 0:
        {
            return ___addProxies(in, current);
        }
        case 1:
        {
            return ___addProxy(in, current);
        }
        case 2:
        {
            return ___getClientProxy(in, current);
        }
        case 3:
        {
            return ___getServerProxy(in, current);
        }
        case 4:
        {
            return ___ice_id(in, current);
        }
        case 5:
        {
            return ___ice_ids(in, current);
        }
        case 6:
        {
            return ___ice_isA(in, current);
        }
        case 7:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Ice::Router::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Ice::Router::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
    ::Ice::Object::__read(__is, true);
}


bool
Ice::operator==(const ::Ice::Router& l, const ::Ice::Router& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Ice::operator<(const ::Ice::Router& l, const ::Ice::Router& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void ICE_DECLSPEC_EXPORT 
Ice::__patch__RouterPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Ice::RouterPtr* p = static_cast< ::Ice::RouterPtr*>(__addr);
    assert(p);
    *p = ::Ice::RouterPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Ice::Router::ice_staticId(), v->ice_id());
    }
}
#ifdef ICEE_HAS_AMI

bool
Ice::AMI_Router_getClientProxy::__invoke(const ::Ice::RouterPrx& __prx, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prx->__checkTwowayOnly(__Ice__Router__getClientProxy_name);
        __prepare(__prx, __Ice__Router__getClientProxy_name, ::Ice::Nonmutating, __ctx);
        __os->endWriteEncaps();
        return __send();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __releaseCallback(__ex);
        return false;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
}

void
Ice::AMI_Router_getClientProxy::__response(bool __ok)
{
    ::Ice::ObjectPrx __ret;
    try
    {
        if(!__ok)
        {
            __is->throwUnknownUserException();
        }
        __is->read(__ret);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
    ice_response(__ret);
    __releaseCallback();
}
#endif
#ifdef ICEE_HAS_AMI

bool
Ice::AMI_Router_addProxies::__invoke(const ::Ice::RouterPrx& __prx, const ::Ice::ObjectProxySeq& proxies, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prx->__checkTwowayOnly(__Ice__Router__addProxies_name);
        __prepare(__prx, __Ice__Router__addProxies_name, ::Ice::Idempotent, __ctx);
        if(proxies.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            ::Ice::__writeObjectProxySeq(__os, &proxies[0], &proxies[0] + proxies.size());
        }
        __os->endWriteEncaps();
        return __send();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __releaseCallback(__ex);
        return false;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
}

void
Ice::AMI_Router_addProxies::__response(bool __ok)
{
    ::Ice::ObjectProxySeq __ret;
    try
    {
        if(!__ok)
        {
            __is->throwUnknownUserException();
        }
        ::Ice::__readObjectProxySeq(__is, __ret);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __finished(__ex);
        return;
    }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
    catch(...)
    {
        throw;
    }
#endif
    ice_response(__ret);
    __releaseCallback();
}
#endif

::Ice::ObjectPrx
IceProxy::Ice::Router::getClientProxy(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Router__getClientProxy_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Router__getClientProxy_name, ::Ice::Nonmutating, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Ice::ObjectPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}
#ifdef ICEE_HAS_AMI

bool
IceProxy::Ice::Router::getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr& __cb)
{
    return __cb->__invoke(this, 0);
}

bool
IceProxy::Ice::Router::getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr& __cb, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, &__ctx);
}
#endif

::Ice::ObjectPrx
IceProxy::Ice::Router::getServerProxy(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Router__getServerProxy_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Router__getServerProxy_name, ::Ice::Nonmutating, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Ice::ObjectPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                __is->read(__ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

void
IceProxy::Ice::Router::addProxy(const ::Ice::ObjectPrx& proxy, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Router__addProxy_name, ::Ice::Idempotent, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(proxy);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}

::Ice::ObjectProxySeq
IceProxy::Ice::Router::addProxies(const ::Ice::ObjectProxySeq& proxies, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Router__addProxies_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Router__addProxies_name, ::Ice::Idempotent, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                if(proxies.size() == 0)
                {
                    __os->writeSize(0);
                }
                else
                {
                    ::Ice::__writeObjectProxySeq(__os, &proxies[0], &proxies[0] + proxies.size());
                }
            }
            catch(const ::Ice::LocalException& __ex)
            {
                __outS.abort(__ex);
            }
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Ice::ObjectProxySeq __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Ice::__readObjectProxySeq(__is, __ret);
                return __ret;
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
            catch(...)
            {
                throw;
            }
#endif
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapperRelaxed(__handler, __ex, __cnt);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__handler, __ex, __cnt);
        }
#if defined(_MSC_VER) && defined(_M_ARM) // ARM bug.
        catch(...)
        {
            throw;
        }
#endif
    }
}
#ifdef ICEE_HAS_AMI

bool
IceProxy::Ice::Router::addProxies_async(const ::Ice::AMI_Router_addProxiesPtr& __cb, const ::Ice::ObjectProxySeq& proxies)
{
    return __cb->__invoke(this, proxies, 0);
}

bool
IceProxy::Ice::Router::addProxies_async(const ::Ice::AMI_Router_addProxiesPtr& __cb, const ::Ice::ObjectProxySeq& proxies, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, proxies, &__ctx);
}
#endif

const ::std::string&
IceProxy::Ice::Router::ice_staticId()
{
    return __Ice__Router_ids[1];
}

::IceProxy::Ice::Object*
IceProxy::Ice::Router::__newInstance() const
{
    return new Router;
}
