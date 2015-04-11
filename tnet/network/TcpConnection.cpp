#include <tnet/network/TcpConnection.h>
#include <tnet/network/ClientSocket.h>

using namespace std;
TNET_BEGIN_NAMESPACE(network);

TcpConnection::TcpConnection() 
    : _packetStream(NULL)
{ 
}

TcpConnection::~TcpConnection() { 
}

bool TcpConnection::init(const string&ip, int port, 
                         PacketStream *packetStream) 
{
    _socket = new ClientSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    assert(packetStream);
    _packetStream = packetStream;
    return _socket->init();
}

bool TcpConnection::postPacket(Packet *packet) {
    if (!packet) {
        LOG(ERROR) << "packet is empty" << endl;
        return false;
    }
    {
        util::ScopedLock lock(_packetLock);
        _packetList.push_back(packet);
    }
    return true;
}
TNET_END_NAMESPACE(network);

