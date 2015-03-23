# -*- mode: python -*-
install_root = "/home/tank/svn/tnet/"
ccflags = "-I%s -I%s -std=c++11" % (install_root, install_root + 'include/')

env = Environment(CCFLAGS = ccflags)
env['install_root'] = install_root

env.SConscript('tnet/SConscript', variant_dir='build', exports='env')
