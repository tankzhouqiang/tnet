#include <tnet/network/TcpAcceptor.h>
#include <tnet/util/StringUtil.h>
using namespace std;
TNET_BEGIN_NAMESPACE(network);

TcpAcceptor::TcpAcceptor() 
    : _serverAdapter(NULL)
{
}

TcpAcceptor::~TcpAcceptor() {
}

bool TcpAcceptor::init(const string& ip, int port, 
                       ServerAdapter *adapter) 
{
    _socket = new ServerSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    _serverAdapter = adapter;
    
    return true;
}


TNET_END_NAMESPACE(network);

