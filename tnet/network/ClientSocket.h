#ifndef TNET_CLIENTSOCKET_H
#define TNET_CLIENTSOCKET_H

#include <tnet/common/Common.h>
#include <tnet/network/Socket.h>

TNET_BEGIN_NAMESPACE(network);

class ClientSocket : public Socket
{
public:
    ClientSocket(const std::string& serverIp, int serverPort);
    ~ClientSocket();
private:
    ClientSocket(const ClientSocket &);
    ClientSocket& operator=(const ClientSocket &);
public:
    bool connect();
private:
    std::string _serverIP;
    int _serverPort;
};

TNET_TYPEDEF_PTR(ClientSocket);

TNET_END_NAMESPACE(network);

#endif //TNET_CLIENTSOCKET_H
