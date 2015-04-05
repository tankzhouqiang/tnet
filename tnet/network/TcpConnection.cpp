#include <tnet/network/TcpConnection.h>
#include <tnet/network/ClientSocket.h>

using namespace std;
TNET_BEGIN_NAMESPACE(network);

TcpConnection::TcpConnection() { 
}

TcpConnection::~TcpConnection() { 
}

bool TcpConnection::init(const string&ip, int port) {
    _socket = new ClientSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    return true;
}

TNET_END_NAMESPACE(network);

