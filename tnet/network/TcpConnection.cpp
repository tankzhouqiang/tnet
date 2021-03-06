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
    , _timeout(DEFAULT_TIMEOUT)
{ 
}

TcpConnection::~TcpConnection() { 
}

bool TcpConnection::init(const string&ip, int port, 
                         PacketStream *packetStream, int64_t timeout) 
{
    _socket = new ClientSocket(ip, port);
    if (!_socket->init()) {
        delete _socket;
        return false;
    }
    _socket->setIOComponent(this);
    assert(packetStream);
    _packetStream = packetStream;
    _timeout = timeout;
    return true;
}

bool TcpConnection::postPacket(Packet *packet, IPacketHandler *packetHandler,
                               void *args, bool block) 
{
    if (!packet) {
        LOG(ERROR) << "packet is empty" << endl;
        return false;
    }
    if (!_isServer) {
      if (!block && _sessionPool.getSessionCount() > MAX_PACKET_SIZE) {
	LOG(ERROR) << "send packet list is full." << endl;
	return false;
      } 
      while (block && _sessionPool.getSessionCount() > MAX_PACKET_SIZE) {
	usleep(SEND_WAIT_TIME);
      }
        uint32_t sessionId = _sessionPool.allocateSession(
                packetHandler, args, packet, _timeout);
        packet->setSessionId(sessionId);
    }
    {
        util::ScopedLock lock(_packetLock);
        _packetList.push_back(packet);
    }
    return true;
}

int TcpConnection::readSocket(int readSize) {
    _inputDataBuff.ensureFree(readSize);
    int readLen = _socket->readn((void*)_inputDataBuff.getFree(), 
				 readSize);
    return readLen;
}

Packet* TcpConnection::getOnePacket(bool &closed) {
    if (_inputDataBuff.getDataLen() < PacketHeader::PACKET_HEADER_LEN) {
        int ret = readSocket(DEFAULT_SOCKET_READ_SIZE);
        if (ret > 0) {
            _inputDataBuff.pourData(ret);
            if (ret < PacketHeader::PACKET_HEADER_LEN) {
                return NULL;
            }
        } else {
            return NULL;
        }
    }
    uint32_t bodyLen = _inputDataBuff.onlyReadUInt32();
    int packetLen = bodyLen + PacketHeader::PACKET_HEADER_LEN;
    if (_inputDataBuff.getDataLen() < packetLen) {
        int needSize = packetLen - _inputDataBuff.getDataLen();
        int readSize = needSize > DEFAULT_SOCKET_READ_SIZE ?
                       needSize : DEFAULT_SOCKET_READ_SIZE;
        int ret = readSocket(readSize);
        if (ret > 0) {
            _inputDataBuff.pourData(ret);
            if (ret < needSize) {
                return NULL;
            }
        } else {
            return NULL;
        }
    }
    
    //todo how to process close
    // if (readLen == 0) {
    //     closed = true;
    //     return NULL;
    // }

    Packet *packet = _packetStream->decode(&_inputDataBuff);
    if (!packet) {
        LOG(ERROR) << "decode packet error" << endl;
        return NULL;
    }
    _inputDataBuff.shrink();
    return packet;
}

bool TcpConnection::handleReadEvent() {
    while (true) {
        bool closed = false;
        Packet *packet = getOnePacket(closed);
        if (!packet)  {
            if (closed) {
                return false;
            } else {
                return true;
            }
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
            IPacketHandler *handler = session->_handler;
	    //	    cout << "sessionId: " << sessionId << endl;
            handler->handlePacket(packet, session->_args);
            delete packet;
            delete session;
        }
    }
    return true;
}

bool TcpConnection::handleWriteEvent() {
    uint32_t count = 0;
    list<Packet*> sendPacketList;
    {
        int outputDataLen = _outputDataBuff.getDataLen();
        util::ScopedLock lock(_packetLock);
        uint32_t count = 0;
        for (list<Packet*>::iterator it = _packetList.begin(); 
             it != _packetList.end(); ++it)
        {
            Packet *packet = *it;
            sendPacketList.push_back(packet);
            if (++count > ONE_SEND_PACKET_COUNT) {
                break;
            }
	    //limit output buf size.
	    int packetLen = packet->getBodyLen() + PacketHeader::PACKET_HEADER_LEN;
	    outputDataLen += packetLen;
	    if (outputDataLen > MAX_DATABUF_SIZE) {
	      break;
	    }
        }
        for (uint32_t i = 0; i < count; ++i) {
            _packetList.pop_front();
        }
    }
    
    for (list<Packet*>::iterator it = sendPacketList.begin(); 
         it != sendPacketList.end(); ++it)
    {
        DataBuffer dataBuffer;
        Packet *packet = *it;
        assert(packet);
        if (!_packetStream->encode(packet, &_outputDataBuff)) {
            LOG(ERROR) << "encode packet error" << endl;
            delete packet;
            continue;
        }
        delete packet;
    }
    int dataLen = _outputDataBuff.getDataLen();
    if (dataLen > 0) {
        int ret = _socket->writen(_outputDataBuff.getData(), 
                dataLen);
        if (ret > 0) {
            _outputDataBuff.drainData(ret);
        }
        _outputDataBuff.shrink();
    }
}

bool TcpConnection::checkTimeout() {
    _sessionPool.checkTimeout();
}

TNET_END_NAMESPACE(network);

