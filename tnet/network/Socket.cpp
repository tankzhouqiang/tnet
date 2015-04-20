#include <tnet/network/Socket.h>
using namespace std;

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

    int value = 1;
    bool rc = (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR,
                     (const void *)(&value), sizeof(value)) == 0);
    if (!rc) {
        LOG(ERROR) << "set SO_REUSEADDR" << endl;
        return false;
    }
    return true;
}

TNET_END_NAMESPACE(network);

