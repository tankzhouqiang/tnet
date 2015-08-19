# -*- mode: python -*-
import sys, os, platform, time

install_root = "/home/tank/svn/tnet/"
ccflags = "-I%s -I%s " % (install_root, install_root + 'include/')

env = Environment(CCFLAGS = ccflags)
env['install_root'] = install_root
env.Decider('MD5-timestamp')
env['ENV']["LD_LIBRARY_PATH"] = "/usr/local/lib64:/usr/local/lib:/usr/lib64:/usr/lib:%s/build/tnet/util/:%s/build/tnet/network:%s/lib" % (env['install_root']\
, env['install_root'], env['install_root'])

def runUnitTest_(target, source, env):
    cmd = ""
    for item in env['ENV'].items():
        cmd += (' %s=%s' % item)

    cmd += ' %s'
    for p in source:
        dirname = os.path.dirname(p.abspath)
        print "ut test: Entering directory `%s'" % dirname
        print cmd % p.abspath
        ret = os.system(cmd % p.abspath)
        print "ATest: Leaving directory `%s'" % dirname
        if ret !=0:
            return ret

    return 0
_builders = {}
_builders['runUnitTest'] = Builder(action= runUnitTest_)

def uTest(self, target, source):
    self.Alias('test', target)
    self.runUnitTest(target, source)
_methods = []
_methods.append(uTest)

env.Append(BUILDERS = _builders)
for method in _methods:
    env.AddMethod(method)

env.SConscript(dirs='.', variant_dir='build', exports='env', duplicate=1)
