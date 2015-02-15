// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Callback.h>
#include <IceE/IceE.h>

using namespace std;
using namespace Demo;

class CallbackReceiverI : public CallbackReceiver
{
public:

    virtual void
    callback(Ice::Int num, const Ice::Current&)
    {
        printf("received callback #%d\n", num); fflush(stdout);
    }
};

int
run(int argc, char* argv[], const Ice::CommunicatorPtr& communicator)
{
    if(argc > 1)
    {
        fprintf(stderr, "%s: too many arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    Ice::PropertiesPtr properties = communicator->getProperties();
    const char* proxyProperty = "CallbackSender.Proxy";
    string proxy = properties->getProperty(proxyProperty);
    if(proxy.empty())
    {
        fprintf(stderr, "%s: property `%s' not set\n", argv[0], proxyProperty);
        return EXIT_FAILURE;
    }

    CallbackSenderPrx server = CallbackSenderPrx::checkedCast(communicator->stringToProxy(proxy));
    if(!server)
    {
        fprintf(stderr, "%s: invalid proxy\n", argv[0]);
        return EXIT_FAILURE;
    }

    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Callback.Client");
    Ice::Identity ident;
    ident.name = IceUtil::generateUUID();
    ident.category = "";
    CallbackReceiverPtr cr = new CallbackReceiverI;
    adapter->add(cr, ident);
    adapter->activate();
    server->ice_getConnection()->setAdapter(adapter);
    server->addClient(ident);
    communicator->waitForShutdown();

    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    Ice::CommunicatorPtr communicator;

    try
    {
        Ice::InitializationData initData;
        initData.properties = Ice::createProperties();
        initData.properties->load("config");
        communicator = Ice::initialize(argc, argv, initData);
        status = run(argc, argv, communicator);
    }
    catch(const Ice::Exception& ex)
    {
        fprintf(stderr, "%s\n", ex.toString().c_str());
        status = EXIT_FAILURE;
    }

    if(communicator)
    {
        try
        {
            communicator->destroy();
        }
        catch(const Ice::Exception& ex)
        {
            fprintf(stderr, "%s\n", ex.toString().c_str());
            status = EXIT_FAILURE;
        }
    }

    return status;
}
