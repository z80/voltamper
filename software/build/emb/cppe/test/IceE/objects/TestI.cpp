// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include <TestI.h>
#include <TestCommon.h>

using namespace Test;

BI::BI() :
    _postUnmarshalInvoked(false)
{
}

bool
BI::postUnmarshalInvoked(const Ice::Current&)
{
    return _postUnmarshalInvoked;
}

void
BI::ice_preMarshal()
{
    preMarshalInvoked = true;
}

void
BI::ice_postUnmarshal()
{
    _postUnmarshalInvoked = true;
}

CI::CI() :
    _postUnmarshalInvoked(false)
{
}

bool
CI::postUnmarshalInvoked(const Ice::Current&)
{
    return _postUnmarshalInvoked;
}

void
CI::ice_preMarshal()
{
    preMarshalInvoked = true;
}

void
CI::ice_postUnmarshal()
{
    _postUnmarshalInvoked = true;
}

DI::DI() :
    _postUnmarshalInvoked(false)
{
}

bool
DI::postUnmarshalInvoked(const Ice::Current&)
{
    return _postUnmarshalInvoked;
}

void
DI::ice_preMarshal()
{
    preMarshalInvoked = true;
}

void
DI::ice_postUnmarshal()
{
    _postUnmarshalInvoked = true;
}

EI::EI() :
    E(1, "hello")
{
}

bool
EI::checkValues(const Ice::Current&)
{
    return i == 1 && s == "hello";
}

FI::FI()
{
}

FI::FI(const EPtr& e) :
    F(e, e)
{
}

bool
FI::checkValues(const Ice::Current&)
{
    return e1 && e1 == e2;
}

#ifdef ICEE_PURE_CLIENT
InitialI::InitialI() :
#else
InitialI::InitialI(const Ice::ObjectAdapterPtr& adapter) :
    _adapter(adapter),
#endif
    _b1(new BI),
    _b2(new BI),
    _c(new CI),
    _d(new DI),
    _e(new EI),
    _f(new FI(_e))
{
    _b1->theA = _b2; // Cyclic reference to another B
    _b1->theB = _b1; // Self reference.
    _b1->theC = 0; // Null reference.

    _b2->theA = _b2; // Self reference, using base.
    _b2->theB = _b1; // Cyclic reference to another B
    _b2->theC = _c; // Cyclic reference to a C.

    _c->theB = _b2; // Cyclic reference to a B.

    _d->theA = _b1; // Reference to a B.
    _d->theB = _b2; // Reference to a B.
    _d->theC = 0; // Reference to a C.
}

void
InitialI::shutdown(const Ice::Current&)
{
#ifndef ICEE_PURE_CLIENT
    _adapter->getCommunicator()->shutdown();
#ifdef _WIN32_WCE
    tprintf("The server has shutdown, close the window to terminate the server.");
#endif
#endif
}

BPtr
InitialI::getB1(const Ice::Current&)
{
    _b1->preMarshalInvoked = false;
    _b2->preMarshalInvoked = false;
    _c->preMarshalInvoked = false;
    return _b1;
}

BPtr
InitialI::getB2(const Ice::Current&)
{
    _b1->preMarshalInvoked = false;
    _b2->preMarshalInvoked = false;
    _c->preMarshalInvoked = false;
    return _b2;
}

CPtr
InitialI::getC(const Ice::Current&)
{
    _b1->preMarshalInvoked = false;
    _b2->preMarshalInvoked = false;
    _c->preMarshalInvoked = false;
    return _c;
}

DPtr
InitialI::getD(const Ice::Current&)
{
    _b1->preMarshalInvoked = false;
    _b2->preMarshalInvoked = false;
    _c->preMarshalInvoked = false;
    _d->preMarshalInvoked = false;
    return _d;
}

EPtr
InitialI::getE(const Ice::Current&)
{
    return _e;
}

FPtr
InitialI::getF(const Ice::Current&)
{
    return _f;
}

void
InitialI::getAll(BPtr& b1, BPtr& b2, CPtr& c, DPtr& d, const Ice::Current&)
{
    _b1->preMarshalInvoked = false;
    _b2->preMarshalInvoked = false;
    _c->preMarshalInvoked = false;
    _d->preMarshalInvoked = false;
    b1 = _b1;
    b2 = _b2;
    c = _c;
    d = _d;
}

IPtr
InitialI::getI(const Ice::Current&)
{
    return new II();
}

void
InitialI::setI(const IPtr&, const Ice::Current&)
{
}


IPtr
InitialI::getJ(const Ice::Current&)
{
    return new JI();
}

IPtr
InitialI::getH(const Ice::Current&)
{
    return new HI();
}
