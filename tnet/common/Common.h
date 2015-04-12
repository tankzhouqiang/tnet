#ifndef TNET_COMMON_H_
#define TNET_COMMON_H_

#include <assert.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <libgen.h>
#include <glog/logging.h>
#include <map>

#define DELETE_AND_SET_NULL(object)  if (object) { delete object; object = NULL;}

//#define TNET_BEGIN_NAMESPACE(x) namespace Tnet { namespace x {
#define TNET_BEGIN_NAMESPACE(x) namespace Tnet { namespace x{ 

#define TNET_END_NAMESPACE(x) } }

#define TNET_USE_ROOT_NAMESPACE using namespace Tnet;

#define TNET_USE_NAMESPACE(x) using namespace Tnet::x

#define TNET_NS(x) Tnet::x

#include <tr1/memory>
#define TNET_TYPEDEF_PTR(x) typedef std::tr1::shared_ptr<x> x##Ptr

#define TEST_DATA "test_data"

static std::string getExecPath() {    
    char exec_name[2048] = {0};                                                                                                             
    readlink("/proc/self/exe", exec_name, 2048);                                                                                            
    char *dname = dirname(exec_name);                                                                                                       
    return std::string(dname);                                                                                                              
};

#endif /*TNET_COMMON_H_*/


