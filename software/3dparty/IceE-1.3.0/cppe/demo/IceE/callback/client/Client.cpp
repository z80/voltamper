// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include <Callback.h>

using namespace std;
using namespace Demo;

class CallbackReceiverI : public CallbackReceiver
{
public:

    virtual void callback(const Ice::Current&)
    {
        printf("received callback\n"); fflush(stdout);
    }
};


void
menu()
{
    printf("usage:\n");
    printf("t: send callback as twoway\n");
    printf("o: send callback as oneway\n");
#ifdef ICEE_HAS_BATCH
    printf("O: send callback as batch oneway\n");
    printf("f: flush all batch requests\n");
#endif
    printf("s: shutdown server\n");
    printf("x: exit\n");
    printf("?: help\n");
}

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

    Ice::ObjectPrx base = communicator->stringToProxy(proxy);
    CallbackSenderPrx twoway = CallbackSenderPrx::checkedCast(base->ice_twoway()->ice_timeout(-1));
    if(!twoway)
    {
        fprintf(stderr, "%s: invalid proxy\n", argv[0]);
        return EXIT_FAILURE;
    }
    CallbackSenderPrx oneway = twoway->ice_oneway();
#ifdef ICEE_HAS_BATCH
    CallbackSenderPrx batchOneway = twoway->ice_batchOneway();
#endif    
    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Callback.Client");
    CallbackReceiverPtr cr = new CallbackReceiverI;
    adapter->add(cr, communicator->stringToIdentity("callbackReceiver"));
    adapter->activate();

    CallbackReceiverPrx twowayR = CallbackReceiverPrx::uncheckedCast(
        adapter->createProxy(communicator->stringToIdentity("callbackReceiver")));
    CallbackReceiverPrx onewayR = twowayR->ice_oneway();

    menu();

    char c = EOF;
    do
    {
        try
        {
            printf("==> "); fflush(stdout);
            do
            {
               c = getchar();
            }
            while(c != EOF && c == '\n');
            if(c == 't')
            {
                twoway->initiateCallback(twowayR);
            }
            else if(c == 'o')
            {
                oneway->initiateCallback(onewayR);
            }
#ifdef ICEE_HAS_BATCH
            else if(c == 'O')
            {
                batchOneway->initiateCallback(onewayR);
            }
            else if(c == 'f')
            {
                batchOneway->ice_flushBatchRequests();
            }
#endif
            else if(c == 's')
            {
                twoway->shutdown();
            }
            else if(c == 'x')
            {
                // Nothing to do
            }
            else if(c == '?')
            {
                menu();
            }
            else
            {
                printf("unknown command `%c'\n", c);
                menu();
            }
        }
        catch(const Ice::Exception& ex)
        {
            fprintf(stderr, "%s\n", ex.toString().c_str());
        }
    }
    while(c != EOF && c != 'x');

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
