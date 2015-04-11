#include <tnet/network/TcpAcceptor.h>
#include <tnet/util/StringUtil.h>
using namespace std;
TNET_BEGIN_NAMESPACE(network);

TcpAcceptor::TcpAcceptor() 
    : _serverAdapter(NULL)
    , _ownTransport(NULL)
    , _epollEvent(NULL)
{
}

TcpAcceptor::~TcpAcceptor() {
}

bool TcpAcceptor::init(const string& ip, int port, 
                       ServerAdapter *adapter, 
                       EpollEvent *epollEvent) 
{
    _socket = new ServerSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    _serverAdapter = adapter;
    _epollEvent = epollEvent;
    return true;
}

void TcpAcceptor::setTransport(Transport *transport) {
    _ownTransport = transport;
}

void TcpAcceptor::handleReadEvent() {
    LOG(INFO) << "new connection." << endl;
    assert(_socket);
    ServerSocket *serverSocket = dynamic_cast<ServerSocket*> (_socket);
    assert(serverSocket);
    ServerSocket *newSocket = serverSocket->accept();
    if (!newSocket) {
        return ;
    }
    TcpConnection *connection = new TcpConnection();
    connection->setSocket(newSocket);
    assert(_ownTransport);
    _ownTransport->addIOComponent(connection);
    assert(_epollEvent);
    _epollEvent->addEvent(newSocket, true, true);
}


TNET_END_NAMESPACE(network);

