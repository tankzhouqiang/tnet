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
    return true;
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
    
    if (_socket->readn((void*)dataBuffer.getData(), 
                       PacketHeader::PACKET_HEADER_LEN)
        != PacketHeader::PACKET_HEADER_LEN) 
    {
        return NULL;
    }
    dataBuffer.pourData(PacketHeader::PACKET_HEADER_LEN);
    uint32_t bodyLen = dataBuffer.onlyReadUInt32();
    cout << "bodyLen" << bodyLen << endl;
    dataBuffer.ensureFree(bodyLen);
    cout << "bodyLen1111" << bodyLen << endl;
    if (_socket->readn((void*)dataBuffer.getFree(), bodyLen) 
        != bodyLen) 
    {
        return NULL;
    }
    dataBuffer.pourData(bodyLen);
    cout << "bodyLen2222" << bodyLen << endl;
    Packet *packet = _packetStream->decode(&dataBuffer);
    if (!packet) {
        LOG(ERROR) << "decode packet error" << endl;
        return NULL;
    }
    cout << "bodyLen333" << bodyLen << endl;
    return packet;
}

void TcpConnection::handleReadEvent() {
    while (true) {
        cout << "handleReadEvent in tcpconnection" << endl;
        Packet *packet = getOnePacket();
        if (!packet)  {
            cout << "handleReadEvent packet empty." << endl;
            break;
        }
        if (_isServer) {
            _serverAdapter->handlePacket(packet, this);
        } else {
            uint32_t sessionId = packet->getSessionId();
            Session *session = _sessionPool.getSession(sessionId);
            if (!session) {
                LOG(ERROR) << "session Id " << sessionId << "is not existed" << endl;
                continue;
            }
            cout << "client recvie sessionId" << sessionId << endl;
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
        cout << "write data" << dataLen << endl;
        cout << *(uint32_t*) dataBuffer.getData();
        if (_socket->writen(dataBuffer.getData(), dataLen) != dataLen)
        {
            LOG(ERROR) << "write data error" << endl;
        }
        delete packet;
    }
    _packetList.clear();
}

TNET_END_NAMESPACE(network);

