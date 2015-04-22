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
    
    ssize_t readn(void *buf, size_t n) {
//        size_t nleft = n ;
        char *ptr = (char*)buf;
        size_t nread;
        size_t res = -1;
        std::cout << "need read in socket" << n << std::endl;            
        do {
            res = ::read(_socketFd, ptr, n);
            if (res > 0)
            {
                return res;
            }
        } while (-1 == res && errno == EINTR);
        return res;

        // while (nleft > 0) {
        //     if ((nread = read(_socketFd, ptr, nleft)) < 0) {
        //         if (errno == EINTR) {
        //             nread = 0;
        //         } else {
        //             return -1;
        //         } 
        //     } else if (nread == 0) {
        //         break;
        //     }
        //     if (errno != 0) {
        //         return -1;
        //     } 
        //     nleft -= nread;
        //     ptr += nread;
        //     std::cout << errno << " read in socket" << nread << std::endl;            
        // }
        // return (n - nleft);
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
