#ifndef TNET_TCPACCEPTOR_H
#define TNET_TCPACCEPTOR_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>
#include <tnet/network/ServerAdapter.h>
#include <tnet/network/ServerSocket.h>
#include <tnet/network/Transport.h>

TNET_BEGIN_NAMESPACE(network);
class Transport;

class TcpAcceptor : public IOComponent
{
public:
    TcpAcceptor();
    ~TcpAcceptor();
private:
    TcpAcceptor(const TcpAcceptor &);
    TcpAcceptor& operator=(const TcpAcceptor &);
public:
    bool init(const std::string& ip, int port, 
              ServerAdapter *adapter, EpollEvent *epollEvent, 
              PacketStream *packetStream);
    void setTransport(Transport *transport);
    /*override*/ virtual bool handleReadEvent();
    /*override*/ virtual bool handleWriteEvent() {assert(false);}
    /*override*/ virtual bool handleErrorEvent() {
        return true;
    };
private:
    ServerAdapter *_serverAdapter;
    Transport *_ownTransport;
    EpollEvent *_epollEvent;
    PacketStream *_packetStream;
};

TNET_TYPEDEF_PTR(TcpAcceptor);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPACCEPTOR_H
