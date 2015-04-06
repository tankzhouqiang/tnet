#ifndef TNET_TCPACCEPTOR_H
#define TNET_TCPACCEPTOR_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>
#include <tnet/network/ServerAdapter.h>
#include <tnet/network/ServerSocket.h>

TNET_BEGIN_NAMESPACE(network);

class TcpAcceptor : public IOComponent
{
public:
    TcpAcceptor();
    ~TcpAcceptor();
private:
    TcpAcceptor(const TcpAcceptor &);
    TcpAcceptor& operator=(const TcpAcceptor &);
public:
    bool init(const std::string& ip, int port, ServerAdapter *adapter);

    /*override*/ virtual void handleReadEvent() {assert(false);}
    /*override*/ virtual void handleWriteEvent() {assert(false);}
    /*override*/ virtual void handleErrorEvent() {assert(false);};
private:
    ServerAdapter *_serverAdapter;
};

TNET_TYPEDEF_PTR(TcpAcceptor);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPACCEPTOR_H
