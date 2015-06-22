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

    int readn(void *buf, size_t n) {
        int res;
        do {
            res = ::read(_socketFd, buf, n);
        } while (res < 0 && errno == EINTR);
        return res;
    }

    int writen(void *buf, size_t n) {
        int res;
        do {
            res = ::write(_socketFd, buf, n);
        } while (res < 0 && errno == EINTR);
        return res;
    }

    int getSoError() {
        int lastError = errno;
        int  soError = 0;
        socklen_t soErrorLen = sizeof(soError);
        if (getsockopt(_socketFd, SOL_SOCKET, SO_ERROR,
                       (void *)(&soError), &soErrorLen) != 0)
        {
            return lastError;
        }
        if (soErrorLen != sizeof(soError))
            return EINVAL;

        return soError;
    }

    bool setIntOption (int option, int value);
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
