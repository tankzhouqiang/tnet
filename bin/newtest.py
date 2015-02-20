#!/bin/env python

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
    while n >= 1 and ls[n] <> 'tbase':
        n = n - 1
    n = n + 1
    path = ""
    if n <= dirCount:
        path = ls[n]
    while n < dirCount :
        path =path + "/"+ls[n+1]
        n = n+1
    return path


def createTestClassH(path, classname):
	ns = getNamespace(path)
	hp = getHeaderPath(path)
	if not ns:
		return False
	context = ""
	context = context + "#ifndef TBASE_" + classname.upper() + "TEST_H" + "\n"
	context = context + "#define TBASE_" + classname.upper() + "TEST_H" + "\n"
	context = context + "" + "\n"
	context = context + "#include <tbase/common/Common.h>" + "\n"
	context = context + "#include <tbase/common/Log.h>" + "\n"
	context = context + "#include <tbase/" + hp + "/" + classname + ".h>" + "\n"
	context = context + "#include <cppunit/extensions/HelperMacros.h>" + "\n"
	context = context + "" + "\n"
	context = context + "TBASE_BEGIN_NAMESPACE(" + ns + ");" + "\n"
	context = context + "" + "\n"
	context = context + "class " + classname + "Test : public CppUnit::TestFixture {" + "\n"
	context = context + "    CPPUNIT_TEST_SUITE(" + classname + "Test);" + "\n"
	context = context + "    CPPUNIT_TEST(testSimpleProcess" + ");" + "\n"
	context = context + "    CPPUNIT_TEST_SUITE_END();" + "\n"
	context = context + "public:" + "\n"
	context = context + "    " + classname + "Test();" + "\n"
	context = context + "    ~" + classname + "Test();" + "\n"
	context = context + "public:" + "\n"
	context = context + "    void setUp();" + "\n"
	context = context + "    void tearDown();" + "\n"
	context = context + "    void testSimpleProcess" + "();" + "\n"
	context = context + "private:" + "\n"
	context = context + "    TBASE_LOG_DECLARE();" + "\n"
	context = context + "};" + "\n"
	context = context + "" + "\n"
	context = context + "TBASE_END_NAMESPACE(" + ns + ");" + "\n"
	context = context + "" + "\n"
	context = context + "#endif //TBASE_" + classname.upper() + "TEST_H" + "\n"
	f = file(path + "/" + classname + "Test.h", "w")
	f.write(context)
	f.close()
	return True

def createTestClassCPP(path, classname):
	ns = getNamespace(path)
	hp = getHeaderPath(path)
	if not ns:
		return False
	context = ""
	context = context + "#include <tbase/" + hp + "/test/" + classname + "Test.h>" + "\n"
	context = context + "#include <tbase/test/test.h>" + "\n"
	context = context + "#include <cppunit/TestAssert.h>" + "\n"
	context = context + "" + "\n"
	context = context + "TBASE_BEGIN_NAMESPACE(" + ns + ");" + "\n"
	context = context + "TBASE_LOG_SETUP(" + ns + ", " + classname + "Test);" + "\n"
	context = context + "" + "\n"
	context = context + "CPPUNIT_TEST_SUITE_REGISTRATION(" + classname + "Test);" + "\n"
	context = context + "" + "\n"
	context = context + classname + "Test::" + classname + "Test() { " + "\n"
	context = context + "}" + "\n"
	context = context + "" + "\n"
	context = context + classname + "Test::~" + classname + "Test() { " + "\n"
	context = context + "}" + "\n"
	context = context + "" + "\n"
	context = context + "void " + classname + "Test::setUp() { " + "\n"
	context = context + "    TBASE_LOG(DEBUG, \"setUp!\");\n"
	context = context + "}" + "\n"
	context = context + "" + "\n"
	context = context + "void " + classname + "Test::tearDown() { " + "\n"
	context = context + "    TBASE_LOG(DEBUG, \"tearDown!\");\n"
	context = context + "}" + "\n"
	context = context + "" + "\n"
	context = context + "void " + classname + "Test::testSimpleProcess" + "() { " + "\n"
	context = context + "    TBASE_LOG(DEBUG, \"Begin Test!\");" + "\n"
	context = context + "" + "\n"
	context = context + "    CPPUNIT_ASSERT(false);" + "\n"
	context = context + "    CPPUNIT_ASSERT_EQUAL(0, 1);" + "\n"
	context = context + "}" + "\n"
	context = context + "" + "\n"
	context = context + "TBASE_END_NAMESPACE(" + ns + ");" + "\n"
	context = context + "" + "\n"
	f = file(path + "/" + classname + "Test.cpp", "w")
	f.write(context)
	f.close()
	return True

def createTestClass(path, classname):
	ret = 0
	if os.path.exists(path + "/" + classname + "Test.h"):
		print "header file " + path + "/" + classname + "Test.h exists!" 
	else:
		if createTestClassH(path, classname):
			print "create header file " + path + "/" + classname + "Test.h succeed."
			ret = ret + 1
		else:
			print "create header file " + path + "/" + classname + "Test.h failed."
	if os.path.exists(path + "/" + classname + "Test.cpp"):
		print "source file " + path + "/" + classname + "Test.cpp exists!" 
	else:
		if createTestClassCPP(path, classname):
			print "create source file " + path + "/" + classname + "Test.cpp succeed."
			ret = ret + 1
		else:
			print "create source file " + path + "/" + classname + "Test.cpp failed."
	return ret

def insertMakefile(makefile, name):
  TIP = "test_sources"
  TIPLEN = len(TIP)
  fin = file(makefile, "r")
  fbak = file(makefile + ".bak", "w")
  context = fin.read()
  fin.close()
  fbak.write(context)
  fbak.close()
  fout = file(makefile, "w")
  fin = file(makefile + ".bak", "r")
  while True:
    l = fin.readline()
    if not l:
      break
    if len(l) > TIPLEN and l[:TIPLEN] == TIP:
       l = l + "        " + name + "\\\n"
#      n = l.find("=")
#      if n != -1:
#        l = l[:n+1] + " " + name + " \\\n    " + l[n+1:]
    fout.write(l)
  fin.close()
  fout.close()
  print name + " has been inserted into " + makefile


def insertSConscript(scon_name, name):
	hasFindSource = False
	os.system("mv " + scon_name + " " + scon_name + ".bak")
	TIP = "_test_sources\s*=\s*\["
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
	if createTestClass(path, sys.argv[1]) == 2:
		insertSConscript(path + "/SConscript", sys.argv[1])
#		insertMakefile(path + "/Makefile.am", sys.argv[1] + "Test.h " + sys.argv[1] + "Test.cpp")
