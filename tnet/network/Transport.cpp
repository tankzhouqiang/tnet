#include <tnet/network/Transport.h>
#include <tnet/util/StringUtil.h>

using namespace std;
TNET_USE_NAMESPACE(util);

TNET_BEGIN_NAMESPACE(network);

Transport::Transport() 
    : _threadCount(DEFAULT_THREAD_COUNT)
    , _tcpAcceptor(NULL)
    , _epollEvent(NULL)
{ 
}

Transport::~Transport() { 
    DELETE_AND_SET_NULL(_epollEvent);
    DELETE_AND_SET_NULL(_tcpAcceptor);
}

void Transport::setThreadCount(uint32_t threadCount) {
    _threadCount = threadCount;
}

bool Transport::init(const string& spec, ServerAdapter *adapter) {
    assert(adapter);
    _tcpAcceptor = new TcpAcceptor();
    if (!_tcpAcceptor->init(spec, adapter)) {
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

bool Transport::startServer() {
    
}


bool Transport::connect(const string& spec, ClientAdapter *adapter, 
                        void *args)
{
}

bool Transport::startClient() {
}

void Transport::stop() {
}

TNET_END_NAMESPACE(network);

