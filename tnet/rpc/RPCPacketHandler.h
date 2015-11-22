#ifndef TNET_RPCPACKETHANDLER_H
#define TNET_RPCPACKETHANDLER_H

#include <tnet/common/Common.h>
#include <tnet/network/IPacketHandler.h>
TNET_BEGIN_NAMESPACE(rpc);

class RPCPacketHandler : public network::IPacketHandler
{
public:
    RPCPacketHandler();
    ~RPCPacketHandler();
private:
    RPCPacketHandler(const RPCPacketHandler &);
    RPCPacketHandler& operator=(const RPCPacketHandler &);
public:
    /*override*/ virtual void handlePacket(network::Packet *packet, 
            void *args);

private:
};

TNET_TYPEDEF_PTR(RPCPacketHandler);

TNET_END_NAMESPACE(rpc);

#endif //TNET_RPCPACKETHANDLER_H
