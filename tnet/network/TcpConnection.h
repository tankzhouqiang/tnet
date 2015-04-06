#ifndef TNET_TCPCONNECTION_H
#define TNET_TCPCONNECTION_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>
#include <tnet/network/PacketStream.h>

TNET_BEGIN_NAMESPACE(network);

class TcpConnection : public IOComponent
{
public:
    TcpConnection();
    ~TcpConnection();
private:
    TcpConnection(const TcpConnection &);
    TcpConnection& operator=(const TcpConnection &);
public:
    bool init(const std::string&ip, int port, 
              PacketStream *packetStream);
    
    /*override*/ virtual void handleReadEvent() {assert(false);}
    /*override*/ virtual void handleWriteEvent() {assert(false);}
    /*override*/ virtual void handleErrorEvent() {assert(false);};
private:
    PacketStream *_packetStream;
};

TNET_TYPEDEF_PTR(TcpConnection);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPCONNECTION_H
