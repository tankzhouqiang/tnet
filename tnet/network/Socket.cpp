#include <tnet/network/Socket.h>

TNET_BEGIN_NAMESPACE(network);

Socket::Socket() 
    : _socketFd(-1)
    , _ioComponent(NULL)
{ 
}

Socket::~Socket() { 
}

bool Socket::socket() {
    _socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd < 0) {
        LOG(ERROR) << "create socket error.";
        return false;
    }
    return true;
}

TNET_END_NAMESPACE(network);

