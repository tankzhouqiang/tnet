#include <tnet/rpc/RPCPacketHandler.h>
#include <tnet/network/DefaultPacket.h>

TNET_USE_NAMESPACE(network);
TNET_BEGIN_NAMESPACE(rpc);

RPCPacketHandler::RPCPacketHandler() { 
}

RPCPacketHandler::~RPCPacketHandler() { 
}

void RPCPacketHandler::handlePacket(Packet *packet, void *args)
{
    assert(packet);
    DefaultPacket *defaultPacket = 
        dynamic_cast<DefaultPacket*>(packet);
    assert(defaultPacket);
    uint32_t bodyLen = defaultPacket->getBodyLen();
}

TNET_END_NAMESPACE(rpc);

