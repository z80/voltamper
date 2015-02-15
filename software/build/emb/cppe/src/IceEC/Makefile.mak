# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice-E is licensed to you under the terms described in the
# ICEE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

LIBNAME		= $(top_srcdir)\lib\iceec$(LIBSUFFIX).lib
DLLNAME		= $(top_srcdir)\bin\iceec$(SOVERSION)$(LIBSUFFIX).dll

TARGETS		= $(LIBNAME) $(DLLNAME)

TRANSPORT_DIR   = $(top_srcdir)\src\TcpTransport
ICEE_DIR   	= $(top_srcdir)\src\IceE

TRANSPORT_OBJS  = Connector.obj \
                  EndpointFactory.obj \
                  TcpEndpoint.obj \
                  Transceiver.obj

ICEE_OBJS      	= Base64.obj \
		  BasicStream.obj \
                  Buffer.obj \
                  BuiltinSequences.obj \
                  Communicator.obj \
                  Cond.obj \
                  ConnectionI.obj \
		  ConnectRequestHandler.obj \
                  ConvertUTF.obj \
                  DefaultsAndOverrides.obj \
                  Endpoint.obj \
		  EventHandler.obj \
                  ExceptionBase.obj \
                  FactoryTable.obj \
                  FactoryTableDef.obj \
                  Identity.obj \
                  Initialize.obj \
                  Instance.obj \
                  LocalException.obj \
                  Locator.obj \
                  LocatorInfo.obj \
                  Logger.obj \
                  LoggerI.obj \
                  LoggerUtil.obj \
		  MutexProtocol.obj \
                  Network.obj \
		  ObjectFactoryManager.obj \
		  ObjectFactoryManagerI.obj \
                  OperationMode.obj \
                  Outgoing.obj \
		  OutgoingAsync.obj \
		  Object.obj \
                  OutgoingConnectionFactory.obj \
                  Properties.obj \
                  Protocol.obj \
                  Proxy.obj \
                  ProxyFactory.obj \
		  Random.obj \
                  RecMutex.obj \
                  Reference.obj \
                  ReferenceFactory.obj \
		  RetryQueue.obj \
		  RequestHandler.obj \
                  Router.obj \
                  RouterInfo.obj \
                  SafeStdio.obj \
		  SelectorThread.obj \
                  Shared.obj \
                  StringConverter.obj \
                  StringUtil.obj \
                  Thread.obj \
                  ThreadException.obj \
		  ThreadPool.obj \
                  Time.obj \
		  Timer.obj \
                  TraceLevels.obj \
                  TraceUtil.obj \
                  UnknownEndpoint.obj \
                  Unicode.obj

HDIR		= $(headerdir)\IceE
SDIR		= $(slicedir)\IceE

!include $(top_srcdir)\config\Make.rules.mak

CPPFLAGS	= -I.. $(CPPFLAGS) -DICE_API_EXPORTS -DFD_SETSIZE=1024 -DICEE_PURE_CLIENT -DWIN32_LEAN_AND_MEAN
SLICE2CPPEFLAGS = --ice --include-dir IceE --dll-export ICE_API $(SLICE2CPPEFLAGS)

!if "$(STATICLIBS)" != "yes" && "$(OPTIMIZE_SPEED)" != "yes" && "$(OPTIMIZE_SIZE)" != "yes"
PDBFLAGS        = /pdb:$(DLLNAME:.dll=.pdb)
!endif

{$(SDIR)\}.ice{$(HDIR)}.h:
	del /q $(HDIR)\$(*F).h $(ICEE_DIR)\$(*F).cpp 
	$(SLICE2CPPE) $(SLICE2CPPEFLAGS) $< 
	move $(*F).h $(HDIR)
	move $(*F).cpp $(ICEE_DIR)

{$(TRANSPORT_DIR)\}.cpp.obj::
    $(CXX) /c $(CPPFLAGS) $(CXXFLAGS) $<

{$(ICEE_DIR)\}.cpp.obj::
    $(CXX) /c $(CPPFLAGS) $(CXXFLAGS) $<

!if "$(STATICLIBS)" == "yes"

$(DLLNAME):

$(LIBNAME): $(ICEE_OBJS) $(TRANSPORT_OBJS)
	$(AR) $(ARFLAGS) $(PDBFLAGS) $(ICEE_OBJS) $(TRANSPORT_OBJS) /out:$(LIBNAME)

!else

$(LIBNAME): $(DLLNAME)

$(DLLNAME): $(ICEE_OBJS) $(TRANSPORT_OBJS)
	$(LINK) $(LDFLAGS) /dll $(PDBFLAGS) $(ICEE_OBJS) $(TRANSPORT_OBJS) /out:$(DLLNAME) $(BASELIBS)
	move $(DLLNAME:.dll=.lib) $(LIBNAME)
	@if exist $@.manifest echo ^ ^ ^ Embedding manifest using $(MT) && \
	    $(MT) -nologo -manifest $@.manifest -outputresource:$@;#2 && del /q $@.manifest
	@if exist $(DLLNAME:.dll=.exp) del /q $(DLLNAME:.dll=.exp)

!endif

clean::
	del /q $(LIBNAME:.lib=.*)

install:: all
	copy $(LIBNAME) $(install_libdir)

!if "$(STATICLIBS)" != "yes"

clean::
	del /q $(DLLNAME:.dll=.*)

install:: all
	copy $(DLLNAME) $(install_bindir)

!endif

!include .depend
