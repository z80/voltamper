// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_EVENT_HANDLER_H
#define ICEE_EVENT_HANDLER_H

#include <IceE/Shared.h>
#include <IceE/EventHandlerF.h>
#include <IceE/InstanceF.h>
#include <IceE/ThreadPoolF.h>
#include <IceE/BasicStream.h>
#include <IceE/Network.h>
#include <IceE/SelectorF.h>

namespace Ice
{

class LocalException;

}

namespace IceInternal
{

class EventHandler : virtual public ::IceUtil::Shared
{
public:

    InstancePtr instance() const;
    
    //
    // Return true if read() must be called before calling message().
    //
    virtual bool readable() const = 0;

    //
    // Read data via the event handler. May only be called if
    // readable() returns true.
    //
    virtual bool read(BasicStream&) = 0;

    //
    // A complete message has been received.
    //
    virtual void message(BasicStream&, const ThreadPoolPtr&) = 0;

    //
    // Will be called if the event handler is finally
    // unregistered. (Calling unregister() does not unregister
    // immediately.)
    //
    virtual void finished(const ThreadPoolPtr&) = 0;

    //
    // Propagate an exception to the event handler.
    //
    virtual void exception(const ::Ice::LocalException&) = 0;

    //
    // Get a textual representation of the event handler.
    //
    virtual std::string toString() const = 0;

protected:
    
    EventHandler(const InstancePtr&, SOCKET = INVALID_SOCKET);
    ICE_API virtual ~EventHandler();

    const InstancePtr _instance;

    //
    // The _stream data member is for use by ThreadPool or by the
    // connection for connection validation only.
    //
    BasicStream _stream;
    SOCKET _fd;
    bool _serializing;
    bool _registered;
    friend class ThreadPool;
    friend class Selector<EventHandler>;
};

class ThreadPoolWorkItem : virtual public IceUtil::Shared
{
public:
    
    virtual void execute(const ThreadPoolPtr&) = 0;
};

}

#endif
