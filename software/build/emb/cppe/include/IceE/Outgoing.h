// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_OUTGOING_H
#define ICEE_OUTGOING_H

#include <IceE/Mutex.h>
#include <IceE/Monitor.h>
#include <IceE/RequestHandlerF.h>
#include <IceE/InstanceF.h>
#include <IceE/ConnectionF.h>
#include <IceE/ReferenceF.h>
#include <IceE/BasicStream.h>
#include <IceE/Current.h>
#include <memory>

namespace Ice
{

class LocalException;

}

namespace IceInternal
{

//
// An exception wrapper, which is used for local exceptions that
// require special retry considerations.
//
class ICE_API LocalExceptionWrapper
{
public:

    LocalExceptionWrapper(const Ice::LocalException&, bool);
    LocalExceptionWrapper(const LocalExceptionWrapper&);

    const Ice::LocalException* get() const;

    //
    // If true, always repeat the request. Don't take retry settings
    // or "at-most-once" guarantees into account.
    //
    // If false, only repeat the request if the retry settings allow
    // to do so, and if "at-most-once" does not need to be guaranteed.
    //
    bool retry() const;

    static void throwWrapper(const ::std::exception&);

private:

    const LocalExceptionWrapper& operator=(const LocalExceptionWrapper&);

    std::auto_ptr<Ice::LocalException> _ex;
    bool _retry;
};

class ICE_API OutgoingMessageCallback : private IceUtil::noncopyable
{
public:

    virtual ~OutgoingMessageCallback() { }

    virtual void sent(bool) = 0;
    virtual void finished(const Ice::LocalException&) = 0;
};

class ICE_API Outgoing : public OutgoingMessageCallback
{
public:

    Outgoing(RequestHandler*, Reference*, const std::string&, Ice::OperationMode, const Ice::Context*);

    bool invoke(); // Returns true if ok, false if user exception.
    void abort(const Ice::LocalException&);
    virtual void sent(bool);
    virtual void finished(BasicStream&);
    void finished(const Ice::LocalException&);

    // Inlined for speed optimization.
    BasicStream* is() { return &_is; }
    BasicStream* os() { return &_os; }

private:

    //
    // Optimization. The request handler and the reference may not be
    // deleted while a stack-allocated Outgoing still holds it.
    //
    RequestHandler* _handler;
    Reference* _reference;

    std::auto_ptr<Ice::LocalException> _exception;

    enum
    {
        StateUnsent,
        StateInProgress,
        StateOK,
        StateUserException,
        StateLocalException,
        StateFailed
    } _state;

    BasicStream _is;
    BasicStream _os;
    bool _sent;

    //
    // NOTE: we use an attribute for the monitor instead of inheriting
    // from the monitor template.  Otherwise, the template would be
    // exported from the DLL on Windows and could cause linker errors
    // because of multiple definition of IceUtil::Monitor<IceUtil::Mutex>,
    // see bug 1541.
    //
    IceUtil::Monitor<IceUtil::Mutex> _monitor;
};

#ifdef ICEE_HAS_BATCH

class BatchOutgoing : public OutgoingMessageCallback
{
public:

    BatchOutgoing(RequestHandler*, Instance*);

    void invoke();

    virtual void sent(bool);
    virtual void finished(const Ice::LocalException&);

    BasicStream* os() { return &_os; }

private:

    IceUtil::Monitor<IceUtil::Mutex> _monitor;
    RequestHandler* _handler;
    bool _sent;
    std::auto_ptr<Ice::LocalException> _exception;

    BasicStream _os;
};

#endif

}

#endif
