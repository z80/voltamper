// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_EXCEPTION_BASE_H
#define ICEE_EXCEPTION_BASE_H

#include <IceE/Config.h>
#include <ostream>

namespace IceUtil
{

class ICE_API Exception : public std::exception
{
public:

    Exception();
    Exception(const char*, int);
    virtual ~Exception() throw();
    virtual std::string ice_name() const;
    virtual std::string toString() const;
    virtual const char* what() const throw();
    virtual Exception* ice_clone() const;
    virtual void ice_throw() const;
    const char* ice_file() const;
    int ice_line() const;
    
private:
    
    const char* _file;
    int _line;
    static const char* _name;
    mutable std::string _str; // Initialized lazily in what().
};

inline std::ostream& operator<<(std::ostream& os, const Exception& ex)
{
    return os << ex.toString();
}

class ICE_API NullHandleException : public Exception
{
public:
    
    NullHandleException(const char*, int);
    virtual ~NullHandleException() throw();
    virtual std::string ice_name() const;
    virtual Exception* ice_clone() const;
    virtual void ice_throw() const;

private:

    static const char* _name;
};

class ICE_API IllegalArgumentException : public Exception
{
public:

    IllegalArgumentException(const char*, int);
    IllegalArgumentException(const char*, int, const std::string&);
    virtual ~IllegalArgumentException() throw();
    virtual std::string ice_name() const;
    virtual Exception* ice_clone() const;
    virtual void ice_throw() const;

    std::string reason;

private:

    static const char* _name;
};

class ICE_API SyscallException : public Exception
{
public:

    SyscallException(const char*, int, int);
    virtual std::string ice_name() const;
    virtual std::string toString() const;
    virtual Exception* ice_clone() const;
    virtual void ice_throw() const;

    int error() const;

private:

    const int _error;
    static const char* _name;
};

}

#endif
