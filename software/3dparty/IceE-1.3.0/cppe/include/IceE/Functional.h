// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_FUNCTIONAL_H
#define ICEE_FUNCTIONAL_H

#include <IceE/Handle.h>
#include <functional>

namespace IceUtilInternal
{

// ----------------------------------------------------------------------
// Various function objects that work with handles instead of plain
// pointers.
// ----------------------------------------------------------------------

template<class R, class T, class H>
class MemFun : public std::unary_function<H, R>
{
    typedef R (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit MemFun(MemberFN p) : _mfn(p) { }
    R operator()(H handle) const
    {
        return (handle.get() ->* _mfn)();
    }
};

template<class R, class T, class H, class A>
class MemFun1 : public std::binary_function<H, A, R>
{
    typedef R (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit MemFun1(MemberFN p) : _mfn(p) { }
    R operator()(H handle, A arg) const
    {
        return (handle.get() ->* _mfn)(arg);
    }
};

template<class T, class H>
class VoidMemFun : public std::unary_function<H, void>
{
    typedef void (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit VoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(H handle) const
    {
        (handle.get() ->* _mfn)();
    }
};

template<class T, class H, class A>
class VoidMemFun1 : public std::binary_function<H, A, void>
{
    typedef void (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit VoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(H handle, A arg) const
    {
        (handle.get() ->* _mfn)(arg);
    }
};

template<class R, class K, class T, class H>
class SecondMemFun : public std::unary_function<std::pair<K, H>, R>
{
    typedef R (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit SecondMemFun(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair) const
    {
        return (pair.second.get() ->* _mfn)();
    }
};

template<class R, class K, class T, class H, class A>
class SecondMemFun1 : public std::binary_function<std::pair<K, H>, A, R>
{
    typedef R (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit SecondMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair, A arg) const
    {
        return (pair.second.get() ->* _mfn)(arg);
    }
};

template<class K, class T, class H>
class SecondVoidMemFun : public std::unary_function<std::pair<K, H>, void>
{
    typedef void (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit SecondVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair) const
    {
        (pair.second.get() ->* _mfn)();
    }
};

template<class K, class T, class H, class A>
class SecondVoidMemFun1 : public std::binary_function<std::pair<K, H>, A, void>
{
    typedef void (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit SecondVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair, A arg) const
    {
        (pair.second.get() ->* _mfn)(arg);
    }
};

template<class R, class T, class H>
class ConstMemFun : public std::unary_function<H, R>
{
    typedef R (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit ConstMemFun(MemberFN p) : _mfn(p) { }
    R operator()(H handle) const
    {
        return (handle.get() ->* _mfn)();
    }
};

template<class R, class T, class H, class A>
class ConstMemFun1 : public std::binary_function<H, A, R>
{
    typedef R (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit ConstMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(H handle, A arg) const
    {
        return (handle.get() ->* _mfn)(arg);
    }
};

template<class T, class H>
class ConstVoidMemFun : public std::unary_function<H, void>
{
    typedef void (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit ConstVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(H handle) const
    {
        (handle.get() ->* _mfn)();
    }
};

template<class T, class H, class A>
class ConstVoidMemFun1 : public std::binary_function<H, A, void>
{
    typedef void (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit ConstVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(H handle, A arg) const
    {
        (handle.get() ->* _mfn)(arg);
    }
};

template<class R, class K, class T, class H>
class SecondConstMemFun : public std::unary_function<std::pair<K, H>, R>
{
    typedef R (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit SecondConstMemFun(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair) const
    {
        return (pair.second.get() ->* _mfn)();
    }
};

template<class R, class K, class T, class H, class A>
class SecondConstMemFun1 : public std::binary_function<std::pair<K, H>, A, R>
{
    typedef R (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit SecondConstMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair, A arg) const
    {
        return (pair.second.get() ->* _mfn)(arg);
    }
};

template<class K, class T, class H>
class SecondConstVoidMemFun : public std::unary_function<std::pair<K, H>, void>
{
    typedef void (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit SecondConstVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair) const
    {
        (pair.second.get() ->* _mfn)();
    }
};

template<class K, class T, class H, class A>
class SecondConstVoidMemFun1 : public std::binary_function<std::pair<K, H>, A, void>
{
    typedef void (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit SecondConstVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair, A arg) const
    {
        (pair.second.get() ->* _mfn)(arg);
    }
};

}

// ----------------------------------------------------------------------
// Inline functions that return function objects that work with
// IceUtil::Handle
// ----------------------------------------------------------------------

namespace IceUtil
{

template<class R, class T>
inline ::IceUtilInternal::MemFun<R, T, IceUtil::Handle<T> >
memFun(R (T::*p)(void))
{
    return ::IceUtilInternal::MemFun<R, T, IceUtil::Handle<T> >(p);
}

template<class R, class T, class A>
inline ::IceUtilInternal::MemFun1<R, T, IceUtil::Handle<T>, A>
memFun1(R (T::*p)(A))
{
    return ::IceUtilInternal::MemFun1<R, T, IceUtil::Handle<T>, A>(p);
}

template<class T>
inline ::IceUtilInternal::VoidMemFun<T, IceUtil::Handle<T> >
voidMemFun(void (T::*p)(void))
{
    return ::IceUtilInternal::VoidMemFun<T, IceUtil::Handle<T> >(p);
}

template<class T, class A>
inline ::IceUtilInternal::VoidMemFun1<T, IceUtil::Handle<T>, A>
voidMemFun1(void (T::*p)(A))
{
    return ::IceUtilInternal::VoidMemFun1<T, IceUtil::Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::IceUtilInternal::SecondMemFun<R, K, T, IceUtil::Handle<T> >
secondMemFun(R (T::*p)(void))
{
    return ::IceUtilInternal::SecondMemFun<R, K, T, IceUtil::Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::IceUtilInternal::SecondMemFun1<R, K, T, IceUtil::Handle<T>, A>
secondMemFun1(R (T::*p)(A))
{
    return ::IceUtilInternal::SecondMemFun1<R, K, T, IceUtil::Handle<T>, A>(p);
}

template<class K, class T>
inline ::IceUtilInternal::SecondVoidMemFun<K, T, IceUtil::Handle<T> >
secondVoidMemFun(void (T::*p)(void))
{
    return ::IceUtilInternal::SecondVoidMemFun<K, T, IceUtil::Handle<T> >(p);
}

template<class K, class T, class A>
inline ::IceUtilInternal::SecondVoidMemFun1<K, T, IceUtil::Handle<T>, A>
secondVoidMemFun1(void (T::*p)(A))
{
    return ::IceUtilInternal::SecondVoidMemFun1<K, T, IceUtil::Handle<T>, A>(p);
}

template<class R, class T>
inline ::IceUtilInternal::ConstMemFun<R, T, IceUtil::Handle<T> >
constMemFun(R (T::*p)(void) const)
{
    return ::IceUtilInternal::ConstMemFun<R, T, IceUtil::Handle<T> >(p);
}

template<class R, class T, class A>
inline ::IceUtilInternal::ConstMemFun1<R, T, IceUtil::Handle<T>, A>
constMemFun1(R (T::*p)(A) const)
{
    return ::IceUtilInternal::ConstMemFun1<R, T, IceUtil::Handle<T>, A>(p);
}

template<class T>
inline ::IceUtilInternal::ConstVoidMemFun<T, IceUtil::Handle<T> >
constVoidMemFun(void (T::*p)(void) const)
{
    return ::IceUtilInternal::ConstVoidMemFun<T, IceUtil::Handle<T> >(p);
}

template<class T, class A>
inline ::IceUtilInternal::ConstVoidMemFun1<T, IceUtil::Handle<T>, A>
constVoidMemFun1(void (T::*p)(A) const)
{
    return ::IceUtilInternal::ConstVoidMemFun1<T, IceUtil::Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::IceUtilInternal::SecondConstMemFun<R, K, T, IceUtil::Handle<T> >
secondConstMemFun(R (T::*p)(void) const)
{
    return ::IceUtilInternal::SecondConstMemFun<R, K, T, IceUtil::Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::IceUtilInternal::SecondConstMemFun1<R, K, T, IceUtil::Handle<T>, A>
secondConstMemFun1(R (T::*p)(A) const)
{
    return ::IceUtilInternal::SecondConstMemFun1<R, K, T, IceUtil::Handle<T>, A>(p);
}

template<class K, class T>
inline ::IceUtilInternal::SecondConstVoidMemFun<K, T, IceUtil::Handle<T> >
secondConstVoidMemFun(void (T::*p)(void) const)
{
    return ::IceUtilInternal::SecondConstVoidMemFun<K, T, IceUtil::Handle<T> >(p);
}

template<class K, class T, class A>
inline ::IceUtilInternal::SecondConstVoidMemFun1<K, T, IceUtil::Handle<T>, A>
secondConstVoidMemFun1(void (T::*p)(A) const)
{
    return ::IceUtilInternal::SecondConstVoidMemFun1<K, T, IceUtil::Handle<T>, A>(p);
}

}

// ----------------------------------------------------------------------
// Inline functions that return function objects that work with
// IceInternal::Handle
// ----------------------------------------------------------------------

namespace Ice
{

template<class R, class T>
inline ::IceUtilInternal::MemFun<R, T, ::IceInternal::Handle<T> >
memFun(R (T::*p)(void))
{
    return ::IceUtilInternal::MemFun<R, T, ::IceInternal::Handle<T> >(p);
}

template<class R, class T, class A>
inline ::IceUtilInternal::MemFun1<R, T, ::IceInternal::Handle<T>, A>
memFun1(R (T::*p)(A))
{
    return ::IceUtilInternal::MemFun1<R, T, ::IceInternal::Handle<T>, A>(p);
}

template<class T>
inline ::IceUtilInternal::VoidMemFun<T, ::IceInternal::Handle<T> >
voidMemFun(void (T::*p)(void))
{
    return ::IceUtilInternal::VoidMemFun<T, ::IceInternal::Handle<T> >(p);
}

template<class T, class A>
inline ::IceUtilInternal::VoidMemFun1<T, ::IceInternal::Handle<T>, A>
voidMemFun1(void (T::*p)(A))
{
    return ::IceUtilInternal::VoidMemFun1<T, ::IceInternal::Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::IceUtilInternal::SecondMemFun<R, K, T, ::IceInternal::Handle<T> >
secondMemFun(R (T::*p)(void))
{
    return ::IceUtilInternal::SecondMemFun<R, K, T, ::IceInternal::Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::IceUtilInternal::SecondMemFun1<R, K, T, ::IceInternal::Handle<T>, A>
secondMemFun1(R (T::*p)(A))
{
    return ::IceUtilInternal::SecondMemFun1<R, K, T, ::IceInternal::Handle<T>, A>(p);
}

template<class K, class T>
inline ::IceUtilInternal::SecondVoidMemFun<K, T, ::IceInternal::Handle<T> >
secondVoidMemFun(void (T::*p)(void))
{
    return ::IceUtilInternal::SecondVoidMemFun<K, T, ::IceInternal::Handle<T> >(p);
}

template<class K, class T, class A>
inline ::IceUtilInternal::SecondVoidMemFun1<K, T, ::IceInternal::Handle<T>, A>
secondVoidMemFun1(void (T::*p)(A))
{
    return ::IceUtilInternal::SecondVoidMemFun1<K, T, ::IceInternal::Handle<T>, A>(p);
}

template<class R, class T>
inline ::IceUtilInternal::ConstMemFun<R, T, ::IceInternal::Handle<T> >
constMemFun(R (T::*p)(void) const)
{
    return ::IceUtilInternal::ConstMemFun<R, T, ::IceInternal::Handle<T> >(p);
}

template<class R, class T, class A>
inline ::IceUtilInternal::ConstMemFun1<R, T, ::IceInternal::Handle<T>, A>
constMemFun1(R (T::*p)(A) const)
{
    return ::IceUtilInternal::ConstMemFun1<R, T, ::IceInternal::Handle<T>, A>(p);
}

template<class T>
inline ::IceUtilInternal::ConstVoidMemFun<T, ::IceInternal::Handle<T> >
constVoidMemFun(void (T::*p)(void) const)
{
    return ::IceUtilInternal::ConstVoidMemFun<T, ::IceInternal::Handle<T> >(p);
}

template<class T, class A>
inline ::IceUtilInternal::ConstVoidMemFun1<T, ::IceInternal::Handle<T>, A>
constVoidMemFun1(void (T::*p)(A) const)
{
    return ::IceUtilInternal::ConstVoidMemFun1<T, ::IceInternal::Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::IceUtilInternal::SecondConstMemFun<R, K, T, ::IceInternal::Handle<T> >
secondConstMemFun(R (T::*p)(void) const)
{
    return ::IceUtilInternal::SecondConstMemFun<R, K, T, ::IceInternal::Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::IceUtilInternal::SecondConstMemFun1<R, K, T, ::IceInternal::Handle<T>, A>
secondConstMemFun1(R (T::*p)(A) const)
{
    return ::IceUtilInternal::SecondConstMemFun1<R, K, T, ::IceInternal::Handle<T>, A>(p);
}

template<class K, class T>
inline ::IceUtilInternal::SecondConstVoidMemFun<K, T, ::IceInternal::Handle<T> >
secondConstVoidMemFun(void (T::*p)(void) const)
{
    return ::IceUtilInternal::SecondConstVoidMemFun<K, T, ::IceInternal::Handle<T> >(p);
}

template<class K, class T, class A>
inline ::IceUtilInternal::SecondConstVoidMemFun1<K, T, ::IceInternal::Handle<T>, A>
secondConstVoidMemFun1(void (T::*p)(A) const)
{
    return ::IceUtilInternal::SecondConstVoidMemFun1<K, T, ::IceInternal::Handle<T>, A>(p);
}

}

#endif
