#ifndef TNET_TCPCONNECTION_H
#define TNET_TCPCONNECTION_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>

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
    bool init(const std::string&ip, int port);
private:
};

TNET_TYPEDEF_PTR(TcpConnection);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPCONNECTION_H
