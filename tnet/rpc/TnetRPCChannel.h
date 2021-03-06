#ifndef TNET_TNETRPCCHANNEL_H
#define TNET_TNETRPCCHANNEL_H

#include <tnet/common/Common.h>
#include <tnet/network/TcpConnection.h>
#include <tnet/rpc/RPCPacketHandler.h>
#include <tnet/network/DefaultPacket.h>

TNET_BEGIN_NAMESPACE(rpc);

class TnetRPCChannel : public google::protobuf::RpcChannel
{
public:
    TnetRPCChannel(network::TcpConnection *connection);
    ~TnetRPCChannel();
private:
    TnetRPCChannel(const TnetRPCChannel &);
    TnetRPCChannel& operator=(const TnetRPCChannel &);
public:
    virtual void CallMethod(
            const google::protobuf::MethodDescriptor *method,
            google::protobuf::RpcController *controller,
            const google::protobuf::Message *request,
            google::protobuf::Message *response,
            google::protobuf::Closure *done);
    static uint32_t generateType(
            const google::protobuf::MethodDescriptor *method);

private:
    network::DefaultPacket* generatePacket(
        const google::protobuf::MethodDescriptor *method,
        const google::protobuf::Message *request);

    bool asyncCall(network::DefaultPacket *packet,
                   google::protobuf::RpcController *controller,
                   google::protobuf::Message *response,
                   google::protobuf::Closure *done);

private:
    network::TcpConnection *_connection;
    RPCPacketHandler _handler;
};

TNET_TYPEDEF_PTR(TnetRPCChannel);

TNET_END_NAMESPACE(rpc);

#endif //TNET_TNETRPCCHANNEL_H
