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
using namespace Demo;

ThroughputI::ThroughputI(int reduce) :
    _byteSeq(ByteSeqSize / reduce, 0),
    _stringSeq(StringSeqSize / reduce, "hello"),
    _structSeq(StringDoubleSeqSize / reduce),
    _fixedSeq(FixedSeqSize / reduce),
    _warmup(false)
{
    int i;
    for(i = 0; i < StringDoubleSeqSize / reduce; ++i)
    {
        _structSeq[i].s = "hello";
        _structSeq[i].d = 3.14;
    }
    for(i = 0; i < FixedSeqSize / reduce; ++i)
    {
        _fixedSeq[i].i = 0;
        _fixedSeq[i].j = 0;
        _fixedSeq[i].d = 0;
    }
}

bool
ThroughputI::needsWarmup(const Ice::Current&)
{
    _warmup = false;
    return false;
}

void
ThroughputI::startWarmup(const Ice::Current&)
{
    _warmup = true;
}

void
ThroughputI::endWarmup(const Ice::Current&)
{
    _warmup = false;
}

void
ThroughputI::sendByteSeq(const pair<const Ice::Byte*, const Ice::Byte*>&, const Ice::Current&)
{
}

ByteSeq
ThroughputI::recvByteSeq(const Ice::Current&)
{
    if(_warmup)
    {
        return Demo::ByteSeq();
    }
    else
    {
        return _byteSeq;
    }
}

ByteSeq
ThroughputI::echoByteSeq(const ByteSeq& seq, const Ice::Current&)
{
    return seq;
}

void
ThroughputI::sendStringSeq(const StringSeq&, const Ice::Current&)
{
}

StringSeq
ThroughputI::recvStringSeq(const Ice::Current&)
{
    if(_warmup)
    {
        return Demo::StringSeq();
    }
    else
    {
        return _stringSeq;
    }
}

StringSeq
ThroughputI::echoStringSeq(const StringSeq& seq, const Ice::Current&)
{
    return seq;
}

void
ThroughputI::sendStructSeq(const StringDoubleSeq&, const Ice::Current&)
{
}

StringDoubleSeq
ThroughputI::recvStructSeq(const Ice::Current&)
{
    if(_warmup)
    {
        return Demo::StringDoubleSeq();
    }
    else
    {
        return _structSeq;
    }
}

StringDoubleSeq
ThroughputI::echoStructSeq(const StringDoubleSeq& seq, const Ice::Current&)
{
    return seq;
}

void
ThroughputI::sendFixedSeq(const FixedSeq&, const Ice::Current&)
{
}

FixedSeq
ThroughputI::recvFixedSeq(const Ice::Current&)
{
    if(_warmup)
    {
        return Demo::FixedSeq();
    }
    else
    {
        return _fixedSeq;
    }
}

FixedSeq
ThroughputI::echoFixedSeq(const FixedSeq& seq, const Ice::Current&)
{
    return seq;
}

void
ThroughputI::shutdown(const Ice::Current& c)
{
    c.adapter->getCommunicator()->shutdown();
}
