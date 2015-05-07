#ifndef TNET_TCPCONNECTION_H
#define TNET_TCPCONNECTION_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>
#include <tnet/network/PacketStream.h>
#include <tnet/network/IPacketHandler.h>
#include <tnet/network/ServerAdapter.h>
#include <tnet/network/SessionPool.h>
#include <tnet/util/Lock.h>

TNET_BEGIN_NAMESPACE(network);
class ServerAdapter;

class TcpConnection : public IOComponent
{
public:
    const static uint32_t PACKET_LEN_SIZE = 0;
    const static uint32_t ONE_SEND_PACKET_COUNT = 10000;
public:
    TcpConnection();
    ~TcpConnection();
private:
    TcpConnection(const TcpConnection &);
    TcpConnection& operator=(const TcpConnection &);
public:
    bool init(const std::string&ip, int port, 
              PacketStream *packetStream, int64_t timeout);
    bool postPacket(Packet *packet, 
                    IPacketHandler *packetHandler = NULL, 
                    void *args = NULL);
    void setIsServer(bool isServer) {
        _isServer = isServer;
    }
    void setServerAdapter(ServerAdapter *serverAdapter) {
        _serverAdapter = serverAdapter;
    }
    void setIPacketHandler(IPacketHandler *clientAdapter) {
        _clientAdapter = clientAdapter;
    }
    void setServerPacketStream(PacketStream *packetStream) {
        _packetStream = packetStream;
    }
    /*override*/ virtual bool handleReadEvent();
    /*override*/ virtual bool handleWriteEvent();
    /*override*/ virtual bool handleErrorEvent() {
        return true;
    };
    virtual bool checkTimeout();
private:
    Packet* getOnePacket(bool &closed);
//for test
public:
    std::list<Packet*>& getPacketList() {
        return _packetList;
    }
private:
    bool _isServer;
    PacketStream *_packetStream;
    std::list<Packet*> _packetList;
    util::ThreadMutex _packetLock;
    ServerAdapter *_serverAdapter;
    IPacketHandler *_clientAdapter;
    SessionPool _sessionPool;
    int64_t _timeout;
};

TNET_TYPEDEF_PTR(TcpConnection);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPCONNECTION_H
