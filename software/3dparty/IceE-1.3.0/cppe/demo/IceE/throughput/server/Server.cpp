// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <ThroughputI.h>
#include <IceE/IceE.h>

using namespace std;

int
run(int argc, char* argv[], const Ice::CommunicatorPtr& communicator)
{
    //
    // Check if we need to run with small sequences
    //
    int reduce = 1;
    for(int i = 0; i < argc; ++i)
    {
        if(strcmp(argv[i], "--small") == 0)
        {
            reduce = 100;
        }
    }

    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Throughput");
    Demo::ThroughputPtr servant = new ThroughputI(reduce);
    adapter->add(servant, communicator->stringToIdentity("throughput"));
    adapter->activate();
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
