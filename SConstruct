# -*- mode: python -*-
import sys, os, platform, time
install_root = "/home/tank/svn/tnet/"
include_root = "/home/tank/svn/tnet/include"
ccflags = "-I%s -I%s " % (install_root, include_root)

env = Environment(CCFLAGS = ccflags)
env['install_root'] = install_root

env.SConscript(dirs='.', variant_dir='build', exports='env', duplicate=1)

