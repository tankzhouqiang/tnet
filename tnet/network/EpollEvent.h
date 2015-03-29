#ifndef TNET_EPOLLEVENT_H
#define TNET_EPOLLEVENT_H

#include <tnet/common/Common.h>
#include <tnet/network/Socket.h>
#include <tnet/network/IOEvent.h>

TNET_BEGIN_NAMESPACE(network);

class EpollEvent
{
public:
    static const uint32_t MAX_SOCKET_EVENTS_COUNT = 256;
public:
    EpollEvent();
    ~EpollEvent();
public:
    bool addEvent(Socket *socket, bool enableRead, bool enableWrite);
    int getEvents(int timeout, IOEvent *ioevents, int cnt);
    bool removeEvent(Socket *socket);
private:
    EpollEvent(const EpollEvent &);
    EpollEvent& operator=(const EpollEvent &);
public:
    
private:
    int _iepfd;    // epoll的fd
};

TNET_TYPEDEF_PTR(EpollEvent);

TNET_END_NAMESPACE(network);

#endif //TNET_EPOLLEVENT_H
