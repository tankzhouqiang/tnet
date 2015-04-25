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
    virtual bool handleReadEvent() = 0;
    virtual bool handleWriteEvent() = 0;
    virtual bool handleErrorEvent() = 0;

    Socket* getSocket() const {
        return _socket;
    }

    void setSocket(Socket *socket) {
        assert(socket);
        _socket = socket;
    }
    bool getClosed() const {
        return _closed;
    }
    void setClosed(bool closed) {
        _closed = closed;
    }
protected:
    Socket *_socket;
    bool _closed;
};

TNET_TYPEDEF_PTR(IOComponent);

TNET_END_NAMESPACE(network);

#endif //TNET_IOCOMPONENT_H
