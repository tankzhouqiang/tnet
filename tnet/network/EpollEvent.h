#ifndef TNET_EPOLLEVENT_H
#define TNET_EPOLLEVENT_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class EpollEvent
{
public:
    EpollEvent();
    ~EpollEvent();
private:
    EpollEvent(const EpollEvent &);
    EpollEvent& operator=(const EpollEvent &);
public:

private:
};

TNET_TYPEDEF_PTR(EpollEvent);

TNET_END_NAMESPACE(network);

#endif //TNET_EPOLLEVENT_H
