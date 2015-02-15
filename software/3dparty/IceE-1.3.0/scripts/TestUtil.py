# **********************************************************************
#
# Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import sys, os, re, errno, getopt, time, StringIO, string, copy
from threading import Thread

# Global flags and their default values.
protocol = ""                   # If unset, default to TCP. Valid values are "tcp" or "ssl".
compress = False                # Set to True to enable bzip2 compression.
serialize = False               # Set to True to have tests use connection serialization
host = "127.0.0.1"              # Default to loopback.
debug = False                   # Set to True to enable test suite debugging.
mono = False                    # Set to True when not on Windows
keepGoing = False               # Set to True to have the tests continue on failure.
ipv6 = False                    # Default to use IPv4 only
iceHome = None                  # Binary distribution to use (None to use binaries from source distribution)
x64 = False                     # Binary distribution is 64-bit
java2 = False                   # Use Java 2 jar file from binary distribution
javaCmd = "java"                # Default java loader
valgrind = False                # Set to True to use valgrind for C++ executables.
tracefile = None
cross = []

def isCygwin():
    # The substring on sys.platform is required because some cygwin
    # versions return variations like "cygwin_nt-4.01".
    return sys.platform[:6] == "cygwin"

def isWin32():
    return sys.platform == "win32" or isCygwin()

def isVista():
    return isWin32() and sys.getwindowsversion()[0] == 6

def isWin9x():
    if isWin32():
        return not (os.environ.has_key("OS") and os.environ["OS"] == "Windows_NT")
    else:
        return 0

def isSolaris():
    return sys.platform == "sunos5"
       
def isSparc():
    p = os.popen("uname -m")
    l = p.readline().strip()
    p.close()
    if l == "sun4u":
        return True
    else:
        return False

def isHpUx():
   return sys.platform == "hp-ux11"

def isAIX():
   return sys.platform in ['aix4', 'aix5']
  
def isDarwin():
   return sys.platform == "darwin"

def isLinux():
    return sys.platform.startswith("linux")

#
# The PHP interpreter is called "php5" on some platforms (e.g., SLES).
#
phpCmd = "php"
for path in string.split(os.environ["PATH"], os.pathsep):
    #
    # Stop if we find "php" in the PATH first.
    #
    if os.path.exists(os.path.join(path, "php")):
        break
    elif os.path.exists(os.path.join(path, "php5")):
        phpCmd = "php5"
        break

#
# This is set by the choice of init method. If not set, before it is
# used, it indicates a bug and things should terminate.
#
defaultMapping = None

testErrors = []

toplevel = None 

path = [ ".", "..", "../..", "../../..", "../../../..", "../../../../.." ]
head = os.path.dirname(sys.argv[0])
if len(head) > 0:
    path = [os.path.join(head, p) for p in path]
path = [os.path.abspath(p) for p in path if os.path.exists(os.path.join(p, "scripts", "TestUtil.py")) ]
if len(path) == 0:
    raise "can't find toplevel directory!"
toplevel = path[0]

def sanitize(cp):
    np = ""
    for p in cp.split(os.pathsep):
        if p == "classes":
            continue
        if len(np) > 0:
            np = np + os.pathsep
        np = np + p
    return np
        
def configurePaths():
    if iceHome:
        print "*** using Ice installation from " + iceHome,
        if x64:
            print "(64bit)",
        print

    # First sanitize the environment.
    os.environ["CLASSPATH"] = sanitize(os.getenv("CLASSPATH", ""))

    #
    # If Ice is installed from RPMs, just set the CLASSPATH for Java.
    #
    if iceHome == "/usr":
        javaDir = os.path.join("/", "usr", "share", "java")
        if java2:
            addClasspath(os.path.join(javaDir, "Ice-java2.jar"))
        else:
            addClasspath(os.path.join(javaDir, "Ice.jar"))
        return # That's it, we're done!
    
    if isWin32():
        libDir = getCppBinDir()
    else:
        libDir = os.path.join(getIceDir("cpp"), "lib")
        if iceHome and x64: 
            if isHpUx():
                libDir = os.path.join(libDir, "pa20_64")
	    elif isSolaris():
		if isSparc():
		    libDir = os.path.join(libDir, "sparcv9")
		else:
		    libDir = os.path.join(libDir, "amd64")
	    else:
		libDir = libDir + "64"
    addLdPath(libDir)

    javaDir = os.path.join(getIceDir("java"), "lib")
    if iceHome and java2:
        addClasspath(os.path.join(javaDir, "java2", "Ice.jar"))
    else:
        addClasspath(os.path.join(javaDir, "Ice.jar"))
    addClasspath(os.path.join(javaDir))
    
    # 
    # On Windows, C# assemblies are found thanks to the .exe.config files.
    #
    if not isWin32():
        os.environ["MONO_PATH"] = os.path.join(getIceDir("cs"), "bin") + os.pathsep + os.getenv("MONO_PATH", "")
        
    #
    # On Windows x64, set PYTHONPATH to python/x64.
    #
    pythonDir = os.path.join(getIceDir("py"), "python")
    if isWin32() and x64:
        os.environ["PYTHONPATH"] = os.path.join(pythonDir, "x64") + os.pathsep + os.getenv("PYTHONPATH", "")
    else:
        os.environ["PYTHONPATH"] = pythonDir + os.pathsep + os.getenv("PYTHONPATH", "")

    rubyDir = os.path.join(getIceDir("rb"), "ruby")
    os.environ["RUBYLIB"] = rubyDir + os.pathsep + os.getenv("RUBYLIB", "")

def configureEmbeddedPaths():
    if iceHome:
        print "*** using Ice-E installation from " + iceHome,
        if x64:
            print "(64bit)",
        print

    if isWin32():
        libDir = getCppBinDir()
    else:
        libDir = os.path.join(getIceDir("cppe"), "lib")
        if iceHome and x64: 
            if isHpUx():
                libDir = os.path.join(libDir, "pa20_64")
	    elif isSolaris():
		if isSparc():
		    libDir = os.path.join(libDir, "sparcv9")
		else:
		    libDir = os.path.join(libDir, "amd64")
	    else:
		libDir = libDir + "64"
    addLdPath(libDir)

def addLdPath(libpath, env = None):
    if env is None:
        env = os.environ
    if isWin32():
        env["PATH"] = libpath + os.pathsep + env.get("PATH", "")
    elif isHpUx():
        env["SHLIB_PATH"] = libpath + os.pathsep + env.get("SHLIB_PATH", "")
        env["LD_LIBRARY_PATH"] = libpath + os.pathsep + env.get("LD_LIBRARY_PATH", "")
    elif isDarwin():
        env["DYLD_LIBRARY_PATH"] = libpath + os.pathsep + env.get("DYLD_LIBRARY_PATH", "")
    elif isAIX():
        env["LIBPATH"] = libpath + os.pathsep + env.get("LIBPATH", "")
    else:
        env["LD_LIBRARY_PATH"] = libpath + os.pathsep + env.get("LD_LIBRARY_PATH", "")
        env["LD_LIBRARY_PATH_64"] = libpath + os.pathsep + env.get("LD_LIBRARY_PATH_64", "")
    return env

def addClasspath(dir, env = None):
    if env is None:
        env = os.environ
    env["CLASSPATH"] = dir + os.pathsep + env.get("CLASSPATH", "")
    return env

# List of supported cross languages test.
crossTests = [
               "Ice/adapterDeactivation",
               "Ice/background",
               "Ice/binding",
               "Ice/checksum",
               #"Ice/custom",
               "Ice/exceptions",
               "Ice/facets",
               "Ice/hold",
               "Ice/inheritance",
               "Ice/location",
               "Ice/objects",
               "Ice/operations",
               "Ice/proxy",
               "Ice/retry",
               #"Ice/servantLocator",
               "Ice/timeout",
               "Ice/slicing/exceptions",
               "Ice/slicing/objects",
               ]
    
def run(tests, root = False):
    def usage():
        if getDefaultMapping() == "cppe":
            print "usage: " + sys.argv[0] + """
          --all                   Run all sensible permutations of the tests.
          --start=index           Start running the tests at the given index.
          --loop                  Run the tests in a loop.
          --filter=<regex>        Run all the tests that match the given regex.
          --rfilter=<regex>       Run all the tests that do not match the given regex.
          --debug                 Display debugging information on each test.
          --host=host             Set --Ice.Default.Host=<host>.
          --continue              Keep running when a test fails.
          --ice-home=<path>       Use the binary distribution from the given path.
          --x64                   Binary distribution is 64-bit.
          --cross=lang            Run cross language test.
          --script                Generate a script to run the tests.
            """
        else:
            print "usage: " + sys.argv[0] + """
          --all                   Run all sensible permutations of the tests.
          --all-cross             Run all sensible permutations of cross language tests.
          --start=index           Start running the tests at the given index.
          --loop                  Run the tests in a loop.
          --filter=<regex>        Run all the tests that match the given regex.
          --rfilter=<regex>       Run all the tests that do not match the given regex.
          --debug                 Display debugging information on each test.
          --protocol=tcp|ssl      Run with the given protocol.
          --compress              Run the tests with protocol compression.
          --host=host             Set --Ice.Default.Host=<host>.
          --valgrind              Run the test with valgrind.
          --serialize             Run with connection serialization.
          --continue              Keep running when a test fails
          --ipv6                  Use IPv6 addresses.
          --ice-home=<path>       Use the binary distribution from the given path.
          --x64                   Binary distribution is 64-bit.
          --java2                 Use Java 2 jar file.
          --cross=lang            Run cross language test.
          --script                Generate a script to run the tests.
            """
        sys.exit(2)

    try:
        if getDefaultMapping() == "cppe":
            opts, args = getopt.getopt(sys.argv[1:], "lr:R:",
                                   ["start=", "start-after=", "filter=", "rfilter=", "all", "loop", "debug",
                                    "host=", "continue", "ice-home=", "x64", "cross=", "script"])
        else:
            opts, args = getopt.getopt(sys.argv[1:], "lr:R:",
                                   ["start=", "start-after=", "filter=", "rfilter=", "all", "all-cross", "loop",
                                    "debug", "protocol=", "compress", "valgrind", "host=", "serialize", "continue",
                                    "ipv6", "ice-home=", "cross=", "x64", "script", "java2"])
    except getopt.GetoptError:
        usage()

    if args:
        usage()

    start = 0
    loop = False
    all = False
    allCross = False
    arg = ""
    script = False

    filters = []
    for o, a in opts:
        if o == "--continue":
            global keepGoing
            keepGoing = True
        elif o in ("-l", "--loop"):
            loop = True
        elif o in ("-r", "-R", "--filter", '--rfilter'):
            testFilter = re.compile(a)
            if o in ("--rfilter", "-R"):
                filters.append((testFilter, True))
            else:
                filters.append((testFilter, False))
        elif o == "--cross":
            global cross
            if not a in ["cpp", "java", "cs", "py", "rb", "cppe"]:
                print "cross must be one of cpp, java, cs, py or rb"
                sys.exit(1)
            cross.append(a)
        elif o == "--all" :
            all = True
        elif o == "--all-cross" :
            allCross = True
        elif o in '--start':
            start = int(a)
        elif o == "--script":
            script = True
        elif o == "--protocol":
            if a not in ( "ssl", "tcp"):
                usage()
            if mono and getDefaultMapping() == "cs" and a == "ssl":
                print "SSL is not supported with mono"
                sys.exit(1)

        if o in ( "--cross", "--protocol", "--host", "--debug", "--compress", "--valgrind", "--serialize", "--ipv6", \
                  "--ice-home", "--x64", "--java2"):
            arg += " " + o
            if len(a) > 0:
                arg += " " + a

    if not root:
        tests = [ (os.path.join(getDefaultMapping(), "test", x), y) for x, y in tests ]

    # Expand all the tests and argument combinations.
    expanded = []
    if all:
        expanded.append([(test, arg, config) for test,config in tests if "once" in config ])

        if getDefaultMapping() == "cppe":
            expanded.append([ (test, arg, config) for test,config in tests if "core" in config])
        else:
            a = '--protocol=tcp %s'  % arg
            expanded.append([ (test, a, config) for test,config in tests if "core" in config])

            a = '--protocol=ssl %s'  % arg
            expanded.append([ (test, a, config) for test,config in tests if "core" in config])

            a = '--protocol=tcp --compress %s'  % arg
            expanded.append([ (test, a, config) for test,config in tests if "core" in config])

            a = "--ipv6 --protocol=tcp %s" % arg
            expanded.append([ (test, a, config) for test,config in tests if "core" in config])

            a = "--ipv6 --protocol=ssl %s" % arg
            expanded.append([ (test, a, config) for test,config in tests if "core" in config])

            a = "--protocol=tcp %s" % arg
            expanded.append([ (test, a, config) for test,config in tests if "service" in config])

            a = "--protocol=ssl --ipv6 %s" % arg
            expanded.append([ (test, a, config) for test,config in tests if "service" in config])

            a = "--protocol=tcp --serialize %s" % arg
            expanded.append([ (test, a, config) for test,config in tests if "stress" in config])
    elif not allCross:
        expanded.append([ (test, arg, config) for test,config in tests])

    if allCross:
        if len(cross) == 0:
            cross = ["cpp", "java", "cs" ]
	if root:
	    allLang = ["cpp", "java", "cs" ]
	else:
	    allLang = [ getDefaultMapping() ]
        for lang in allLang:
            # This is all other languages than the current mapping.
            crossLang = [ l for l in cross if lang != l ]
            # This is all eligible cross tests for the current mapping.
            # Now expand out the tests. We run only tcp for most cross tests.
            for c in crossLang:
                a = "--cross=%s --protocol=tcp" % c
                expanded.append([ ( "%s/test/%s" % (lang, test), a, []) for test in crossTests if not (test == "Ice/background" and (lang == "cs" or c == "cs"))])
                
                # Add ssl & compress for the operations test.
                if mono and c == "cs": # Don't add the ssl tests for mono.
                    continue
                a = "--cross=%s --protocol=ssl --compress" % c
                expanded.append([("%s/test/Ice/operations" % lang, a, [])])

    # Apply filters after expanding.
    if len(filters) > 0:
        for testFilter, removeFilter in filters:
            nexpanded = []
            for tests in expanded:
                if removeFilter:
                    nexpanded.append([ (x, a, y) for x,a,y in tests if not testFilter.search(x) ])
                else:
                    nexpanded.append([ (x, a, y) for x,a,y in tests if testFilter.search(x) ])
            expanded = nexpanded

    if loop:
        num = 1
        while 1:
            runTests(start, expanded, num, script = script)
            num += 1
    else:
        runTests(start, expanded, script = script)

    global testErrors
    if len(testErrors) > 0:
        print "The following errors occurred:"
        for x in testErrors:
            print x

if not isWin32():
    mono = True

def getIceDir(subdir = None):
    #
    # If ICE_HOME is set we're running the test against a binary distribution. Otherwise,
    # we're running the test against a source distribution.
    # 
    global iceHome
    if iceHome:
        return iceHome
    elif subdir:
        return os.path.join(toplevel, subdir)
    else: 
        return toplevel

def writePhpIni(src, dst):
    extDir = None
    ext = None

    #
    # TODO
    #
    # When we no longer support PHP 5.1.x, we can use the following PHP
    # command-line options:
    #
    # -d extension_dir=...
    # -d extension=[php_ice.dll|IcePHP.so]
    #
    if isWin32():
        ext = "php_ice.dll"
        extDir = os.path.abspath(os.path.join(getIceDir("php"), "bin"))
    else:
        ext = "IcePHP.so"
        if not iceHome:
            extDir = os.path.abspath(os.path.join(toplevel, "php", "lib"))
        else:
            #
            # If ICE_HOME points to the installation directory of a source build, the
            # PHP extension will be located in $ICE_HOME/lib or $ICE_HOME/lib64.
            # For an RPM installation, PHP is already configured to load the extension.
            # We could also execute "php -m" and check if the output includes "ice".
            #
            if x64:
                extDir = os.path.join(iceHome, "lib64")
            else:
                extDir = os.path.join(iceHome, "lib")

            if not os.path.exists(os.path.join(extDir, ext)):
                if iceHome == "/usr":
                    extDir = None # Assume PHP is already configured to load the extension.
                else:
                    print "unable to find IcePHP extension!"
                    sys.exit(1)

    ini = open(src, "r").readlines()
    for i in range(0, len(ini)):
        ini[i] = ini[i].replace("ICE_HOME", os.path.join(toplevel))
    tmpini = open(dst, "w")
    tmpini.writelines(ini)
    if extDir:
        tmpini.write("extension_dir=%s\n" % extDir)
        tmpini.write("extension=%s\n" % ext)
    tmpini.close()

def getIceSoVersion():

    config = open(os.path.join(toplevel, "cpp", "include", "IceUtil", "Config.h"), "r")
    intVersion = int(re.search("ICE_INT_VERSION ([0-9]*)", config.read()).group(1))
    majorVersion = intVersion / 10000
    minorVersion = intVersion / 100 - 100 * majorVersion    
    patchVersion = intVersion % 100
    if patchVersion > 50:
        if patchVersion >= 52:
            return '%db%d' % (majorVersion * 10 + minorVersion, patchVersion - 50)
        else:
            return '%db' % (majorVersion * 10 + minorVersion)
    else:
        return '%d' % (majorVersion * 10 + minorVersion)

def getIceSSLVersion():
    javaPipeIn, javaPipeOut = os.popen4("java IceSSL.Util")
    if not javaPipeIn or not javaPipeOut:
        print "unable to get IceSSL version!"
        sys.exit(1)
    version = javaPipeOut.readline()
    if not version:
        print "unable to get IceSSL version!"
        sys.exit(1)
    javaPipeIn.close()
    javaPipeOut.close()
    return version.strip()

def getJdkVersion():
    javaPipeIn, javaPipeOut = os.popen4("java -version")
    if not javaPipeIn or not javaPipeOut:
        print "unable to get Java version!"
        sys.exit(1)
    version = javaPipeOut.readline()
    if not version:
        print "unable to get Java version!"
        sys.exit(1)
    javaPipeIn.close()
    javaPipeOut.close()
    return version

def getIceBox():
    #
    # Get and return the path of the IceBox executable
    #
    lang = getDefaultMapping()
    if lang == "cpp":
        iceBox = ""
        if isWin32():
            #
            # Read the build.txt file from the test directory to figure out 
            # how the IceBox service was built ("debug" vs. "release") and 
            # decide which icebox executable to use.
            # 
            build = open(os.path.join(os.getcwd(), "build.txt"), "r")
            type = build.read().strip()
            if type == "debug":
                iceBox = os.path.join(getCppBinDir(), "iceboxd.exe")
            elif type == "release":
                iceBox = os.path.join(getCppBinDir(), "icebox.exe")
        else:
            iceBox = os.path.join(getCppBinDir(), "icebox")

        if not os.path.exists(iceBox):
            print "couldn't find icebox executable to run the test"
            sys.exit(0)
    elif lang == "java":
        iceBox = "IceBox.Server"
    elif lang == "cs":
        iceBox = os.path.join(getIceDir("cs"), "bin", "iceboxnet")
                
    if iceBox == "":
        print "couldn't find icebox executable to run the test"
        sys.exit(0)
    
    return iceBox

class InvalidSelectorString(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

sslConfigTree = { 
        "cpp" : { 
            "plugin" : " --Ice.Plugin.IceSSL=IceSSL:createIceSSL --Ice.Default.Protocol=ssl " +
            "--IceSSL.DefaultDir=%(certsdir)s --IceSSL.CertAuthFile=cacert.pem",
            "client" : " --IceSSL.CertFile=c_rsa1024_pub.pem --IceSSL.KeyFile=c_rsa1024_priv.pem",
            "server" : " --IceSSL.CertFile=s_rsa1024_pub.pem --IceSSL.KeyFile=s_rsa1024_priv.pem",
            "colloc" : " --IceSSL.CertFile=c_rsa1024_pub.pem --IceSSL.KeyFile=c_rsa1024_priv.pem"
            },
        "java" : { 
            "plugin" : " --Ice.Plugin.IceSSL=IceSSL.PluginFactory --Ice.Default.Protocol=ssl " +
            "--IceSSL.DefaultDir=%(certsdir)s --IceSSL.Truststore=certs.jks --IceSSL.Password=password",
            "client" : " --IceSSL.Keystore=client.jks",
            "server" : " --IceSSL.Keystore=server.jks",
            "colloc" : " --IceSSL.Keystore=client.jks"
            },
        "cs" : {
            "plugin" : " --Ice.Plugin.IceSSL=IceSSL:IceSSL.PluginFactory --Ice.Default.Protocol=ssl" +
            " --IceSSL.Password=password --IceSSL.DefaultDir=%(certsdir)s",
            "client" : " --IceSSL.CertFile=c_rsa1024.pfx --IceSSL.CheckCertName=0",
            "server" : " --IceSSL.CertFile=s_rsa1024.pfx --IceSSL.ImportCert.CurrentUser.Root=cacert.pem",
            "colloc" : " --IceSSL.CertFile=c_rsa1024.pfx --IceSSL.ImportCert.CurrentUser.Root=cacert.pem --IceSSL.CheckCertName=0"
            },
        }
sslConfigTree["py"] = sslConfigTree["cpp"]
sslConfigTree["rb"] = sslConfigTree["cpp"]
sslConfigTree["php"] = sslConfigTree["cpp"]

def getDefaultMapping():
    """Try and guess the language mapping out of the current path"""

    here = os.getcwd()
    while len(here) > 0:
	current = os.path.basename(here)
	here = os.path.dirname(here)
        if current in ["cpp", "cs", "java", "php", "py", "rb", "tmp", "cppe"]:
	    return current
    else:
        raise "cannot determine mapping"

def getTestEnv():
    env = {}
    env["certsdir"] = os.path.abspath(os.path.join(toplevel, "certs"))
    return env 

class DriverConfig:
    lang = None
    protocol = None 
    compress = 0
    serialize = 0
    host = None 
    mono = False
    valgrind = False
    type = None
    overrides = None
    ipv6 = False
    x64 = False
    java2 = False

    def __init__(self, type = None):
        global protocol
        global compress
        global serialize
        global host 
        global mono
        global valgrind
        global ipv6
        global x64
        global java2
        self.lang = getDefaultMapping()
        self.protocol = protocol
        self.compress = compress
        self.serialize = serialize
        self.host = host
        self.mono = mono
        self.valgrind = valgrind
        self.type = type
        self.ipv6 = ipv6
        self.x64 = x64
        self.java2 = java2
        
def argsToDict(argumentString, results):
    """Converts an argument string to dictionary"""
    args = argumentString.strip()
    while len(args) > 0:
        end = args.find(" --")
        if end == -1:
            current = args.strip()
            args = ""
        else:
            current = args[:end].strip()
            args = args[end:].strip()

        value = current.find("=")
        if value != -1:
            results[current[:value]] = current[value+1:]
        else:
            results[current] = None
    return results
            
def getCommandLine(exe, config, env=None):

    if not env:
        env = getTestEnv()
        
    #
    # Command lines are built up from the items in the components
    # sequence, which is initialized with command line options common to
    # all test drivers.
    #
    components = ["--Ice.NullHandleAbort=1"]
    components += ["--Ice.Warn.Connections=1"]

    #
    # Turn on network tracing.
    #
    # components.append("--Ice.Trace.Network=3")

    #
    # Now we add additional components dependent on the desired
    # configuration.
    #
    if config.protocol == "ssl":
        components.append(sslConfigTree[config.lang]["plugin"] % env)
        components.append(sslConfigTree[config.lang][config.type] % env)

    if config.compress:
        components.append("--Ice.Override.Compress=1")

    if config.serialize:
        components.append("--Ice.ThreadPool.Server.Serialize=1")

    if config.type == "server" or config.type == "colloc" and config.lang == "py":
        components.append("--Ice.ThreadPool.Server.Size=1 --Ice.ThreadPool.Server.SizeMax=3 --Ice.ThreadPool.Server.SizeWarn=0")

    if config.type == "server":
        components.append("--Ice.PrintAdapterReady=1 --Ice.ServerIdleTime=30")

    if config.ipv6:
        components.append("--Ice.Default.Host=0:0:0:0:0:0:0:1 --Ice.IPv6=1")
    elif config.host != None and len(config.host) != 0:
        components.append("--Ice.Default.Host=%s" % config.host)

    #
    # Not very many tests actually require an option override, so not to worried
    # about optimal here.
    #
    if config.overrides != None and len(config.overrides) > 0:
        propTable = {}
        for c in components:
            argsToDict(c, propTable)
                    
        argsToDict(config.overrides, propTable)
        components = []
        for k, v in propTable.iteritems():
            if v != None:
                components.append("%s=%s" % (k, v))
            else:
                components.append("%s" % k)
    
    output = StringIO.StringIO()
    if config.mono and config.lang == "cs":
        print >>output, "mono", "--debug %s.exe" % exe,
    elif config.lang == "rb" and config.type == "client":
        print >>output, "ruby", exe,
    elif config.lang == "java":
        print >>output, "%s -ea" % javaCmd,
        if isSolaris() and config.x64:
            print >>output, "-d64",
        if not config.ipv6:
            print >>output, "-Djava.net.preferIPv4Stack=true",
        print >>output,  exe,
    elif config.lang == "py":
        print >>output, "python", exe,
    elif config.lang == "php" and config.type == "client":
        print >>output, phpCmd, "-c tmp.ini -f", exe, " -- ",
    elif config.lang == "cpp" and config.valgrind:
        # --child-silent-after-fork=yes is required for the IceGrid/activator test where the node
        # forks a process with execv failing (invalid exe name).
        print >>output, "valgrind -q --child-silent-after-fork=yes --leak-check=full ",
        print >>output, "--suppressions=" + os.path.join(toplevel, "config", "valgrind.sup"), exe,
    else:
        print >>output, exe,

    for c in components:
        print >>output, c,
    commandline = output.getvalue()
    output.close()

    return commandline

def getDefaultServerFile():
    lang = getDefaultMapping()
    if lang in ["rb", "php", "cpp", "cs", "cppe"]:
        return "server"
    if lang == "py":
        return "Server.py"
    if lang in ["java"]:
        return "Server"

def getDefaultClientFile(lang = None):
    if lang is None:
        lang = getDefaultMapping()
    if lang == "rb":
        return "Client.rb"
    if lang == "php":
        return "Client.php"
    if lang in ["cpp", "cs", "cppe"]:
        return "client"
    if lang == "py":
        return "Client.py"
    if lang in ["java"]:
        return "Client"

def getDefaultCollocatedFile():
    lang = getDefaultMapping()
    if lang == "rb":
        return "Collocated.rb"
    if lang == "php":
        return "Collocated.php"
    if lang in ["cpp", "cs", "cppe"]:
        return "collocated"
    if lang == "py":
        return "Collocated.py"
    if lang in ["java"]:
        return "Collocated"

def isDebug():
    return debug

import Expect
def spawn(cmd, env = None, cwd = None):
    if debug:
        print "(%s)" % cmd,
    return Expect.Expect(cmd, env = env, logfile=tracefile, cwd = cwd)

def spawnClient(cmd, env = None, cwd = None, echo = True):
    client = spawn(cmd, env, cwd)
    if echo:
        client.trace()
    return client

def spawnServer(cmd, env = None, cwd = None, count = 1, adapter = None, echo = True):
    server = spawn(cmd, env, cwd)
    if adapter:
        server.expect("%s ready\n" % adapter)
    else:
        while count > 0:
            server.expect("[^\n]+ ready\n")
            count = count -1
    if echo:
        server.trace([re.compile("[^\n]+ ready")])
    return server

def getMirrorDir(base, mapping):
    """Get the mirror directory for the current test in the given mapping."""
    lang = getDefaultMapping()
    after = []
    before = base
    while len(before) > 0:
	current = os.path.basename(before)
	before = os.path.dirname(before)
	if current == lang:
	    break
	after.insert(0, current)
    else:
        raise "cannot find language dir"
    return os.path.join(before, mapping, *after)


def clientServerTest(additionalServerOptions = "", additionalClientOptions = "",
                     server = None, client = None, serverenv = None, clientenv = None):
    if server is None:
        server = getDefaultServerFile()
    if client is None:
        client = getDefaultClientFile()
    serverDesc = server
    clientDesc = client

    lang = getDefaultMapping()
    testdir = os.getcwd()

    # Setup the server.
    if lang in ["rb", "php"]:
        serverdir = getMirrorDir(testdir, "cpp")
    else:
        serverdir = testdir
    if lang != "java":
        server = os.path.join(serverdir, server)

    if serverenv is None:
        serverenv = copy.deepcopy(os.environ)
        if lang == "cpp" or lang == "cppe":
            addLdPath(os.path.join(serverdir), serverenv)
        elif lang == "java":
            addClasspath(os.path.join(serverdir, "classes"), serverenv)

    global cross
    if len(cross) == 0:
        cross.append(lang)

    for clientLang in cross:
        clientCfg = DriverConfig("client")
        if clientLang != lang:
            if clientDesc != getDefaultClientFile():
                print "** skipping cross test"
                return

            clientCfg.lang = clientLang
            client = getDefaultClientFile(clientLang)
            clientdir = getMirrorDir(testdir, clientLang)
            if clientLang == "cppe":
                clientdir = clientdir.replace("Ice", "IceE")
            else:
                clientdir = clientdir.replace("IceE", "Ice")
	    print clientdir
            if not os.path.exists(clientdir):
                print "** no matching test for %s" % clientLang
                return
        else:
            clientdir = testdir

        if clientLang != "java":
            client = os.path.join(clientdir, client)

        if clientenv is None:
            clientenv = copy.deepcopy(os.environ)
            if clientLang == "cpp" or clientLang == "cppe":
                addLdPath(os.path.join(clientdir), clientenv)
            elif clientLang == "java":
                addClasspath(os.path.join(clientdir, "classes"), clientenv)

        print "starting " + serverDesc + "...",
        serverCfg = DriverConfig("server")
        if lang in ["rb", "php"]:
            serverCfg.lang = "cpp"
        server = getCommandLine(server, serverCfg) + " " + additionalServerOptions
        serverProc = spawnServer(server, env = serverenv)
        print "ok"

        if lang == "php":
            writePhpIni("php.ini", "tmp.ini")

        if clientLang == lang:
            print "starting %s..." % clientDesc,
        else:
            print "starting %s %s ..." % (clientLang, clientDesc),
        client = getCommandLine(client, clientCfg) + " " + additionalClientOptions
        clientProc = spawnClient(client, env = clientenv)
        print "ok"

        clientProc.waitTestSuccess()
        serverProc.waitTestSuccess()

def collocatedTest(additionalOptions = "", collocated = None):
    lang = getDefaultMapping()
    if len(cross) > 1 or cross[0] != lang:
        print "** skipping cross test"
        return
    testdir = os.getcwd()

    if collocated == None:
        collocated = getDefaultCollocatedFile()
    collocatedDesc = collocated
    if lang != "java":
        collocated = os.path.join(testdir, collocated) 
        if lang == "cpp":
            env = copy.deepcopy(os.environ)
            addLdPath(os.path.join(testdir), env)
        else:
            env = None
    else:
        env = copy.deepcopy(os.environ)
        addClasspath(os.path.join(testdir, "classes"), env)

    print "starting %s ..." % (collocatedDesc),
    collocated = getCommandLine(collocated, DriverConfig("colloc")) + ' ' + additionalOptions 
    collocatedProc = spawnClient(collocated, env = env)
    print "ok"
    collocatedProc.waitTestSuccess()

def cleanDbDir(path):
    for filename in [ os.path.join(path, f) for f in os.listdir(path) if f != ".gitignore" and f != "DB_CONFIG" ]:
	os.remove(filename)

def startClient(exe, args = "", config=None, env=None, echo = True):
    if config == None:
        config = DriverConfig("client")
    cmd = getCommandLine(exe, config, env) + ' ' + args
    if config.lang == "php":
        writePhpIni("php.ini", "tmp.ini")

    return spawnClient(cmd, echo = echo)

def startServer(exe, args = "", config=None, env=None, adapter = None, count = 1, echo = False):
    if config == None:
        config = DriverConfig("server")
    cmd = getCommandLine(exe, config, env) + ' ' + args
    return spawnServer(cmd, adapter = adapter, count = count, echo = echo)

def startColloc(exe, args, config=None, env=None):
    if config == None:
        config = DriverConfig("colloc")
    cmd = getCommandLine(exe, config, env) + ' ' + args
    return spawnClient(cmd)

def simpleTest(exe, options = ""):
    print "starting client...",
    command = exe + ' ' + options
    client = spawnClient(command)
    print "ok"
    client.waitTestSuccess()

def getCppBinDir():
    if getDefaultMapping() == "cppe":
        binDir = os.path.join(getIceDir("cppe"), "bin")
    else:
        binDir = os.path.join(getIceDir("cpp"), "bin")
    if iceHome and x64:
        if isHpUx():
            binDir = os.path.join(binDir, "pa20_64")
        elif isSolaris():
            if isSparc():
                binDir = os.path.join(binDir, "sparcv9")
            else:
                binDir = os.path.join(binDir, "amd64")
        elif isWin32():
            binDir = os.path.join(binDir, "x64")
    return binDir

def getTestName():
    lang = getDefaultMapping()
    here = os.getcwd().split(os.sep)
    here.reverse()
    for i in range(0, len(here)):
        if here[i] == lang:
            break
    else:
        raise "cannot find language dir"
    here = here[:i-1]
    here.reverse()
    # The crossTests list is in UNIX format.
    name = os.path.join(*here).replace(os.sep, '/')
    # XXX
    return name.replace("IceE", "Ice")

def processCmdLine():
    def usage():
        if getDefaultMapping() == "cppe":
            print "usage: " + sys.argv[0] + """
          --debug                 Display debugging information on each test.
          --trace=<file>          Display tracing.
          --host=host             Set --Ice.Default.Host=<host>.
          --ice-home=<path>       Use the binary distribution from the given path.
          --x64                   Binary distribution is 64-bit.
          --cross=lang            Run cross language test.
            """
        else:
            print "usage: " + sys.argv[0] + """
          --debug                 Display debugging information on each test.
          --trace=<file>          Display tracing.
          --protocol=tcp|ssl      Run with the given protocol.
          --compress              Run the tests with protocol compression.
          --valgrind              Run the tests with valgrind.
          --host=host             Set --Ice.Default.Host=<host>.
          --serialize             Run with connection serialization.
          --ipv6                  Use IPv6 addresses.
          --ice-home=<path>       Use the binary distribution from the given path.
          --x64                   Binary distribution is 64-bit.
          --java2                 Use Java 2 jar file.
          --cross=lang            Run cross language test.
            """
        sys.exit(2)

    try:
        if getDefaultMapping() == "cppe":
            opts, args = getopt.getopt(
                sys.argv[1:], "", ["debug", "trace=", "host=", "ice-home=", "x64", "cross="])
        else:
            opts, args = getopt.getopt(
                sys.argv[1:], "", ["debug", "trace=", "protocol=", "compress", "valgrind", "host=", "serialize", \
                                   "ipv6", "ice-home=", "x64", "cross=", "java2"])
    except getopt.GetoptError:
        usage()

    if args:
        usage()

    for o, a in opts:
        if o == "--ice-home":
            global iceHome
            iceHome = a
        elif o == "--cross":
            global cross
            #testName = getTestName()
            #if testName == "Ice/custom":
            #if getTestName() not in crossTests:
            cross.append(a)
            if not a in ["cpp", "java", "cs", "py", "rb", "cppe"]:
                print "cross must be one of cpp, java, cs, py or rb"
                sys.exit(1)
            if getTestName() not in crossTests:
                print "*** This test does not support cross language testing"
                sys.exit(0)
	    # Temporary.
	    lang = getDefaultMapping()
            if getTestName() == "Ice/background" and (lang == "cs" or cross == "cs"):
                print "*** This test does not support cross language testing"
                sys.exit(0)
            
        elif o == "--x64":
            global x64
            x64 = True
        elif o == "--java2":
            global java2
            java2 = True
        elif o == "--compress":
            global compress
            compress = True
        elif o == "--serialize":
            global serialize
            serialize = True
        elif o == "--host":
            global host
            host = a
        elif o == "--valgrind":
            global valgrind
            valgrind = True
        elif o == "--ipv6":
            global ipv6
            ipv6 = True
	if o == "--trace":
            global tracefile
	    if a == "stdout":
		tracefile = sys.stdout
	    else:
		tracefile = open(a, "w")
        elif o == "--debug":
            global debug
            debug = True
        elif o == "--protocol":
            if a not in ( "ssl", "tcp"):
                usage()
            # ssl protocol isn't directly supported with mono.
            if mono and getDefaultMapping() == "cs" and a == "ssl":
                print "SSL is not supported with mono"
                sys.exit(1)
            global protocol
            protocol = a

    if len(args) > 0:
        usage()

    # Only use binary distribution from ICE_HOME environment variable if USE_BIN_DIST=yes
    if not iceHome and os.environ.get("USE_BIN_DIST", "no") == "yes":
        if getDefaultMapping() == "cppe":
            if os.environ.get("ICEE_HOME", "") != "":
                iceHome = os.environ["ICEE_HOME"]
            elif isLinux():
                iceHome = "/usr"
        else:
            if os.environ.get("ICE_HOME", "") != "":
                iceHome = os.environ["ICE_HOME"]
            elif isLinux():
                iceHome = "/usr"
            
    if not x64:
        x64 = isWin32() and os.environ.get("XTARGET") == "x64" or os.environ.get("LP64") == "yes"
    
    if getDefaultMapping() == "cppe":
        configureEmbeddedPaths()
    else:
        configurePaths()

def runTests(start, expanded, num = 0, script = False):
    total = 0
    for tests in expanded:
        for i, args, config in tests:
            total = total + 1
    #
    # The configs argument is a list containing one or more test configurations.
    #
    index = 0
    for tests in expanded:
        for i, args, config in tests:
            index = index + 1
            if index < start:
                continue
            i = os.path.normpath(i)
            dir = os.path.join(toplevel, i)

            print
            if num > 0:
                print "[" + str(num) + "]",
            if script:
                prefix = "echo \""
                suffix = "\""
            else:
                prefix = ""
                suffix = ""

            print "%s*** running tests %d/%d in %s%s" % (prefix, index, total, dir, suffix)
            print "%s*** configuration:" % prefix,
            if len(args.strip()) == 0:
                print "Default",
            else:
                print args.strip(),
            print suffix

            if args.find("cross") != -1:
                test = os.path.join(*i.split(os.sep)[2:])
		# The crossTests list is in UNIX format.
		test = test.replace(os.sep, '/')
                test = test.replace("IceE", "Ice")
                if not test in crossTests:
                    print "%s*** test does not support cross testing%s" % (prefix, suffix)
                    continue

            #
            # Skip tests not supported with IPv6 if necessary
            #
            if args.find("ipv6") != -1 and "noipv6" in config:
                print "%s*** test not supported with IPv6%s" % (prefix, suffix)
                continue

            if isVista() and "novista" in config:
                print "%s*** test not supported under Vista%s" % (prefix, suffix)
                continue

            if not isWin32() and "win32only" in config:
                print "%s*** test only supported under Win32%s" % (prefix, suffix)
                continue

            # If this is mono and we're running ssl protocol tests
            # then skip. This occurs when using --all.
            if mono and ("nomono" in config or (i.find(os.path.join("cs","test")) != -1 and args.find("ssl") != -1)):
                print "%s*** test not supported with mono%s" % (prefix, suffix)
                continue

            # If this is java and we're running ipv6 under windows then skip.
            if isWin32() and i.find(os.path.join("java","test")) != -1 and args.find("ipv6") != -1:
                print "%s*** test not supported under windows%s" % (prefix, suffix)
                continue

            # Skip tests not supported by valgrind
            if args.find("valgrind") != -1 and ("novalgrind" in config or args.find("ssl") != -1):
                print "%s*** test not supported with valgrind%s" % (prefix, suffix)
                continue
            
            if script:
                print "echo \"*** test started: `date`\""
                print "cd %s" % dir
            else:
                print "*** test started:", time.strftime("%x %X")
                sys.stdout.flush()

                os.chdir(dir)

            global keepGoing
            if script:
                print "if ! python %s %s; then" % (os.path.join(dir, "run.py"), args)
                print "  echo 'test in %s failed'" % os.path.abspath(dir)
                if not keepGoing:
                    print "  exit 1"
                print "fi"
            else:
                status = os.system("python " + os.path.join(dir, "run.py " + args))

                if status:
                    if(num > 0):
                        print "[" + str(num) + "]",
                    message = "test in " + os.path.abspath(dir) + " failed with exit status", status,
                    print message
                    if not keepGoing:
                        sys.exit(status)
                    else:
                        print " ** Error logged and will be displayed again when suite is completed **"
                        global testErrors
                        testErrors.append(message)


if os.environ.has_key("ICE_CONFIG"):
    os.unsetenv("ICE_CONFIG")

import inspect
frame = inspect.currentframe()
# Move to the top-most frame in the callback.
while frame.f_back is not None:
    frame = frame.f_back
if os.path.split(frame.f_code.co_filename)[1] == "run.py":
    # If we're not in the test directory, chdir to the correct
    # location.
    if not os.path.isabs(sys.argv[0]):
        d = os.path.join(os.getcwd(), sys.argv[0])
    else:
        d = sys.argv[0]
    d = os.path.split(d)[0]
    if os.path.normpath(d) != os.getcwd():
        os.chdir(d)
    processCmdLine()
