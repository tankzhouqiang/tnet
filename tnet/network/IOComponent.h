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
    Socket* getSocket() const {
        return _socket;
    }
protected:
    Socket *_socket;
};

TNET_TYPEDEF_PTR(IOComponent);

TNET_END_NAMESPACE(network);

#endif //TNET_IOCOMPONENT_H
