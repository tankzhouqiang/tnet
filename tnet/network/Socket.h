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

    int readn(void *buf, size_t n, bool isBlock = true) {
        size_t nleft = n;
        char *ptr = (char*)buf;
        ssize_t nread;
        while (nleft > 0) {
            if ((nread = read(_socketFd, ptr, nleft)) <= 0) {
                if (errno == EINTR) {
                    nread = 0;
                } else if (errno == EAGAIN) {
		  if (isBlock) {
		    nread = 0;
		  } else {
		    return nread;
		  }
		} else {
                    return nread;
                }
            }
            nleft -= nread;
            ptr += nread;
        }
        return (n - nleft);
    }

    ssize_t writen(void *buf, size_t n) {
        size_t nleft = n ;
        char *ptr = (char*)buf;
        ssize_t nwrite = 0;
        while (nleft > 0) {
            if ((nwrite = write(_socketFd, ptr, nleft)) <= 0) {
                if (nwrite < 0 && (errno == EINTR || errno == EAGAIN)) {
                    nwrite = 0;
                } else {
                    return nwrite;
                }
            }
            nleft -= nwrite;
            ptr += nwrite;
        }
        return (n);
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
