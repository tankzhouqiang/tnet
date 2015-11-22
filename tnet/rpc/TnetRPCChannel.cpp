#include <tnet/rpc/TnetRPCChannel.h>
#include <tnet/network/DefaultPacket.h>

TNET_USE_NAMESPACE(network);
TNET_BEGIN_NAMESPACE(rpc);

TnetRPCChannel::TnetRPCChannel(TcpConnection *connection) :
    _connection(connection)
{
}

TnetRPCChannel::~TnetRPCChannel() {
    if (_connection) {
        delete _connection;
    }
}

void TnetRPCChannel::CallMethod(
        const google::protobuf::MethodDescriptor *method,
        google::protobuf::RpcController *controller,
        const google::protobuf::Message *request,
        google::protobuf::Message *response,
        google::protobuf::Closure *done)
{
    assert(method);
    const google::protobuf::ServiceDescriptor *serviceDes = method->service();
    // uint32_t serviceId = (uint32_t) (serviceDes->options().GetExtension(service_id));
    // uint32_t methodId = (uint32_t) (method->options().GetExtension(service_id));
    // uint32_t type = (serviceId << 16) | methodId;
    uint32_t type;
    DefaultPacket *packet = new DefaultPacket();
    packet->setPacketType(type);
    

}

TNET_END_NAMESPACE(rpc);

