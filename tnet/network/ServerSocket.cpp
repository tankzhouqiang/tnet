#include <tnet/network/ServerSocket.h>
#include <fcntl.h>

using namespace std;
TNET_BEGIN_NAMESPACE(network);

ServerSocket::ServerSocket(const std::string& ip, const int port) 
    : _ip(ip)
    , _port(port)
    , _backLog(DEFAULT_BACK_LOG)
{ 
}

ServerSocket::~ServerSocket() { 
}

bool ServerSocket::init() {
    if (!socket()) {
        return false;
    }
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0 , sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_ip.data());
    serverAddr.sin_port = htons(static_cast<short>(_port));
    if (bind(serverAddr) < 0) {
        return false;
    }
    if (listen() < 0) {
        return false;
    }
    return true;
}

bool ServerSocket::bind(const struct sockaddr_in& serverAddr) {
    if (::bind(_socketFd, (const struct sockaddr*) &serverAddr, 
               sizeof(serverAddr)) < 0)
    {
        LOG(ERROR) << "bind error" << endl;
        return false;
    }
    return true;
}

bool ServerSocket::listen() {
    if (::listen(_socketFd, _backLog) < 0) {
        LOG(ERROR) << "listen error" << endl;
        return false;
    }
    return true;
}

ServerSocket* ServerSocket::accept() {
    struct sockaddr_in clientAddr;
    socklen_t len;
    int connFd = ::accept(_socketFd, (struct sockaddr*)&clientAddr, &len);
    if (connFd < 0) {
        LOG(ERROR) << "accept error" << endl;
        return NULL;
    }
    int val = fcntl(connFd, F_GETFL, 0);
    fcntl(connFd, F_SETFL, val | O_NONBLOCK);

    char buf[2048];
    LOG(INFO) << "new connection from " << 
        inet_ntop(AF_INET, &clientAddr.sin_addr, buf, sizeof(buf)) << endl;
    LOG(INFO) << "port: " << clientAddr.sin_port << endl;
    ServerSocket *socket = new ServerSocket();
    socket->setSocketFd(connFd);
    
    return socket;
}

TNET_END_NAMESPACE(network);

