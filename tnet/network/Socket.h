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
//        size_t nleft = n ;
        char *ptr = (char*)buf;
        size_t nread;
        int res = 0;
        do {
            res = ::read(_socketFd, ptr, n);
            if (res > 0)
            {
                return res;
            }
        } while (-1 == res && errno == EINTR);
        return res;
    }

    ssize_t writen(void *buf, size_t n) {
        size_t nleft = n ;
        char *ptr = (char*)buf;
        size_t nwrite;
        while (nleft > 0) {
            if ((nwrite = write(_socketFd, ptr, nleft)) <= 0) {
                if (nwrite < 0 && errno == EINTR) {
                    nwrite = 0;
                } else {
                    return -1;
                } 
            } else if (nwrite == 0) {
                break;
            }
            nleft -= nwrite;
            ptr += nwrite;
        }
        return n;
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
