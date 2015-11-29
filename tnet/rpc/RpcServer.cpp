#include <tnet/rpc/RpcServer.h>
#include <tnet/rpc/TnetRPCChannel.h>

TNET_BEGIN_NAMESPACE(rpc);

RpcServer::RpcServer() { 
}

RpcServer::~RpcServer() { 
}

bool RpcServer::registerService(google::protobuf::Service *service) {
    assert(service);
    const google::protobuf::ServiceDescriptor *serDes = 
        service->GetDescriptor();
    int methodCount = serDes->method_count();
    for (int i = 0; i < methodCount; ++i) {
        google::protobuf::MethodDescriptor *methodDes = 
            (google::protobuf::MethodDescriptor*) (serDes->method(i));
        uint32_t type = TnetRPCChannel::generateType(methodDes);
        std::map<uint32_t, google::protobuf::MethodDescriptor*>::const_iterator it = _rpcCallMap.find(type);
        if (it == _rpcCallMap.end()) {
            _rpcCallMap[type] = methodDes;
            return true;
        } else {
            LOG(ERROR) << "same method has existed." << std::endl;
            return false;
        }
    }
}

TNET_END_NAMESPACE(rpc);

