#include <tnet/network/Socket.h>
using namespace std;

TNET_BEGIN_NAMESPACE(network);

Socket::Socket() 
    : _socketFd(-1)
    , _ioComponent(NULL)
{ 
}

Socket::~Socket() { 
    ::close(_socketFd);
}

bool Socket::socket() {
    _socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd < 0) {
        LOG(ERROR) << "create socket error.";
        return false;
    }

    int value = 1;
    bool rc = (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR,
                     (const void *)(&value), sizeof(value)) == 0);
    if (!rc) {
        LOG(ERROR) << "set SO_REUSEADDR" << endl;
        return false;
    }

    if (!setIntOption(SO_SNDBUF, 640000)) {                                     
        return false;                                                           
    }                                                                           
    if (!setIntOption(SO_RCVBUF, 640000)) {                                     
        return false;                                                           
    }                                                                           
    return true;
}

bool Socket::setIntOption (int option, int value) {
    bool rc = false;
    rc = setsockopt(_socketFd, SOL_SOCKET, option,
                    (const void *)(&value), sizeof(value)) == 0;
    return rc;
}

TNET_END_NAMESPACE(network);

