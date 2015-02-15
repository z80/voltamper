// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/ObjectAdapter.h>
#include <IceE/ObjectAdapterFactory.h>
#include <IceE/UUID.h>
#include <IceE/Instance.h>
#include <IceE/ProxyFactory.h>
#include <IceE/ReferenceFactory.h>
#include <IceE/EndpointFactory.h>
#include <IceE/IncomingConnectionFactory.h>
#include <IceE/OutgoingConnectionFactory.h>
#include <IceE/ServantManager.h>
#include <IceE/LocalException.h>
#include <IceE/Properties.h>
#include <IceE/Functional.h>
#ifdef ICEE_HAS_LOCATOR
#    include <IceE/LocatorInfo.h>
#    include <IceE/Locator.h>
#endif
#ifdef ICEE_HAS_ROUTER
#    include <IceE/RouterInfo.h>
#    include <IceE/Router.h>
#endif
#include <IceE/Endpoint.h>
#include <IceE/LoggerUtil.h>
#include <IceE/TraceLevels.h>
#include <ctype.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

IceUtil::Shared* IceInternal::upCast(::Ice::ObjectAdapter* p) { return p; }

string
Ice::ObjectAdapter::getName() const
{
    //
    // No mutex lock necessary, _name is immutable.
    //
    return _noConfig ? string("") : _name;
}

CommunicatorPtr
Ice::ObjectAdapter::getCommunicator() const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    return _communicator;
}

void
Ice::ObjectAdapter::activate()
{
#ifdef ICEE_HAS_LOCATOR
    LocatorInfoPtr locatorInfo;
#endif
    bool printAdapterReady = false;

    {    
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
        
        checkForDeactivation();

        //
        // If the one off initializations of the adapter are already
        // done, we just need to activate the incoming connection
        // factories and we're done.
        //
        if(_activateOneOffDone)
        {
            for_each(_incomingConnectionFactories.begin(), _incomingConnectionFactories.end(),
                     Ice::voidMemFun(&IncomingConnectionFactory::activate));        
            return;
        }

        //
        // One off initializations of the adapter: update the locator
        // registry and print the "adapter ready" message. We set the
        // _waitForActivate flag to prevent deactivation from other
        // threads while these one off initializations are done.
        //
        _waitForActivate = true;

#ifdef ICEE_HAS_LOCATOR
        locatorInfo = _locatorInfo;
#endif
        if(!_noConfig)
        {
            printAdapterReady =
                _instance->initializationData().properties->getPropertyAsInt("Ice.PrintAdapterReady") > 0;
        }
    }

#ifdef ICEE_HAS_LOCATOR
    try
    {
        Ice::Identity dummy;
        dummy.name = "dummy";
        updateLocatorRegistry(locatorInfo, createDirectProxy(dummy));
    }
    catch(const Ice::LocalException&)
    {
        //
        // If we couldn't update the locator registry, we let the
        // exception go through and don't activate the adapter to
        // allow to user code to retry activating the adapter
        // later.
        //
        {
            IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
            _waitForActivate = false;
            notifyAll();
        }
        throw;
    }
#endif

    if(printAdapterReady)
    {
        printf("%s ready\n", _name.c_str());
        fflush(stdout);
    }

    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
        assert(!_deactivated); // Not possible if _waitForActivate = true;

        //
        // Signal threads waiting for the activation.
        //
        _waitForActivate = false;
        notifyAll();

        _activateOneOffDone = true;

        for_each(_incomingConnectionFactories.begin(), _incomingConnectionFactories.end(),
                 Ice::voidMemFun(&IncomingConnectionFactory::activate));
    }
}

void
Ice::ObjectAdapter::hold()
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
        
    for_each(_incomingConnectionFactories.begin(), _incomingConnectionFactories.end(),
             Ice::voidMemFun(&IncomingConnectionFactory::hold));
}
    
void
Ice::ObjectAdapter::waitForHold()
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    for_each(_incomingConnectionFactories.begin(), _incomingConnectionFactories.end(),
             Ice::constVoidMemFun(&IncomingConnectionFactory::waitUntilHolding));
}

void
Ice::ObjectAdapter::deactivate()
{
    vector<IncomingConnectionFactoryPtr> incomingConnectionFactories;
    OutgoingConnectionFactoryPtr outgoingConnectionFactory;
#ifdef ICEE_HAS_LOCATOR
    LocatorInfoPtr locatorInfo;
#endif

    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
        
        //
        // Ignore deactivation requests if the object adapter has already
        // been deactivated.
        //
        if(_deactivated)
        {
            return;
        }

        //
        // Wait for activation to complete. This is necessary to not 
        // get out of order locator updates.
        //
        while(_waitForActivate)
        {
            wait();
        }

#ifdef ICEE_HAS_ROUTER
        if(_routerInfo)
        {
            //
            // Remove entry from the router manager.
            //
            _instance->routerManager()->erase(_routerInfo->getRouter());

            //
            //  Clear this object adapter with the router.
            //
            _routerInfo->setAdapter(0);
        }
#endif

        incomingConnectionFactories = _incomingConnectionFactories;
        outgoingConnectionFactory = _instance->outgoingConnectionFactory();
#ifdef ICEE_HAS_LOCATOR
        locatorInfo = _locatorInfo;
#endif

        _deactivated = true;
        
        notifyAll();
    }

#ifdef ICEE_HAS_LOCATOR
    try
    {
        updateLocatorRegistry(locatorInfo, 0);
    }
    catch(const Ice::LocalException&)
    {
        //
        // We can't throw exceptions in deactivate so we ignore
        // failures to update the locator registry.
        //
    }
#endif

    //
    // Must be called outside the thread synchronization, because
    // Connection::destroy() might block when sending a CloseConnection
    // message.
    //
    for_each(incomingConnectionFactories.begin(), incomingConnectionFactories.end(),
             Ice::voidMemFun(&IncomingConnectionFactory::destroy));

#ifdef ICEE_HAS_ROUTER
    //
    // Must be called outside the thread synchronization, because
    // changing the object adapter might block if there are still
    // requests being dispatched.
    //
    outgoingConnectionFactory->removeAdapter(this);
#endif
}

void
Ice::ObjectAdapter::waitForDeactivate()
{
    vector<IceInternal::IncomingConnectionFactoryPtr> incomingConnectionFactories;

    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

        if(_destroyed)
        {
            return;
        }

        //
        // Wait for deactivation of the adapter itself, and for
        // the return of all direct method calls using this adapter.
        //
        while(!_deactivated)
        {
            wait();
        }

        incomingConnectionFactories = _incomingConnectionFactories;
    }

    //
    // Now we wait until all incoming connection factories are
    // finished.
    //
    for_each(incomingConnectionFactories.begin(), incomingConnectionFactories.end(),
             Ice::voidMemFun(&IncomingConnectionFactory::waitUntilFinished));
}

bool
Ice::ObjectAdapter::isDeactivated() const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    return _deactivated;
}

void
Ice::ObjectAdapter::destroy()
{
    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

        //
        // Another thread is in the process of destroying the object
        // adapter. Wait for it to finish.
        //
        while(_destroying)
        {
            wait();
        }

        //
        // Object adapter is already destroyed.
        //
        if(_destroyed)
        {
            return;
        }

        _destroying = true;
    }

    //
    // Deactivate and wait for completion.
    //
    deactivate();
    waitForDeactivate();

    //
    // Now it's also time to clean up our servants.
    //
    _servantManager->destroy();

    ObjectAdapterFactoryPtr objectAdapterFactory;

    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

        //
        // Signal that destroy is complete.
        //
        _destroying = false;
        _destroyed = true;
        notifyAll();

        //
        // We're done, now we can throw away all incoming connection
        // factories.
        //
        _incomingConnectionFactories.clear();

        //
        // Remove object references (some of them cyclic).
        //
        _instance = 0;
        _communicator = 0;
#ifdef ICEE_HAS_ROUTER
        _routerEndpoints.clear();
        _routerInfo = 0;
#endif
        _publishedEndpoints.clear();
#ifdef ICEE_HAS_LOCATOR
        _locatorInfo = 0;
#endif
        _reference = 0;

        objectAdapterFactory = _objectAdapterFactory;
        _objectAdapterFactory = 0;
    }

    if(objectAdapterFactory)
    {
        objectAdapterFactory->removeObjectAdapter(_name);
    }
}

ObjectPrx
Ice::ObjectAdapter::add(const ObjectPtr& object, const Identity& ident)
{
    return addFacet(object, ident, "");
}

ObjectPrx
Ice::ObjectAdapter::addFacet(const ObjectPtr& object, const Identity& ident, const string& facet)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    _servantManager->addServant(object, ident, facet);

    return newProxy(ident, facet);
}

ObjectPrx
Ice::ObjectAdapter::addWithUUID(const ObjectPtr& object)
{
    return addFacetWithUUID(object, "");
}

ObjectPrx
Ice::ObjectAdapter::addFacetWithUUID(const ObjectPtr& object, const string& facet)
{
    Identity ident;
    ident.name = IceUtil::generateUUID();
    return addFacet(object, ident, facet);
}

void
Ice::ObjectAdapter::addDefaultServant(const ObjectPtr& object, const string& category)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    return _servantManager->addDefaultServant(object, category);
}

ObjectPtr
Ice::ObjectAdapter::remove(const Identity& ident)
{
    return removeFacet(ident, "");
}

ObjectPtr
Ice::ObjectAdapter::removeFacet(const Identity& ident, const string& facet)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    return _servantManager->removeServant(ident, facet);
}

FacetMap
Ice::ObjectAdapter::removeAllFacets(const Identity& ident)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    return _servantManager->removeAllFacets(ident);
}

ObjectPtr
Ice::ObjectAdapter::removeDefaultServant(const string& category)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    return _servantManager->removeDefaultServant(category);
}

ObjectPtr
Ice::ObjectAdapter::find(const Identity& ident) const
{
    return findFacet(ident, "");
}

ObjectPtr
Ice::ObjectAdapter::findFacet(const Identity& ident, const string& facet) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    return _servantManager->findServant(ident, facet);
}

FacetMap
Ice::ObjectAdapter::findAllFacets(const Identity& ident) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    return _servantManager->findAllFacets(ident);
}

ObjectPtr
Ice::ObjectAdapter::findByProxy(const ObjectPrx& proxy) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    ReferencePtr ref = proxy->__reference();
    return findFacet(ref->getIdentity(), ref->getFacet());
}

ObjectPtr
Ice::ObjectAdapter::findDefaultServant(const string& category) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();

    return _servantManager->findDefaultServant(category);
}

ObjectPrx
Ice::ObjectAdapter::createProxy(const Identity& ident) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

    checkForDeactivation();
    checkIdentity(ident);

    return newProxy(ident, "");
}

#ifdef ICEE_HAS_LOCATOR
ObjectPrx
Ice::ObjectAdapter::createDirectProxy(const Identity& ident) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
    
    checkForDeactivation();
    checkIdentity(ident);

    return newDirectProxy(ident, "");
}

ObjectPrx
Ice::ObjectAdapter::createIndirectProxy(const Identity& ident) const
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
    
    checkForDeactivation();
    checkIdentity(ident);

    return newIndirectProxy(ident, "", _id);
}
#endif

#ifdef ICEE_HAS_LOCATOR
void
Ice::ObjectAdapter::setLocator(const LocatorPrx& locator)
{
    IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
    
    checkForDeactivation();

    _locatorInfo = _instance->locatorManager()->get(locator);
}
#endif

void
Ice::ObjectAdapter::refreshPublishedEndpoints()
{
#ifdef ICEE_HAS_LOCATOR
    LocatorInfoPtr locatorInfo;
#endif
    vector<EndpointPtr> oldPublishedEndpoints;

    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

        checkForDeactivation();

        oldPublishedEndpoints = _publishedEndpoints;
        _publishedEndpoints = parsePublishedEndpoints();

#ifdef ICEE_HAS_LOCATOR
        locatorInfo = _locatorInfo;
#endif
    }

#ifdef ICEE_HAS_LOCATOR
    try
    {
        Ice::Identity dummy;
        dummy.name = "dummy";
        updateLocatorRegistry(locatorInfo, createDirectProxy(dummy));
    }
    catch(const Ice::LocalException& ex)
    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);

        //
        // Restore the old published endpoints.
        //
        _publishedEndpoints = oldPublishedEndpoints;
        ex.ice_throw();
    }
#endif
}

#ifdef ICEE_HAS_BATCH
void
Ice::ObjectAdapter::flushBatchRequests()
{
    vector<IncomingConnectionFactoryPtr> f;
    {
        IceUtil::Monitor<IceUtil::RecMutex>::Lock sync(*this);
        f = _incomingConnectionFactories;
    }
    for_each(f.begin(), f.end(), Ice::voidMemFun(&IncomingConnectionFactory::flushBatchRequests));
}
#endif

ServantManagerPtr
Ice::ObjectAdapter::getServantManager() const
{
    //
    // No mutex lock necessary, _servantManager is immutable.
    //
    return _servantManager;
}

Ice::ObjectAdapter::ObjectAdapter(const InstancePtr& instance, const CommunicatorPtr& communicator,
                                  const ObjectAdapterFactoryPtr& objectAdapterFactory, 
                                  const string& name, const string& endpointInfo,
#ifdef ICEE_HAS_ROUTER
                                  const RouterPrx& router,
#endif
                                  bool noConfig) :
    _deactivated(false),
    _instance(instance),
    _communicator(communicator),
    _objectAdapterFactory(objectAdapterFactory),
    _servantManager(new ServantManager(instance, name)),
    _activateOneOffDone(false),
    _name(name),
#ifdef ICEE_HAS_LOCATOR
    _id(instance->initializationData().properties->getProperty(name + ".AdapterId")),
    _replicaGroupId(instance->initializationData().properties->getProperty(name + ".ReplicaGroupId")),
#endif
    _waitForActivate(false),
    _destroying(false),
    _destroyed(false),
    _noConfig(noConfig)
{
    if(_noConfig)
    {
        _reference = _instance->referenceFactory()->create("dummy -t", "");
        return;
    }

    PropertiesPtr properties = instance->initializationData().properties;

    //
    // Setup a reference to be used to get the default proxy options
    // when creating new proxies. By default, create twoway proxies.
    //
    string proxyOptions = properties->getPropertyWithDefault(_name + ".ProxyOptions", "-t");
    try
    {
        _reference = _instance->referenceFactory()->create("dummy " + proxyOptions, "");
    }
    catch(const ProxyParseException&)
    {
        InitializationException ex(__FILE__, __LINE__);
        ex.reason = "invalid proxy options `" + proxyOptions + "' for object adapter `" + _name + "'";
        throw ex;
    }

    __setNoDelete(true);
    try
    {
#ifdef ICEE_HAS_ROUTER
        if(!router)
        {
            string routerStr = _instance->initializationData().properties->getProperty(_name + ".Router");
            if(!routerStr.empty())
            {
                const_cast<RouterPrx&>(router) =
                    RouterPrx::uncheckedCast(_instance->proxyFactory()->stringToProxy(routerStr));
            }
        }
        if(router)
        {
            _routerInfo = _instance->routerManager()->get(router);
            if(_routerInfo)
            {
                //
                // Make sure this router is not already registered with another adapter.
                //
                if(_routerInfo->getAdapter())
                {
                    throw AlreadyRegisteredException(__FILE__, __LINE__, "object adapter with router",
                                                     _instance->identityToString(router->ice_getIdentity()));
                }

                //
                // Add the router's server proxy endpoints to this object
                // adapter.
                //
                vector<EndpointPtr> endpoints = _routerInfo->getServerEndpoints();
                copy(endpoints.begin(), endpoints.end(), back_inserter(_routerEndpoints));
                sort(_routerEndpoints.begin(), _routerEndpoints.end()); // Must be sorted.
                _routerEndpoints.erase(unique(_routerEndpoints.begin(), _routerEndpoints.end()),
                                       _routerEndpoints.end());

                //
                // Associate this object adapter with the router. This way,
                // new outgoing connections to the router's client proxy will
                // use this object adapter for callbacks.
                //
                _routerInfo->setAdapter(this);

                //
                // Also modify all existing outgoing connections to the
                // router's client proxy to use this object adapter for
                // callbacks.
                //      
                _instance->outgoingConnectionFactory()->setRouterInfo(_routerInfo);
            }
        }
        else
#endif
        {
            //
            // Parse the endpoints, but don't store them in the adapter.
            // The connection factory might change it, for example, to
            // fill in the real port number.
            //
            vector<EndpointPtr> endpoints;
            if(endpointInfo.empty())
            {
                endpoints = 
                    parseEndpoints(_instance->initializationData().properties->getProperty(_name + ".Endpoints"), true);
            }
            else
            {
                endpoints = parseEndpoints(endpointInfo, true);
            }

            for(vector<EndpointPtr>::iterator p = endpoints.begin(); p != endpoints.end(); ++p)
            {
                _incomingConnectionFactories.push_back(new IncomingConnectionFactory(_instance, *p, this));
            }

            if(endpoints.empty())
            {
                TraceLevelsPtr tl = _instance->traceLevels();
                if(tl->network >= 2)
                {
                    Trace out(_instance->initializationData().logger, tl->networkCat);
                    out << "created adapter `" << name << "' without endpoints";
                }
            }

            //
            // Parse published endpoints.
            //
            _publishedEndpoints = parsePublishedEndpoints();
        }

#ifdef ICEE_HAS_LOCATOR
        string locator = _instance->initializationData().properties->getProperty(_name + ".Locator");
        if(!locator.empty())
        {
            setLocator(LocatorPrx::uncheckedCast(_instance->proxyFactory()->stringToProxy(locator)));
        }
        else
        {
            setLocator(_instance->referenceFactory()->getDefaultLocator());
        }
#endif
    }
    catch(...)
    {
        //
        // There's no need to remove the adapter from the factory if
        // creation fails. Furthermore, since this code is called with
        // the factory mutex locked, we can't call removeObjectAdapter
        // on the factory here so we clear the factory reference to
        // ensure it won't be called by destroy().
        // 
        _objectAdapterFactory = 0;

        destroy();
        __setNoDelete(false);
        throw;
    }
    __setNoDelete(false);  
}

Ice::ObjectAdapter::~ObjectAdapter()
{
    if(!_deactivated)
    {
        Warning out(_instance->initializationData().logger);
        out << "object adapter `" << _name << "' has not been deactivated";
    }
    else if(!_destroyed)
    {
        Warning out(_instance->initializationData().logger);
        out << "object adapter `" << _name << "' has not been destroyed";
    }
    else
    {
        //assert(!_servantManager); // We don't clear this reference, it needs to be immutable.
        assert(!_communicator);
        assert(_incomingConnectionFactories.empty());
        assert(!_waitForActivate);
    }
}

ObjectPrx
Ice::ObjectAdapter::newProxy(const Identity& ident, const string& facet) const
{
#ifdef ICEE_HAS_LOCATOR
    if(_id.empty())
    {
#endif
        return newDirectProxy(ident, facet);
#ifdef ICEE_HAS_LOCATOR
    }
    else if(_replicaGroupId.empty())
    {
        return newIndirectProxy(ident, facet, _id);
    }
    else
    {
        return newIndirectProxy(ident, facet, _replicaGroupId);
    }
#endif
}

ObjectPrx
Ice::ObjectAdapter::newDirectProxy(const Identity& ident, const string& facet) const
{
    vector<EndpointPtr> endpoints = _publishedEndpoints;
    
    //
    // Now we also add the endpoints of the router's server proxy, if
    // any. This way, object references created by this object adapter
    // will also point to the router's server proxy endpoints.
    //
#ifdef ICEE_HAS_ROUTER
    copy(_routerEndpoints.begin(), _routerEndpoints.end(), back_inserter(endpoints));
#endif
    
    //
    // Create a reference and return a proxy for this reference.
    //
    ReferencePtr ref = _instance->referenceFactory()->create(ident, facet, _reference, endpoints);
    return _instance->proxyFactory()->referenceToProxy(ref);
}

#ifdef ICEE_HAS_LOCATOR
ObjectPrx
Ice::ObjectAdapter::newIndirectProxy(const Identity& ident, const string& facet, const string& id) const
{
    //
    // Create a reference with the adapter id.
    //
    ReferencePtr ref = _instance->referenceFactory()->create(ident, facet, _reference, id);

    //
    // Return a proxy for the reference. 
    //
    return _instance->proxyFactory()->referenceToProxy(ref);
}
#endif

void
Ice::ObjectAdapter::checkForDeactivation() const
{
    if(_deactivated)
    {
        ObjectAdapterDeactivatedException ex(__FILE__, __LINE__);
        ex.name = _name;
        throw ex;
    }
}

void
Ice::ObjectAdapter::checkIdentity(const Identity& ident)
{
    if(ident.name.size() == 0)
    {
        IllegalIdentityException e(__FILE__, __LINE__);
        e.id = ident;
        throw e;
    }
}

vector<EndpointPtr>
Ice::ObjectAdapter::parseEndpoints(const string& endpts, bool oaEndpoints) const
{
    string::size_type beg;
    string::size_type end = 0;

    vector<EndpointPtr> endpoints;
    while(end < endpts.length())
    {
        const string delim = " \t\n\r";
        
        beg = endpts.find_first_not_of(delim, end);
        if(beg == string::npos)
        {
            break;
        }

        end = endpts.find(':', beg);
        if(end == string::npos)
        {
            end = endpts.length();
        }
        
        if(end == beg)
        {
            ++end;
            continue;
        }
        
        string s = endpts.substr(beg, end - beg);
        EndpointPtr endp = _instance->endpointFactory()->create(s, oaEndpoints);
        if(endp == 0)
        {
            EndpointParseException ex(__FILE__, __LINE__);
            ex.str = s;
            throw ex;
        }
        endpoints.push_back(endp);

        ++end;
    }

    return endpoints;
}

std::vector<EndpointPtr>
ObjectAdapter::parsePublishedEndpoints()
{
    //
    // Parse published endpoints. If set, these are used in proxies
    // instead of the connection factory endpoints. 
    //
    string endpts = _instance->initializationData().properties->getProperty(_name + ".PublishedEndpoints");
    vector<EndpointPtr> endpoints = parseEndpoints(endpts, false);
    if(!endpoints.empty())
    {
        return endpoints;
    }

    //
    // If the PublishedEndpoints property isn't set, we compute the published enpdoints
    // from the OA endpoints.
    //
    transform(_incomingConnectionFactories.begin(), _incomingConnectionFactories.end(),
              back_inserter(endpoints), Ice::constMemFun(&IncomingConnectionFactory::endpoint));

    //
    // Expand any endpoints that may be listening on INADDR_ANY to include actual
    // addresses in the published endpoints.
    //
    vector<EndpointPtr> expandedEndpoints;
    for(unsigned int i = 0; i < endpoints.size(); ++i)
    {
        vector<EndpointPtr> endps = endpoints[i]->expand();
        expandedEndpoints.insert(expandedEndpoints.end(), endps.begin(), endps.end());
    }
    return expandedEndpoints;
}

#ifdef ICEE_HAS_LOCATOR
void
ObjectAdapter::updateLocatorRegistry(const IceInternal::LocatorInfoPtr& locatorInfo, const Ice::ObjectPrx& proxy)
{
    if(_id.empty())
    {
        return; // Nothing to update.
    }

    //
    // Call on the locator registry outside the synchronization to
    // blocking other threads that need to lock this OA.
    //
    LocatorRegistryPrx locatorRegistry = locatorInfo ? locatorInfo->getLocatorRegistry() : LocatorRegistryPrx();
    if(!locatorRegistry)
    {
        return;
    }

    if(!_id.empty())
    {
        try
        {
            if(_replicaGroupId.empty())
            {
                locatorRegistry->setAdapterDirectProxy(_id, proxy);
            }
            else
            {
                locatorRegistry->setReplicatedAdapterDirectProxy(_id, _replicaGroupId, proxy);
            }
        }
        catch(const AdapterNotFoundException&)
        {
            if(_instance->traceLevels()->location >= 1)
            {
                Trace out(_instance->initializationData().logger, _instance->traceLevels()->locationCat);
                out << "couldn't update object adapter `" + _id + "' endpoints with the locator registry:\n";
                out << "the object adapter is not known to the locator registry";
            }

            NotRegisteredException ex(__FILE__, __LINE__);
            ex.kindOfObject = "object adapter";
            ex.id = _id;
            throw ex;
        }
        catch(const InvalidReplicaGroupIdException&)
        {
            if(_instance->traceLevels()->location >= 1)
            {
                Trace out(_instance->initializationData().logger, _instance->traceLevels()->locationCat);
                out << "couldn't update object adapter `" + _id + "' endpoints with the locator registry:\n";
                out << "the replica group `" << _replicaGroupId << "' is not known to the locator registry";
            }

            NotRegisteredException ex(__FILE__, __LINE__);
            ex.kindOfObject = "replica group";
            ex.id = _replicaGroupId;
            throw ex;
        }
        catch(const AdapterAlreadyActiveException&)
        {
            if(_instance->traceLevels()->location >= 1)
            {
                Trace out(_instance->initializationData().logger, _instance->traceLevels()->locationCat);
                out << "couldn't update object adapter `" + _id + "' endpoints with the locator registry:\n";
                out << "the object adapter endpoints are already set";
            }

            ObjectAdapterIdInUseException ex(__FILE__, __LINE__);
            ex.id = _id;
            throw ex;
        }
        catch(const LocalException& ex)
        {
            if(_instance->traceLevels()->location >= 1)
            {
                Trace out(_instance->initializationData().logger, _instance->traceLevels()->locationCat);
                out << "couldn't update object adapter `" + _id + "' endpoints with the locator registry:\n"
                    << ex.toString();
            }
            throw; // TODO: Shall we raise a special exception instead of a non obvious local exception?
        }

        if(_instance->traceLevels()->location >= 1)
        {
            Trace out(_instance->initializationData().logger, _instance->traceLevels()->locationCat);
            out << "updated object adapter `" + _id + "' endpoints with the locator registry\n";
            out << "endpoints = ";
            vector<EndpointPtr> endpts = proxy ? proxy->__reference()->getEndpoints() : vector<EndpointPtr>();
            for(vector<EndpointPtr>::iterator p = endpts.begin(); p != endpts.end(); ++p)
            {
                if(p != endpts.begin())
                {
                    out << ":";
                }
                out << (*p)->toString();
            }
        }
    }
}
#endif
