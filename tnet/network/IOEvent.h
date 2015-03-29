#ifndef TNET_IOEVENT_H
#define TNET_IOEVENT_H

#include <tnet/common/Common.h>
#include <tnet/network/IOComponent.h>

TNET_BEGIN_NAMESPACE(network);

class IOEvent
{
public:
    IOEvent();
    ~IOEvent();
private:
    IOEvent(const IOEvent &);
    IOEvent& operator=(const IOEvent &);
public:
    IOComponent *_ioc;
    bool _readOccurred;
    bool _writeOccurred;
    bool _errorOccurred;
private:
};

TNET_TYPEDEF_PTR(IOEvent);

TNET_END_NAMESPACE(network);

#endif //TNET_IOEVENT_H
