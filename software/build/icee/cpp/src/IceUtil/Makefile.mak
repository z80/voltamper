# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

LIBNAME		= $(top_srcdir)\lib\iceutil$(LIBSUFFIX).lib
DLLNAME         = $(top_srcdir)\bin\iceutil$(SOVERSION)$(LIBSUFFIX).dll

TARGETS		= $(LIBNAME) $(DLLNAME)

OBJS		= ArgVector.obj \
                  Cond.obj \
                  ConvertUTF.obj \
		  CountDownLatch.obj \
		  CtrlCHandler.obj \
		  Exception.obj \
		  FileUtil.obj \
		  InputUtil.obj \
		  Options.obj \
		  OutputUtil.obj \
		  Random.obj \
		  RWRecMutex.obj \
		  RecMutex.obj \
		  Shared.obj \
		  StaticMutex.obj \
		  StringUtil.obj \
		  Thread.obj \
		  ThreadException.obj \
		  Time.obj \
		  Timer.obj \
		  UUID.obj \
		  Unicode.obj

SRCS		= $(OBJS:.obj=.cpp)

!include $(top_srcdir)/config/Make.rules.mak

CPPFLAGS        = $(CPPFLAGS) -DICE_UTIL_API_EXPORTS -I.. -DWIN32_LEAN_AND_MEAN

!if "$(GENERATE_PDB)" == "yes"
PDBFLAGS	= /pdb:$(DLLNAME:.dll=.pdb)
!endif

!if "$(CPP_COMPILER)" == "BCC2007"
RES_FILE	= ,, IceUtil.res
!else
RES_FILE	= IceUtil.res
!endif

!if "$(STATICLIBS)" == "yes"

$(DLLNAME):

$(LIBNAME): $(OBJS)
	$(AR) $(ARFLAGS) $(PDBFLAGS) $(OBJS) $(PREOUT)$@

!else

$(LIBNAME): $(DLLNAME)

$(DLLNAME): $(OBJS) IceUtil.res
	$(LINK) $(LD_DLLFLAGS) $(PDBFLAGS) $(OBJS) $(PREOUT)$@ $(PRELIBS)$(ICE_OS_LIBS) $(RES_FILE)
	move $(DLLNAME:.dll=.lib) $(LIBNAME)
	@if exist $@.manifest echo ^ ^ ^ Embedding manifest using $(MT) && \
	    $(MT) -nologo -manifest $@.manifest -outputresource:$@;#2 && del /q $@.manifest
	@if exist $(DLLNAME:.dll=.exp) del /q $(DLLNAME:.dll=.exp)

!endif

clean::
	-del /q IceUtil.res

install:: all
#	copy $(LIBNAME) $(install_libdir)
#	copy $(DLLNAME) $(install_bindir)


!if "$(CPP_COMPILER)" == "BCC2007" && "$(OPTIMIZE)" != "yes"

install:: all
#	copy $(DLLNAME:.dll=.tds) $(install_bindir)

!elseif "$(GENERATE_PDB)" == "yes"

install:: all
#	copy $(DLLNAME:.dll=.pdb) $(install_bindir)

!endif

!include .depend
