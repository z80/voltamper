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

#include <IceE/Locator.h>
#include <IceE/LocalException.h>
#include <IceE/ObjectFactory.h>
#include <IceE/BasicStream.h>
#include <IceE/LocalException.h>
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

static const ::std::string __Ice__Locator__findObjectById_name = "findObjectById";

static const ::std::string __Ice__Locator__findAdapterById_name = "findAdapterById";

static const ::std::string __Ice__Locator__getRegistry_name = "getRegistry";

static const ::std::string __Ice__LocatorRegistry__setAdapterDirectProxy_name = "setAdapterDirectProxy";

static const ::std::string __Ice__LocatorRegistry__setReplicatedAdapterDirectProxy_name = "setReplicatedAdapterDirectProxy";

::Ice::Object* IceInternal::upCast(::Ice::Locator* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Ice::Locator* p) { return p; }

::Ice::Object* IceInternal::upCast(::Ice::LocatorRegistry* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::Ice::LocatorRegistry* p) { return p; }

void
Ice::__read(::IceInternal::BasicStream* __is, ::Ice::LocatorPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Ice::Locator;
        v->__copyFrom(proxy);
    }
}

void
Ice::__read(::IceInternal::BasicStream* __is, ::Ice::LocatorRegistryPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::Ice::LocatorRegistry;
        v->__copyFrom(proxy);
    }
}

Ice::AdapterNotFoundException::~AdapterNotFoundException() throw()
{
}

static const char* __Ice__AdapterNotFoundException_name = "Ice::AdapterNotFoundException";

::std::string
Ice::AdapterNotFoundException::ice_name() const
{
    return __Ice__AdapterNotFoundException_name;
}

::Ice::Exception*
Ice::AdapterNotFoundException::ice_clone() const
{
    return new AdapterNotFoundException(*this);
}

void
Ice::AdapterNotFoundException::ice_throw() const
{
    throw *this;
}

void
Ice::AdapterNotFoundException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::Ice::AdapterNotFoundException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
}

void
Ice::AdapterNotFoundException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
}

struct __F__Ice__AdapterNotFoundException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::Ice::AdapterNotFoundException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__Ice__AdapterNotFoundException__Ptr = new __F__Ice__AdapterNotFoundException;

const ::IceInternal::UserExceptionFactoryPtr&
Ice::AdapterNotFoundException::ice_factory()
{
    return __F__Ice__AdapterNotFoundException__Ptr;
}

class __F__Ice__AdapterNotFoundException__Init
{
public:

    __F__Ice__AdapterNotFoundException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::Ice::AdapterNotFoundException", ::Ice::AdapterNotFoundException::ice_factory());
    }

    ~__F__Ice__AdapterNotFoundException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::Ice::AdapterNotFoundException");
    }
};

static __F__Ice__AdapterNotFoundException__Init __F__Ice__AdapterNotFoundException__i;

#ifdef __APPLE__
extern "C" { void __F__Ice__AdapterNotFoundException__initializer() {} }
#endif

Ice::InvalidReplicaGroupIdException::~InvalidReplicaGroupIdException() throw()
{
}

static const char* __Ice__InvalidReplicaGroupIdException_name = "Ice::InvalidReplicaGroupIdException";

::std::string
Ice::InvalidReplicaGroupIdException::ice_name() const
{
    return __Ice__InvalidReplicaGroupIdException_name;
}

::Ice::Exception*
Ice::InvalidReplicaGroupIdException::ice_clone() const
{
    return new InvalidReplicaGroupIdException(*this);
}

void
Ice::InvalidReplicaGroupIdException::ice_throw() const
{
    throw *this;
}

void
Ice::InvalidReplicaGroupIdException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::Ice::InvalidReplicaGroupIdException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
}

void
Ice::InvalidReplicaGroupIdException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
}

struct __F__Ice__InvalidReplicaGroupIdException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::Ice::InvalidReplicaGroupIdException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__Ice__InvalidReplicaGroupIdException__Ptr = new __F__Ice__InvalidReplicaGroupIdException;

const ::IceInternal::UserExceptionFactoryPtr&
Ice::InvalidReplicaGroupIdException::ice_factory()
{
    return __F__Ice__InvalidReplicaGroupIdException__Ptr;
}

class __F__Ice__InvalidReplicaGroupIdException__Init
{
public:

    __F__Ice__InvalidReplicaGroupIdException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::Ice::InvalidReplicaGroupIdException", ::Ice::InvalidReplicaGroupIdException::ice_factory());
    }

    ~__F__Ice__InvalidReplicaGroupIdException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::Ice::InvalidReplicaGroupIdException");
    }
};

static __F__Ice__InvalidReplicaGroupIdException__Init __F__Ice__InvalidReplicaGroupIdException__i;

#ifdef __APPLE__
extern "C" { void __F__Ice__InvalidReplicaGroupIdException__initializer() {} }
#endif

Ice::AdapterAlreadyActiveException::~AdapterAlreadyActiveException() throw()
{
}

static const char* __Ice__AdapterAlreadyActiveException_name = "Ice::AdapterAlreadyActiveException";

::std::string
Ice::AdapterAlreadyActiveException::ice_name() const
{
    return __Ice__AdapterAlreadyActiveException_name;
}

::Ice::Exception*
Ice::AdapterAlreadyActiveException::ice_clone() const
{
    return new AdapterAlreadyActiveException(*this);
}

void
Ice::AdapterAlreadyActiveException::ice_throw() const
{
    throw *this;
}

void
Ice::AdapterAlreadyActiveException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::Ice::AdapterAlreadyActiveException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
}

void
Ice::AdapterAlreadyActiveException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
}

struct __F__Ice__AdapterAlreadyActiveException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::Ice::AdapterAlreadyActiveException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__Ice__AdapterAlreadyActiveException__Ptr = new __F__Ice__AdapterAlreadyActiveException;

const ::IceInternal::UserExceptionFactoryPtr&
Ice::AdapterAlreadyActiveException::ice_factory()
{
    return __F__Ice__AdapterAlreadyActiveException__Ptr;
}

class __F__Ice__AdapterAlreadyActiveException__Init
{
public:

    __F__Ice__AdapterAlreadyActiveException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::Ice::AdapterAlreadyActiveException", ::Ice::AdapterAlreadyActiveException::ice_factory());
    }

    ~__F__Ice__AdapterAlreadyActiveException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::Ice::AdapterAlreadyActiveException");
    }
};

static __F__Ice__AdapterAlreadyActiveException__Init __F__Ice__AdapterAlreadyActiveException__i;

#ifdef __APPLE__
extern "C" { void __F__Ice__AdapterAlreadyActiveException__initializer() {} }
#endif

Ice::ObjectNotFoundException::~ObjectNotFoundException() throw()
{
}

static const char* __Ice__ObjectNotFoundException_name = "Ice::ObjectNotFoundException";

::std::string
Ice::ObjectNotFoundException::ice_name() const
{
    return __Ice__ObjectNotFoundException_name;
}

::Ice::Exception*
Ice::ObjectNotFoundException::ice_clone() const
{
    return new ObjectNotFoundException(*this);
}

void
Ice::ObjectNotFoundException::ice_throw() const
{
    throw *this;
}

void
Ice::ObjectNotFoundException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::Ice::ObjectNotFoundException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
}

void
Ice::ObjectNotFoundException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
}

struct __F__Ice__ObjectNotFoundException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::Ice::ObjectNotFoundException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__Ice__ObjectNotFoundException__Ptr = new __F__Ice__ObjectNotFoundException;

const ::IceInternal::UserExceptionFactoryPtr&
Ice::ObjectNotFoundException::ice_factory()
{
    return __F__Ice__ObjectNotFoundException__Ptr;
}

class __F__Ice__ObjectNotFoundException__Init
{
public:

    __F__Ice__ObjectNotFoundException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::Ice::ObjectNotFoundException", ::Ice::ObjectNotFoundException::ice_factory());
    }

    ~__F__Ice__ObjectNotFoundException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::Ice::ObjectNotFoundException");
    }
};

static __F__Ice__ObjectNotFoundException__Init __F__Ice__ObjectNotFoundException__i;

#ifdef __APPLE__
extern "C" { void __F__Ice__ObjectNotFoundException__initializer() {} }
#endif

Ice::ServerNotFoundException::~ServerNotFoundException() throw()
{
}

static const char* __Ice__ServerNotFoundException_name = "Ice::ServerNotFoundException";

::std::string
Ice::ServerNotFoundException::ice_name() const
{
    return __Ice__ServerNotFoundException_name;
}

::Ice::Exception*
Ice::ServerNotFoundException::ice_clone() const
{
    return new ServerNotFoundException(*this);
}

void
Ice::ServerNotFoundException::ice_throw() const
{
    throw *this;
}

void
Ice::ServerNotFoundException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::Ice::ServerNotFoundException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
}

void
Ice::ServerNotFoundException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
}

struct __F__Ice__ServerNotFoundException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::Ice::ServerNotFoundException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__Ice__ServerNotFoundException__Ptr = new __F__Ice__ServerNotFoundException;

const ::IceInternal::UserExceptionFactoryPtr&
Ice::ServerNotFoundException::ice_factory()
{
    return __F__Ice__ServerNotFoundException__Ptr;
}

class __F__Ice__ServerNotFoundException__Init
{
public:

    __F__Ice__ServerNotFoundException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::Ice::ServerNotFoundException", ::Ice::ServerNotFoundException::ice_factory());
    }

    ~__F__Ice__ServerNotFoundException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::Ice::ServerNotFoundException");
    }
};

static __F__Ice__ServerNotFoundException__Init __F__Ice__ServerNotFoundException__i;

#ifdef __APPLE__
extern "C" { void __F__Ice__ServerNotFoundException__initializer() {} }
#endif

static const ::std::string __Ice__Locator_ids[2] =
{
    "::Ice::Locator",
    "::Ice::Object"
};

bool
Ice::Locator::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Ice__Locator_ids, __Ice__Locator_ids + 2, _s);
}

::std::vector< ::std::string>
Ice::Locator::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Ice__Locator_ids[0], &__Ice__Locator_ids[2]);
}

const ::std::string&
Ice::Locator::ice_id(const ::Ice::Current&) const
{
    return __Ice__Locator_ids[0];
}

const ::std::string&
Ice::Locator::ice_staticId()
{
    return __Ice__Locator_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Locator::___findObjectById(::IceInternal::Incoming& __inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::Ice::Identity id;
    id.__read(__is);
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        ::Ice::ObjectPrx __ret = findObjectById(id, __current);
        __os->write(__ret);
    }
    catch(const ::Ice::ObjectNotFoundException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Locator::___findAdapterById(::IceInternal::Incoming& __inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    __is->read(id);
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        ::Ice::ObjectPrx __ret = findAdapterById(id, __current);
        __os->write(__ret);
    }
    catch(const ::Ice::AdapterNotFoundException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::Locator::___getRegistry(::IceInternal::Incoming& __inS, const ::Ice::Current& __current) const
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::Ice::LocatorRegistryPrx __ret = getRegistry(__current);
    __os->write(::Ice::ObjectPrx(::IceInternal::upCast(__ret.get())));
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Ice__Locator_all[] =
{
    "findAdapterById",
    "findObjectById",
    "getRegistry",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

::Ice::DispatchStatus
Ice::Locator::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Ice__Locator_all, __Ice__Locator_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Ice__Locator_all)
    {
        case 0:
        {
            return ___findAdapterById(in, current);
        }
        case 1:
        {
            return ___findObjectById(in, current);
        }
        case 2:
        {
            return ___getRegistry(in, current);
        }
        case 3:
        {
            return ___ice_id(in, current);
        }
        case 4:
        {
            return ___ice_ids(in, current);
        }
        case 5:
        {
            return ___ice_isA(in, current);
        }
        case 6:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Ice::Locator::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Ice::Locator::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Ice::operator==(const ::Ice::Locator& l, const ::Ice::Locator& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Ice::operator<(const ::Ice::Locator& l, const ::Ice::Locator& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void ICE_DECLSPEC_EXPORT 
Ice::__patch__LocatorPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Ice::LocatorPtr* p = static_cast< ::Ice::LocatorPtr*>(__addr);
    assert(p);
    *p = ::Ice::LocatorPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Ice::Locator::ice_staticId(), v->ice_id());
    }
}

static const ::std::string __Ice__LocatorRegistry_ids[2] =
{
    "::Ice::LocatorRegistry",
    "::Ice::Object"
};

bool
Ice::LocatorRegistry::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__Ice__LocatorRegistry_ids, __Ice__LocatorRegistry_ids + 2, _s);
}

::std::vector< ::std::string>
Ice::LocatorRegistry::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__Ice__LocatorRegistry_ids[0], &__Ice__LocatorRegistry_ids[2]);
}

const ::std::string&
Ice::LocatorRegistry::ice_id(const ::Ice::Current&) const
{
    return __Ice__LocatorRegistry_ids[0];
}

const ::std::string&
Ice::LocatorRegistry::ice_staticId()
{
    return __Ice__LocatorRegistry_ids[0];
}

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::LocatorRegistry::___setAdapterDirectProxy(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string id;
    ::Ice::ObjectPrx proxy;
    __is->read(id);
    __is->read(proxy);
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        setAdapterDirectProxy(id, proxy, __current);
    }
    catch(const ::Ice::AdapterAlreadyActiveException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    catch(const ::Ice::AdapterNotFoundException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
::Ice::DispatchStatus
Ice::LocatorRegistry::___setReplicatedAdapterDirectProxy(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Idempotent, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::std::string adapterId;
    ::std::string replicaGroupId;
    ::Ice::ObjectPrx proxy;
    __is->read(adapterId);
    __is->read(replicaGroupId);
    __is->read(proxy);
    ::IceInternal::BasicStream* __os = __inS.os();
    try
    {
        setReplicatedAdapterDirectProxy(adapterId, replicaGroupId, proxy, __current);
    }
    catch(const ::Ice::AdapterAlreadyActiveException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    catch(const ::Ice::AdapterNotFoundException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    catch(const ::Ice::InvalidReplicaGroupIdException& __ex)
    {
        __os->write(__ex);
        return ::Ice::DispatchUserException;
    }
    return ::Ice::DispatchOK;
}
#endif // ICEE_PURE_CLIENT

#ifndef ICEE_PURE_CLIENT
static ::std::string __Ice__LocatorRegistry_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "setAdapterDirectProxy",
    "setReplicatedAdapterDirectProxy"
};

::Ice::DispatchStatus
Ice::LocatorRegistry::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__Ice__LocatorRegistry_all, __Ice__LocatorRegistry_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __Ice__LocatorRegistry_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___setAdapterDirectProxy(in, current);
        }
        case 5:
        {
            return ___setReplicatedAdapterDirectProxy(in, current);
        }
    }

    assert(false);
    throw Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}
#endif // ICEE_PURE_CLIENT

void
Ice::LocatorRegistry::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
    ::Ice::Object::__write(__os);
}

void
Ice::LocatorRegistry::__read(::IceInternal::BasicStream* __is, bool __rid)
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
Ice::operator==(const ::Ice::LocatorRegistry& l, const ::Ice::LocatorRegistry& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
Ice::operator<(const ::Ice::LocatorRegistry& l, const ::Ice::LocatorRegistry& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

void ICE_DECLSPEC_EXPORT 
Ice::__patch__LocatorRegistryPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::Ice::LocatorRegistryPtr* p = static_cast< ::Ice::LocatorRegistryPtr*>(__addr);
    assert(p);
    *p = ::Ice::LocatorRegistryPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::Ice::LocatorRegistry::ice_staticId(), v->ice_id());
    }
}
#ifdef ICEE_HAS_AMI

bool
Ice::AMI_Locator_findObjectById::__invoke(const ::Ice::LocatorPrx& __prx, const ::Ice::Identity& id, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prx->__checkTwowayOnly(__Ice__Locator__findObjectById_name);
        __prepare(__prx, __Ice__Locator__findObjectById_name, ::Ice::Nonmutating, __ctx);
        id.__write(__os);
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
Ice::AMI_Locator_findObjectById::__response(bool __ok)
{
    ::Ice::ObjectPrx __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::ObjectNotFoundException& __ex)
            {
                __exception(__ex);
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
            return;
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
Ice::AMI_Locator_findAdapterById::__invoke(const ::Ice::LocatorPrx& __prx, const ::std::string& id, const ::Ice::Context* __ctx)
{
    __acquireCallback(__prx);
    try
    {
        __prx->__checkTwowayOnly(__Ice__Locator__findAdapterById_name);
        __prepare(__prx, __Ice__Locator__findAdapterById_name, ::Ice::Nonmutating, __ctx);
        __os->write(id);
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
Ice::AMI_Locator_findAdapterById::__response(bool __ok)
{
    ::Ice::ObjectPrx __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::AdapterNotFoundException& __ex)
            {
                __exception(__ex);
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
            return;
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

::Ice::ObjectPrx
IceProxy::Ice::Locator::findObjectById(const ::Ice::Identity& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Locator__findObjectById_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Locator__findObjectById_name, ::Ice::Nonmutating, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                id.__write(__os);
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
                    try
                    {
                        __outS.is()->throwException();
                    }
                    catch(const ::Ice::ObjectNotFoundException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::UserException& __ex)
                    {
                        ::Ice::UnknownUserException __uex(__FILE__, __LINE__);
                        __uex.unknown = __ex.ice_name();
                        throw __uex;
                    }
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
IceProxy::Ice::Locator::findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr& __cb, const ::Ice::Identity& id)
{
    return __cb->__invoke(this, id, 0);
}

bool
IceProxy::Ice::Locator::findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr& __cb, const ::Ice::Identity& id, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, id, &__ctx);
}
#endif

::Ice::ObjectPrx
IceProxy::Ice::Locator::findAdapterById(const ::std::string& id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Locator__findAdapterById_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Locator__findAdapterById_name, ::Ice::Nonmutating, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
                    try
                    {
                        __outS.is()->throwException();
                    }
                    catch(const ::Ice::AdapterNotFoundException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::UserException& __ex)
                    {
                        ::Ice::UnknownUserException __uex(__FILE__, __LINE__);
                        __uex.unknown = __ex.ice_name();
                        throw __uex;
                    }
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
IceProxy::Ice::Locator::findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr& __cb, const ::std::string& id)
{
    return __cb->__invoke(this, id, 0);
}

bool
IceProxy::Ice::Locator::findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr& __cb, const ::std::string& id, const ::Ice::Context& __ctx)
{
    return __cb->__invoke(this, id, &__ctx);
}
#endif

::Ice::LocatorRegistryPrx
IceProxy::Ice::Locator::getRegistry(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__Locator__getRegistry_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__Locator__getRegistry_name, ::Ice::Nonmutating, __ctx);
            bool __ok = __outS.invoke();
            try
            {
                if(!__ok)
                {
                    __outS.is()->throwUnknownUserException();
                }
                ::Ice::LocatorRegistryPrx __ret;
                ::IceInternal::BasicStream* __is = __outS.is();
                ::Ice::__read(__is, __ret);
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

const ::std::string&
IceProxy::Ice::Locator::ice_staticId()
{
    return __Ice__Locator_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Ice::Locator::__newInstance() const
{
    return new Locator;
}

void
IceProxy::Ice::LocatorRegistry::setAdapterDirectProxy(const ::std::string& id, const ::Ice::ObjectPrx& proxy, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__LocatorRegistry__setAdapterDirectProxy_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__LocatorRegistry__setAdapterDirectProxy_name, ::Ice::Idempotent, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(id);
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
                    try
                    {
                        __outS.is()->throwException();
                    }
                    catch(const ::Ice::AdapterAlreadyActiveException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::AdapterNotFoundException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::UserException& __ex)
                    {
                        ::Ice::UnknownUserException __uex(__FILE__, __LINE__);
                        __uex.unknown = __ex.ice_name();
                        throw __uex;
                    }
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

void
IceProxy::Ice::LocatorRegistry::setReplicatedAdapterDirectProxy(const ::std::string& adapterId, const ::std::string& replicaGroupId, const ::Ice::ObjectPrx& proxy, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::RequestHandlerPtr __handler;
        try
        {
            __checkTwowayOnly(__Ice__LocatorRegistry__setReplicatedAdapterDirectProxy_name);
            __handler = __getRequestHandler();
            ::IceInternal::Outgoing __outS(__handler.get(), _reference.get(), __Ice__LocatorRegistry__setReplicatedAdapterDirectProxy_name, ::Ice::Idempotent, __ctx);
            try
            {
                ::IceInternal::BasicStream* __os = __outS.os();
                __os->write(adapterId);
                __os->write(replicaGroupId);
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
                    try
                    {
                        __outS.is()->throwException();
                    }
                    catch(const ::Ice::AdapterAlreadyActiveException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::AdapterNotFoundException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::InvalidReplicaGroupIdException&)
                    {
                        throw;
                    }
                    catch(const ::Ice::UserException& __ex)
                    {
                        ::Ice::UnknownUserException __uex(__FILE__, __LINE__);
                        __uex.unknown = __ex.ice_name();
                        throw __uex;
                    }
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

const ::std::string&
IceProxy::Ice::LocatorRegistry::ice_staticId()
{
    return __Ice__LocatorRegistry_ids[0];
}

::IceProxy::Ice::Object*
IceProxy::Ice::LocatorRegistry::__newInstance() const
{
    return new LocatorRegistry;
}
