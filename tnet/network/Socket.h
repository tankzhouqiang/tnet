#ifndef TNET_SOCKET_H
#define TNET_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>
#include <arpa/inet.h>

TNET_BEGIN_NAMESPACE(network);
class IOComponent;

class Socket
{
public:
    Socket();
    ~Socket();
private:
    Socket(const Socket &);
    Socket& operator=(const Socket &);
public:
    virtual bool init() = 0;
    void setIOComponent(IOComponent* ioComponent) {
        _ioComponent = ioComponent;
    }
    IOComponent* getIOComponent() const {
        return _ioComponent;
    }
    int getSocketFd() const {
        return _socketFd;
    }
    void setSocketFd(int socketFd) {
        _socketFd = socketFd;
    }
protected:
    bool socket();

protected:
    int _socketFd;
private:
    IOComponent *_ioComponent;
};

TNET_TYPEDEF_PTR(Socket);

TNET_END_NAMESPACE(network);

#endif //TNET_SOCKET_H
