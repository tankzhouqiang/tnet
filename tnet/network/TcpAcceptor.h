#ifndef TNET_TCPACCEPTOR_H
#define TNET_TCPACCEPTOR_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class TcpAcceptor
{
public:
    TcpAcceptor();
    ~TcpAcceptor();
private:
    TcpAcceptor(const TcpAcceptor &);
    TcpAcceptor& operator=(const TcpAcceptor &);
public:

private:
};

TNET_TYPEDEF_PTR(TcpAcceptor);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPACCEPTOR_H
