# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice-E is licensed to you under the terms described in the
# ICEE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

!include $(top_srcdir)\config\Make.rules.mak

SUBDIRS		= proxy \
		  binding \
		  defaultServant \
		  objects \
                  operations \
		  exceptions \
		  inheritance \
		  interceptor \
		  facets \
		  location \
		  slicing \
		  custom \
		  retry \
		  thread \
		  priority \
		  threadPoolPriority \
		  timeout \
		  uuid

!if "$(WINDOWS_MOBILE_SDK)" != "yes"
SUBDIRS		= $(SUBDIRS) \
		  faultTolerance \
		  adapterDeactivation \
!endif

$(EVERYTHING)::
	@for %i in ( $(SUBDIRS) ) do \
	    @echo "making $@ in %i" && \
	    cmd /c "cd %i && $(MAKE) -nologo -f Makefile.mak $@" || exit 1
