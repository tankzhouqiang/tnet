#!/usr/bin/env python

import sys
import os
import re

def getNamespace(path):
	ls = path.split("/")
	n = len(ls)
	while n >= 1 and len(ls[n-1]) == 0:
		n = n - 1
	if n < 2:
		return None
	if ls[n-1] != "test":
		return None
	n = n - 1
	while n >= 1 and len(ls[n-1]) == 0:
		n = n - 1
	if n < 1:
		return None
	return ls[n - 1]

def getHeaderPath(path):
    ls = path.split("/")
    n = len(ls)
    while n >= 1 and len(ls[n-1]) == 0:
        n = n - 1
    if n < 1:
        return None
    n = n-1;
    if ls[n] == 'test':
        n = n-1
    
    dirCount = n;
    while n >= 1 and ls[n] <> 'tnet':
        n = n - 1
    n = n + 1
    path = ""
    if n <= dirCount:
        path = ls[n]
    while n < dirCount :
        path =path + "/"+ls[n+1]
        n = n+1
    return path

def createTestClassCPP(path, classname):
	ns = getNamespace(path)
	hp = getHeaderPath(path)
	if not ns:
		return False
	context = ""
	context = context + "#include \"../" + classname + ".h\"" + "\n"
	context = context + "#include \"gtest/gtest.h\"" + "\n"
	context = context + "\n"
	context = context + "using namespace std;\n"
	context = context + "using namespace::testing;\n"
	context = context + "\n"
	context = context + "TNET_BEGIN_NAMESPACE(" + ns + ");" + "\n"
	context = context + "\n"
	context = context + "class " + classname + "Test : " + "public ::testing::Test {\n"
	context = context + "protected:" + "\n"
	context = context + "    " + classname + "Test() {\n"
	context = context + "    " + "}\n"
	context = context + "    " + "virtual ~" + classname + "Test() {\n"
	context = context + "    " +  "}\n"
	context = context + "    " + "virtual void SetUp() {\n"
	context = context + "    " +  "}\n"
	context = context + "    " + "virtual void TearDown() {\n"
	context = context + "    " +  "}\n"
	context = context +  "};\n"
	context = context +  "\n"
	context = context + "TEST_F(" + classname + "Test,  simpleProcess) {\n"
	context = context +  "}\n"
	context = context +  "\n"
	context = context + "TNET_END_NAMESPACE(" + ns + ");" + "\n"
	context = context + "" + "\n"
	f = file(path + "/" + classname + "Test.cpp", "w")
	f.write(context)
	f.close()
	return True

def createTestClass(path, classname):
	ret = 0
	if os.path.exists(path + "/" + classname + "Test.cpp"):
		print "source file " + path + "/" + classname + "Test.cpp exists!" 
	else:
		if createTestClassCPP(path, classname):
			print "create source file " + path + "/" + classname + "Test.cpp succeed."
			ret = ret + 1
		else:
			print "create source file " + path + "/" + classname + "Test.cpp failed."
	return ret

def insertSConscript(scon_name, name):
	hasFindSource = False
	os.system("mv " + scon_name + " " + scon_name + ".bak")
	TIP = ur"_sources\s*=\s*\["
	fin = file(scon_name + ".bak", "r");
	fout = file(scon_name, "w");
	while True:
		l = fin.readline()
		if not l:
			break;
		if not hasFindSource:
			if re.search(TIP, l):
				hasFindSource = True
		elif l.find(']') != -1:
			l = "    \'" + name + "Test.cpp\',\n" + l
			hasFindSource = False
		fout.write(l)
	fin.close()
	fout.close()
	print name + " has been inserted into " + scon_name
	os.system("rm " + scon_name + ".bak")
	
if __name__ == "__main__":
	if len(sys.argv) != 2:
		print >> sys.stderr, "Usage:", sys.argv[0], "<classname>"
		sys.exit(1)
	path = os.getcwd()
	if createTestClass(path, sys.argv[1]) == 1:
		insertSConscript(path + "/SConscript", sys.argv[1])
