// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/IceE.h>
#include <InitialI.h>
#include <ValueI.h>

using namespace std;
using namespace Demo;

InitialI::InitialI(const Ice::ObjectAdapterPtr& adapter) :
    _simple(new Simple),
    _printer(new PrinterI),
    _printerProxy(PrinterPrx::uncheckedCast(adapter->addWithUUID(_printer))),
    _derivedPrinter(new DerivedPrinterI)
{
    _simple->message = "a message 4 u";
    _printer->message = "Ice rulez!";
    _derivedPrinter->message = _printer->message;
    _derivedPrinter->derivedMessage = "a derived message 4 u";
}

SimplePtr
InitialI::getSimple(const Ice::Current&)
{
    return _simple;
}

void
InitialI::getPrinter(PrinterPtr& impl, PrinterPrx& proxy, const Ice::Current&)
{
    impl = _printer;
    proxy = _printerProxy;
}

PrinterPtr
InitialI::getDerivedPrinter(const Ice::Current&)
{
    return _derivedPrinter;
}

void
InitialI::throwDerivedPrinter(const Ice::Current&)
{
    DerivedPrinterException ex;
    ex.derived = _derivedPrinter;
    throw ex;
}

void
InitialI::shutdown(const Ice::Current& current)
{
    current.adapter->getCommunicator()->shutdown();
}
