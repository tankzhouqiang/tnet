#ifndef TNET_CLIENTSOCKET_H
#define TNET_CLIENTSOCKET_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class ClientSocket
{
public:
    ClientSocket();
    ~ClientSocket();
private:
    ClientSocket(const ClientSocket &);
    ClientSocket& operator=(const ClientSocket &);
public:

private:
};

TNET_TYPEDEF_PTR(ClientSocket);

TNET_END_NAMESPACE(network);

#endif //TNET_CLIENTSOCKET_H
