#include <tnet/rpc/RPCPacketHandler.h>
#include <tnet/rpc/RPCReturnArg.h>
#include <tnet/network/DefaultPacket.h>

TNET_USE_NAMESPACE(network);
TNET_BEGIN_NAMESPACE(rpc);

RPCPacketHandler::RPCPacketHandler() { 
}

RPCPacketHandler::~RPCPacketHandler() { 
}

void RPCPacketHandler::handlePacket(Packet *packet, void *args)
{
    assert(args);
    RPCReturnArg *reArg = (RPCReturnArg *)args;
    google::protobuf::Message *response = reArg->_response;
    google::protobuf::RpcController *controller = 
        reArg->_controller;
    google::protobuf::Closure *done = reArg->_done;

    if (!packet) {
        controller->SetFailed("return packet is NULL");
        delete reArg;
        return;
    }
    DefaultPacket *defaultPacket = 
        dynamic_cast<DefaultPacket*>(packet);
    assert(defaultPacket);
    if (!defaultPacket) {
        controller->SetFailed("default packet is NULL");
        delete reArg;
        return;
    }

    uint32_t bodyLen = defaultPacket->getBodyLen();    
    response->ParseFromArray(defaultPacket->getBody(), bodyLen);
    done->Run();
    delete reArg;
}

TNET_END_NAMESPACE(rpc);

