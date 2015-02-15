#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice-E is licensed to you under the terms described in the
# ICEE_LICENSE file included in this distribution.
#
# **********************************************************************

import os, sys

path = [ ".", "..", "../..", "../../..", "../../../.." ]
head = os.path.dirname(sys.argv[0])
if len(head) > 0:
    path = [os.path.join(head, p) for p in path]
path = [os.path.abspath(p) for p in path if os.path.exists(os.path.join(p, "scripts", "TestUtil.py")) ]
if len(path) == 0:
    raise "can't find toplevel directory!"
sys.path.append(os.path.join(path[0]))
from scripts import *

server = os.path.join(os.getcwd(), "server")
client = os.path.join(os.getcwd(), "client")

num = 12
base = 12340

serverProc = []
for i in range(0, num):
    print "starting server #%d..." % (i + 1),
    serverProc.append(TestUtil.startServer(server, "%d" % (base + i)))
    print "ok"

ports = ""
for i in range(0, num):
    ports = "%s %d" % (ports, base + i)

print "starting client...",
clientProc = TestUtil.startClient(client, ports)
print "ok"

clientProc.waitTestSuccess()
for p in serverProc:
    p.waitTestSuccess()
