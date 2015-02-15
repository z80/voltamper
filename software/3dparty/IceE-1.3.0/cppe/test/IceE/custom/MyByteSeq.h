// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef TEST_MY_BYTE_SEQ_H
#define TEST_MY_BYTE_SEQ_H

#include <IceE/Config.h>

class MyByteSeq
{
public:

    typedef Ice::Byte* iterator;
    typedef Ice::Byte* const_iterator;

    MyByteSeq();
    MyByteSeq(size_t);
    MyByteSeq(const MyByteSeq&);
    ~MyByteSeq();

    size_t size() const;
    void swap(MyByteSeq&);
    const_iterator begin() const;
    const_iterator end() const;
    void operator=(const MyByteSeq&);
    bool operator==(const MyByteSeq&) const; 

private:

    size_t _size;
    Ice::Byte* _data;
};

#endif
