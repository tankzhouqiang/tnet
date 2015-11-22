#ifndef TNET_RPCSERVER_H
#define TNET_RPCSERVER_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(rpc);

class RpcServer
{
public:
    RpcServer();
    ~RpcServer();
private:
    RpcServer(const RpcServer &);
    RpcServer& operator=(const RpcServer &);
public:

private:
};

TNET_TYPEDEF_PTR(RpcServer);

TNET_END_NAMESPACE(rpc);

#endif //TNET_RPCSERVER_H
