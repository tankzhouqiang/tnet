#include <tnet/network/ClientSocket.h>

using namespace std;
TNET_BEGIN_NAMESPACE(network);

ClientSocket::ClientSocket(const string& serverIp, int serverPort) 
    : _serverIP(serverIp)
    , _serverPort(serverPort)
{ 
}

ClientSocket::~ClientSocket() { 
}

bool ClientSocket::init() {
    if (!socket()) {
        return false;
    }
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0 , sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_serverIP.data());
    serverAddr.sin_port = htons(static_cast<short>(_serverPort));
    bool ret = ::connect(_socketFd, (const struct sockaddr*) &serverAddr, 
                         sizeof(serverAddr));
    return ret;
}

TNET_END_NAMESPACE(network);

