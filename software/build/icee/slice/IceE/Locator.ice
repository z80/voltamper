// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_LOCATOR_ICE
#define ICE_LOCATOR_ICE

#include <IceE/Identity.ice>

module Ice
{

/**
 *
 * This exception is raised if an adapter cannot be found.
 *
 **/
exception AdapterNotFoundException
{
};

/**
 *
 * This exception is raised if the replica group provided by the
 * server is invalid.
 *
 **/
exception InvalidReplicaGroupIdException
{
};

/**
 *
 * This exception is raised if a server tries to set endpoints for
 * an adapter that is already active.
 *
 **/
exception AdapterAlreadyActiveException
{
};

/**
 *
 * This exception is raised if an object cannot be found.
 *
 **/
exception ObjectNotFoundException
{
};

/**
 *
 * This exception is raised if a server cannot be found.
 *
 **/
exception ServerNotFoundException
{
};

interface LocatorRegistry;

/**
 *
 * The &Ice; locator interface. This interface is used by clients to
 * lookup adapters and objects. It is also used by servers to get the
 * locator registry proxy.
 *
 * <note><para> The [Locator] interface is intended to be used by
 * &Ice; internals and by locator implementations. Regular user code
 * should not attempt to use any functionality of this interface
 * directly.</para></note>
 *
 **/
interface Locator
{
    /**
     *
     * Find an object by identity and return its proxy.
     *
     * @param id The identity.
     *
     * @return The proxy, or null if the object is not active.
     *
     * @throws ObjectNotFoundException Raised if the object cannot
     * be found.
     *
     **/
    ["ami", "nonmutating", "cpp:const"] idempotent Object* findObjectById(Ice::Identity id)
        throws ObjectNotFoundException;

    /**
     *
     * Find an adapter by id and return its proxy (a dummy direct
     * proxy created by the adapter).
     *
     * @param id The adapter id.
     *
     * @return The adapter proxy, or null if the adapter is not active.
     * 
     * @throws AdapterNotFoundException Raised if the adapter cannot be
     * found.
     *
     **/
    ["ami", "nonmutating", "cpp:const"] idempotent Object* findAdapterById(string id)
        throws AdapterNotFoundException;

    /**
     *
     * Get the locator registry.
     *
     * @return The locator registry.
     *
     **/
    ["nonmutating", "cpp:const"] idempotent LocatorRegistry* getRegistry();
};

/**
 *
 * The &Ice; locator registry interface. This interface is used by
 * servers to register adapter endpoints with the locator.
 *
 * <note><para> The [LocatorRegistry] interface is intended to be used
 * by &Ice; internals and by locator implementations. Regular user
 * code should not attempt to use any functionality of this interface
 * directly.</para></note>
 *
 **/
interface LocatorRegistry
{
    /**
     *
     * Set the adapter endpoints with the locator registry.
     *
     * @param id The adapter id.
     *
     * @param proxy The adapter proxy (a dummy direct proxy created
     * by the adapter). The direct proxy contains the adapter
     * endpoints.
     *
     * @throws AdapterNotFoundException Raised if the adapter cannot
     * be found, or if the locator only allows
     * registered adapters to set their active proxy and the
     * adapter is not registered with the locator.
     *
     * @throws AdapterAlreadyActive Raised if an adapter with the same
     * id is already active.
     *
     **/
    idempotent void setAdapterDirectProxy(string id, Object* proxy)
        throws AdapterNotFoundException, AdapterAlreadyActiveException;

    /**
     *
     * Set the adapter endpoints with the locator registry.
     *
     * @param adapterId The adapter id.
     *
     * @param replicaGroupId The replica group id.
     *
     * @param proxy The adapter proxy (a dummy direct proxy created
     * by the adapter). The direct proxy contains the adapter
     * endpoints.
     *
     * @throws AdapterNotFoundException Raised if the adapter cannot
     * be found, or if the locator only allows registered adapters to
     * set their active proxy and the adapter is not registered with
     * the locator.
     *
     * @throws AdapterAlreadyActive Raised if an adapter with the same
     * id is already active.
     *
     * @throws InvalidReplicaGroupIdException Raised if the given
     * replica group doesn't match the one registered with the
     * locator registry for this object adapter.
     *
     **/
    idempotent void setReplicatedAdapterDirectProxy(string adapterId, string replicaGroupId, Object* proxy)
        throws AdapterNotFoundException, AdapterAlreadyActiveException, InvalidReplicaGroupIdException;
};

};

#endif
