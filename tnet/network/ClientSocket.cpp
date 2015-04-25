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
    int ret = ::connect(_socketFd, (const struct sockaddr*) &serverAddr, 
                        sizeof(serverAddr));
    int val = fcntl(_socketFd, F_GETFL, 0);
    fcntl(_socketFd, F_SETFL, val | O_NONBLOCK);

    struct sockaddr_in clientAddr;
    if (getsockname(_socketFd, (struct sockaddr *) &clientAddr, 
                    NULL) == 0)
    {
        char buf[2048];
        LOG(INFO) << "new connection ip " << 
            inet_ntop(AF_INET, &clientAddr.sin_addr, buf, sizeof(buf)) << endl;
        LOG(INFO) << "port: " << clientAddr.sin_port << endl;
    } else {
        LOG(INFO) << "error port: " << clientAddr.sin_port << endl;
    }
    return ret == 0;
}

TNET_END_NAMESPACE(network);

