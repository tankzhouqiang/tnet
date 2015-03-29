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
    static const std::string IP_PORT_SEPARATOR;
public:
    TcpAcceptor();
    ~TcpAcceptor();
private:
    TcpAcceptor(const TcpAcceptor &);
    TcpAcceptor& operator=(const TcpAcceptor &);
public:
    bool init(const std::string& spec, ServerAdapter *adapter);
private:
    bool parseAddress(const std::string& spec, std::string& ip, int& port);
private:
    ServerAdapter *_serverAdapter;
};

TNET_TYPEDEF_PTR(TcpAcceptor);

TNET_END_NAMESPACE(network);

#endif //TNET_TCPACCEPTOR_H
