#include <tnet/network/EpollEvent.h>
#include <tnet/network/IOComponent.h>
#include <tnet/network/Socket.h>
#include <sys/epoll.h>

TNET_BEGIN_NAMESPACE(network);

EpollEvent::EpollEvent() {
    _iepfd = epoll_create(MAX_SOCKET_EVENTS_COUNT);
}

EpollEvent::~EpollEvent() {
    close(_iepfd);
}

bool EpollEvent::addEvent(Socket *socket, bool enableRead, bool enableWrite) {
    assert(socket);
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = socket->getIOComponent();
    
    ev.events = 0; //level triggered
    if (enableRead) {
        ev.events |= EPOLLIN;
    }
    if (enableWrite) {
        ev.events |= EPOLLOUT;
    }
    
    if (epoll_ctl(_iepfd, EPOLL_CTL_ADD, socket->getSocketFd(), &ev) != 0) {
        LOG(ERROR) << "epoll ctl add error";
        return false;
    }
    return true;
}

int EpollEvent::getEvents(int timeout, IOEvent *ioevents, int cnt) {
    struct epoll_event events[MAX_SOCKET_EVENTS_COUNT];

    if (cnt > MAX_SOCKET_EVENTS_COUNT) {
        cnt = MAX_SOCKET_EVENTS_COUNT;
    }
    int res = epoll_wait(_iepfd, events, cnt, timeout);
    
    if (res > 0) {
        memset(ioevents, 0, sizeof(IOEvent) * res);
    }
    for (int i = 0;  i < res; ++i) {
        ioevents[i]._ioc = 
            reinterpret_cast<IOComponent*> (events[i].data.ptr);
        if ((events[i].events & EPOLLIN) != 0) {
            ioevents[i]._readOccurred = true;
        }
        if ((events[i].events & EPOLLOUT) != 0) {
            ioevents[i]._writeOccurred = true;
        }
        if (events[i].events & (EPOLLERR | EPOLLHUP)) {
            ioevents[i]._errorOccurred = true;
        }
    }
    return res;
}

bool EpollEvent::removeEvent(Socket *socket) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = socket->getIOComponent();
    ev.events = 0;
    if (epoll_ctl(_iepfd, EPOLL_CTL_DEL, socket->getSocketFd(), &ev) != 0) {
        LOG(ERROR) << "epoll ctl delete error";
        return false;
    }
    return true;
}


TNET_END_NAMESPACE(network);

