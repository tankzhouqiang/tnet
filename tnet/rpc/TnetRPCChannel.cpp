#include <tnet/rpc/TnetRPCChannel.h>
#include <tnet/network/DefaultPacket.h>
#include <tnet/rpc/rpc_extensions.pb.h>
#include <tnet/rpc/RPCReturnArg.h>
#include <tnet/rpc/SyncRPCClosure.h>

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

uint32_t TnetRPCChannel::generateType(
        const google::protobuf::MethodDescriptor *method)
{
    assert(method);
    const google::protobuf::ServiceDescriptor *serviceDes = method->service();
    uint32_t serviceId = (uint32_t) (serviceDes->options().GetExtension(tnet::service_id));
    uint32_t methodId = (uint32_t) (method->options().GetExtension(tnet::method_id));
    uint32_t type = (serviceId << 16) | methodId;
    return type;
}


DefaultPacket* TnetRPCChannel::generatePacket(
        const google::protobuf::MethodDescriptor *method,
        const google::protobuf::Message *request) 
{
    assert(method);
    DefaultPacket *packet = new DefaultPacket();
    uint32_t type = generateType(method);
    packet->setPacketType(type);

    uint32_t size = request->ByteSize();
    void *packetBody = malloc(size);
    request->SerializeToArray(packetBody, size);
    packet->setBodyLen(size);
    packet->setBody(packetBody);
    packet->setIsOwnBody(true);    
    return packet;
}

void TnetRPCChannel::CallMethod(
        const google::protobuf::MethodDescriptor *method,
        google::protobuf::RpcController *controller,
        const google::protobuf::Message *request,
        google::protobuf::Message *response,
        google::protobuf::Closure *done)
{
    DefaultPacket *packet = generatePacket(method, request);
    if (done != NULL) {
        asyncCall(packet, controller, response, done);
    } else {
        SyncRPCClosure *syncClo = new SyncRPCClosure();
        asyncCall(packet, controller, response, syncClo);
        syncClo->waitReply();
        delete syncClo;
    }
}

bool TnetRPCChannel::asyncCall(
        DefaultPacket *packet,
        google::protobuf::RpcController *controller,
         google::protobuf::Message *response,
        google::protobuf::Closure *done) 
{
    assert(packet);
    RPCReturnArg *arg = new RPCReturnArg(controller, response, done);
    _connection->postPacket(packet, &_handler, (void*)arg);
    return true;
}
TNET_END_NAMESPACE(rpc);

