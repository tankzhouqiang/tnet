#include <tnet/network/Transport.h>
#include <tnet/util/StringUtil.h>
#include <tnet/util/Thread.h>
#include <stdlib.h>

using namespace std;
TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

const string Transport::IP_PORT_SEPARATOR = ":";

Transport::Transport() 
    : _start(false)
{
    _epollEvent = new EpollEvent(); 
}

Transport::~Transport() { 
    DELETE_AND_SET_NULL(_epollEvent);
    std::vector<IOComponent*>::iterator it = _ioComponentVec.begin();
    for (; it != _ioComponentVec.end(); ++it) {
        delete *it;
    }
    _ioComponentVec.clear();
}

bool Transport::init(const string& spec, PacketStream *packetStream, 
                     ServerAdapter *adapter)
 {
    assert(adapter);
    string ip;
    int port;
    if (!parseAddress(spec, ip, port)) {
        return false;
    }
    
    TcpAcceptor *tcpAcceptor = new TcpAcceptor();
    if (!tcpAcceptor->init(ip, port, adapter, _epollEvent)) {
        return false;
    }
    tcpAcceptor->setTransport(this);
    Socket *socket = tcpAcceptor->getSocket();
    if (!_epollEvent->addEvent(socket, true, false)) {
        LOG(ERROR) << "add epoll listen event error" << endl;
        return false;
    }
    {
        ScopedLock lock(_ioComponentVecLock);
        _ioComponentVec.push_back(tcpAcceptor);
    }
    return true;
}

bool Transport::ioLoop() {
    IOEvent ioEvents[EpollEvent::MAX_SOCKET_EVENTS_COUNT];
    while (_start) {
        int cnt = _epollEvent->getEvents(1000, ioEvents, 
                EpollEvent::MAX_SOCKET_EVENTS_COUNT);
        if (cnt < 0) {
            LOG(ERROR) << "get epoll event error" << endl;
            continue;
        }
        for (int i = 0; i < cnt; ++i) {
            IOComponent *ioComponent = ioEvents[i]._ioc;
            if (ioComponent == NULL) {
                continue;
            }
            if (ioEvents[i]._readOccurred == true) {
                cout << "handleReadEvent" << endl;
                ioComponent->handleReadEvent();
            }
            if (ioEvents[i]._writeOccurred == true) {
                ioComponent->handleWriteEvent();
            }
            if (ioEvents[i]._errorOccurred == true) {
                ioComponent->handleErrorEvent();
            }
        }
    }
}

bool Transport::start() {
    _start = true;
    
    _ioThreadPtr = Thread::createThread(
            tr1::bind(&Transport::ioLoop, this));
    if (!_ioThreadPtr) {
        LOG(ERROR) << "start io thread error" << endl;
        return false;
    }
    return true;
}

void Transport::wait() {
    while (_start) {
        usleep(1000);
    }
}

void Transport::stop() {
    _start = true;
}

TcpConnection* Transport::connect(const string& spec, 
                                  PacketStream *packetStream)
{
    string ip;
    int port;
    if (!parseAddress(spec, ip, port)) {
        return NULL;
    }
    TcpConnection *connection = new TcpConnection();
    if (!connection->init(ip, port, packetStream)) {
        LOG(ERROR) << "tcp connection error";
        return NULL;
    }
    Socket *socket = connection->getSocket();
    assert(socket);
    if (!_epollEvent->addEvent(socket, true, true)) {
        LOG(ERROR) << "connect epoll add event error.";
        return NULL;
    }
    {
        ScopedLock lock(_ioComponentVecLock);
        _ioComponentVec.push_back(connection);
    }
    return connection;
}

bool Transport::parseAddress(const string& spec, string& ip, int& port) {
    vector<string> specVec = util::StringUtil::split(spec, IP_PORT_SEPARATOR);
    if (specVec.size() != 2) {
        LOG(ERROR) <<  "ip:port format error, spec:[" << spec << "]";
        return false;
    }
    ip = specVec[0];
    const string& portStr = specVec[1];
    port = atoi(portStr.data());
    return true;
}

TNET_END_NAMESPACE(network);

