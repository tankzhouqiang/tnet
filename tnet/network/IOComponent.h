#ifndef TNET_IOCOMPONENT_H
#define TNET_IOCOMPONENT_H

#include <tnet/common/Common.h>
#include <tnet/network/Socket.h>

TNET_BEGIN_NAMESPACE(network);
class Socket;

class IOComponent
{
public:
    IOComponent();
    ~IOComponent();
private:
    IOComponent(const IOComponent &);
    IOComponent& operator=(const IOComponent &);
public:
    virtual void handleReadEvent() = 0;
    virtual void handleWriteEvent() = 0;
    virtual void handleErrorEvent() = 0;

    Socket* getSocket() const {
        return _socket;
    }
protected:
    Socket *_socket;
};

TNET_TYPEDEF_PTR(IOComponent);

TNET_END_NAMESPACE(network);

#endif //TNET_IOCOMPONENT_H
