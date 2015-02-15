// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_UNDEF_SYS_MACROS_H
#define ICEE_UNDEF_SYS_MACROS_H

//
// This header includes macros that can end up being dragged into
// the generated code from system headers, such as major() or NDEBUG.
// If a Slice symbol has the same name as a macro, the generated
// code most likely won't compile (but, depending how the macro is
// defined, may even compile).
//
// Here, we undefine symbols that cause such problems.
//

#undef major
#undef minor
#undef min
#undef max

#endif
