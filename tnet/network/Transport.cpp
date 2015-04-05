#include <tnet/network/Transport.h>
#include <tnet/util/StringUtil.h>
#include <stdlib.h>
using namespace std;
TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

const string Transport::IP_PORT_SEPARATOR = ":";

Transport::Transport() 
    : _tcpAcceptor(NULL)
    , _epollEvent(NULL)
    , _start(false)
{ 
}

Transport::~Transport() { 
    DELETE_AND_SET_NULL(_epollEvent);
    DELETE_AND_SET_NULL(_tcpAcceptor);
}

bool Transport::init(const string& spec, PacketStream *packetStream, 
                     ServerAdapter *adapter)
 {
    assert(adapter);
    _tcpAcceptor = new TcpAcceptor();
    string ip;
    int port;
    if (!parseAddress(spec, ip, port)) {
        return false;
    }
    if (!_tcpAcceptor->init(ip, port, adapter)) {
        return false;
    }
    _epollEvent = new EpollEvent();
    Socket *socket = _tcpAcceptor->getSocket();
    if (!_epollEvent->addEvent(socket, true, true)) {
        LOG(ERROR) << "add epoll listen event error" << endl;
        return false;
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

bool Transport::startServer() {
}


bool Transport::connect(const string& spec, PacketStream *packetStream)
{
    string ip;
    int port;
    if (!parseAddress(spec, ip, port)) {
        return false;
    }
}

bool Transport::startClient() {
}

void Transport::stop() {
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

