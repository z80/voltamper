// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef VALUE_ICE
#define VALUE_ICE

module Demo
{

class Simple
{
    string message;
};

class Printer
{
    string message;
    void printBackwards();
};

class DerivedPrinter extends Printer
{
    string derivedMessage;
    void printUppercase();
};

exception DerivedPrinterException
{
    DerivedPrinter derived;
};

interface Initial
{
    Simple getSimple();
    void getPrinter(out Printer impl, out Printer* proxy);
    Printer getDerivedPrinter();
    void throwDerivedPrinter() throws DerivedPrinterException;
    void shutdown();
};

};

#endif
