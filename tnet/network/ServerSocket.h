#ifndef TNET_SERVERSOCKET_H
#define TNET_SERVERSOCKET_H

#include <tnet/common/Common.h>
#include <tnet/network/Socket.h>

TNET_BEGIN_NAMESPACE(network);

class ServerSocket : public Socket
{
public:
    static const int DEFAULT_BACK_LOG = 256;
public:
    ServerSocket(const std::string& ip, int port);
    ServerSocket() {}
    ~ServerSocket();
private:
    ServerSocket(const ServerSocket &);
    ServerSocket& operator=(const ServerSocket &);
public:
    /*overvide*/ bool init();
public:
    bool bind(const struct sockaddr_in& serverAddr);
    bool listen();
    ServerSocket* accept();
private:
    int _backLog;
    std::string _ip;
    int _port;
};

TNET_TYPEDEF_PTR(ServerSocket);

TNET_END_NAMESPACE(network);

#endif //TNET_SERVERSOCKET_H
