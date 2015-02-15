# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

!include $(top_srcdir)/config/Make.rules.mak

install::
	@if not exist $(install_includedir)\IceUtil \
	    @echo "Creating $(install_includedir)\IceUtil..." && \
	    mkdir $(install_includedir)\IceUtil

	@for %i in ( *.h ) do \
	    @echo Installing %i && \
	    copy %i $(install_includedir)\IceUtil
