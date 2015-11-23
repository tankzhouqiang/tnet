#ifndef TNET_RPCRETURNARG_H
#define TNET_RPCRETURNARG_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(rpc);

class RPCReturnArg
{
public:
    RPCReturnArg(google::protobuf::RpcController *controller,
                 google::protobuf::Message *response,
                 google::protobuf::Closure *done);
    ~RPCReturnArg();
private:
    RPCReturnArg(const RPCReturnArg &);
    RPCReturnArg& operator=(const RPCReturnArg &);
public:
    google::protobuf::RpcController *_controller;
    google::protobuf::Message *_response;
    google::protobuf::Closure *_done;
};

TNET_TYPEDEF_PTR(RPCReturnArg);

TNET_END_NAMESPACE(rpc);

#endif //TNET_RPCRETURNARG_H
