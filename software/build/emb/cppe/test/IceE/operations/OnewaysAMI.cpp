// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include <TestCommon.h>
#include <Test.h>
#include <limits>

#ifdef ICEE_HAS_AMI

using namespace std;

class CallbackBase : public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    CallbackBase() :
        _called(false)
    {
    }

    virtual ~CallbackBase()
    {
    }

    bool check()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
        while(!_called)
        {
            if(!timedWait(IceUtil::Time::seconds(5)))
            {
                return false;
            }
        }
        _called = false;
        return true;
    }

protected:

    void called()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(*this);
        assert(!_called);
        _called = true;
        notify();
    }

private:

    bool _called;
};

class AMI_MyClass_onewayOpVoidI : public Test::AMI_MyClass_opVoid, public CallbackBase
{
public:

    virtual void ice_response()
    {
        called();
    }

    virtual void ice_exception(const ::Ice::Exception&)
    {
        test(false);
    }
};

typedef IceUtil::Handle<AMI_MyClass_onewayOpVoidI> AMI_MyClass_onewayOpVoidIPtr;

class AMI_MyClass_onewayOpVoidExI : public Test::AMI_MyClass_opVoid, public CallbackBase
{
public:

    virtual void ice_response()
    {
        test(false);
    }

    virtual void ice_exception(const ::Ice::Exception& ex)
    {
        test(dynamic_cast<const ::Ice::NoEndpointException*>(&ex));
        called();
    }
};

typedef IceUtil::Handle<AMI_MyClass_onewayOpVoidExI> AMI_MyClass_onewayOpVoidExIPtr;

class AMI_MyClass_onewayOpByteExI : public Test::AMI_MyClass_opByte, public CallbackBase
{
public:

    virtual void ice_response(::Ice::Byte r, ::Ice::Byte b)
    {
        test(false);
    }

    virtual void ice_exception(const ::Ice::Exception& ex)
    {
        test(dynamic_cast<const ::Ice::TwowayOnlyException*>(&ex));
        called();
    }
};

typedef IceUtil::Handle<AMI_MyClass_onewayOpByteExI> AMI_MyClass_onewayOpByteExIPtr;

void
onewaysAMI(const Ice::CommunicatorPtr& communicator, const Test::MyClassPrx& proxy)
{
    Test::MyClassPrx p = Test::MyClassPrx::uncheckedCast(proxy->ice_oneway());

    {
        AMI_MyClass_onewayOpVoidIPtr cb = new AMI_MyClass_onewayOpVoidI();
        p->opVoid_async(cb);
        // Let's check if we can reuse the same callback object for another call.
        p->opVoid_async(cb);
    }

    {
        // Check that a call to a void operation raises NoEndpointException
        // in the ice_exception() callback instead of at the point of call.
        Test::MyClassPrx indirect = Test::MyClassPrx::uncheckedCast(p->ice_adapterId("dummy"));
        AMI_MyClass_onewayOpVoidExIPtr cb = new AMI_MyClass_onewayOpVoidExI();
        try
        {
            indirect->opVoid_async(cb);
        }
        catch(const Ice::Exception&)
        {
            test(false);
        }
        test(cb->check());
    }

    {
        AMI_MyClass_onewayOpByteExIPtr cb = new AMI_MyClass_onewayOpByteExI();
        p->opByte_async(cb, 0, 0);
        test(cb->check());
    }
}

#endif
