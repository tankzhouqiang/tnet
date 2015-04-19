#include <tnet/network/TcpConnection.h>
#include <tnet/network/ClientSocket.h>

using namespace std;
TNET_USE_NAMESPACE(util);
TNET_BEGIN_NAMESPACE(network);

TcpConnection::TcpConnection() 
    : _isServer(false)
    , _packetStream(NULL)
    , _serverAdapter(NULL)
    , _clientAdapter(NULL)
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

bool TcpConnection::postPacket(Packet *packet, IPacketHandler *packetHandler,
                               void *args) 
{
    if (!packet) {
        LOG(ERROR) << "packet is empty" << endl;
        return false;
    }
    if (!_isServer) {
        uint32_t sessionId = _sessionPool.allocateSession(
                packetHandler, args);
        packet->setSessionId(sessionId);
    }
    {
        util::ScopedLock lock(_packetLock);
        _packetList.push_back(packet);
    }
    return true;
}

Packet* TcpConnection::getOnePacket() {
    DataBuffer dataBuffer;
    dataBuffer.ensureFree(PacketHeader::PACKET_HEADER_LEN);
    
    if (_socket->readn((void*)dataBuffer.getFree(), 
                       PacketHeader::PACKET_HEADER_LEN)
        != PacketHeader::PACKET_HEADER_LEN) 
    {
        return NULL;
    }
    dataBuffer.pourData(PacketHeader::PACKET_HEADER_LEN);
    uint32_t bodyLen = *(uint32_t*) dataBuffer.getData();
    dataBuffer.ensureFree(bodyLen);
    if (_socket->readn((void*)dataBuffer.getFree(), bodyLen) 
        != bodyLen) 
    {
        return NULL;
    }
    Packet *packet = _packetStream->decode(&dataBuffer);
    if (packet) {
        LOG(ERROR) << "decode packet error" << endl;
        return NULL;
    }
    return packet;
}

void TcpConnection::handleReadEvent() {
    while (true) {
        Packet *packet = getOnePacket();
        if (!packet)  {
            break;
        }
        if (_isServer) {
            _serverAdapter->handlePacket(packet);
        } else {
            uint32_t sessionId = packet->getSessionId();
            Session *session = _sessionPool.getSession(sessionId);
            if (!session) {
                LOG(ERROR) << "session Id " << sessionId << "is not existed" << endl;
                continue;
            }
            IPacketHandler *_handler = session->_handler;
            _handler->handlePacket(packet, session->_args);
        }
        delete packet;
    }
}

void TcpConnection::handleWriteEvent() {
    util::ScopedLock lock(_packetLock);
    for (list<Packet*>::iterator it = _packetList.begin(); 
         it != _packetList.end(); ++it) 
    {
        DataBuffer dataBuffer;
        Packet *packet = *it;
        assert(packet);
        if (!_packetStream->encode(packet, &dataBuffer)) {
            LOG(ERROR) << "encode packet error" << endl;
            delete packet;
            continue;
        }
        int dataLen = dataBuffer.getDataLen();
        if (_socket->writen(dataBuffer.getData(), dataLen) != dataLen)
        {
            LOG(ERROR) << "write data error" << endl;
        }
        delete packet;
    }
    _packetList.clear();
}

TNET_END_NAMESPACE(network);

