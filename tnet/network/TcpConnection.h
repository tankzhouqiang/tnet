#ifndef TNET_TCPCONNECTION_H
#define TNET_TCPCONNECTION_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class TcpConnection
{
public:
    TcpConnection();
    ~TcpConnection();
private:
    TcpConnection(const TcpConnection &);
    TcpConnection& operator=(const TcpConnection &);
public:
    bool init(const std::string&ip, const std::string& port);
private:
};

TNET_TYPEDEF_PTR(TcpConnection);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPCONNECTION_H
