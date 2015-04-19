#ifndef TNET_SERVERADAPTER_H
#define TNET_SERVERADAPTER_H

#include <tnet/common/Common.h>
#include <tnet/network/Packet.h>
#include <tnet/network/TcpConnection.h>

TNET_BEGIN_NAMESPACE(network);
class TcpConnection;

class ServerAdapter
{
public:
    ServerAdapter();
    ~ServerAdapter();
private:
    ServerAdapter(const ServerAdapter &);
    ServerAdapter& operator=(const ServerAdapter &);
public:
    virtual void handlePacket(Packet *packet, 
                              TcpConnection *connection) = 0;
private:
};

TNET_TYPEDEF_PTR(ServerAdapter);

TNET_END_NAMESPACE(network);

#endif //TNET_SERVERADAPTER_H
