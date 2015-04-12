#ifndef TNET_SESSION_H
#define TNET_SESSION_H

#include <tnet/common/Common.h>
#include <tnet/network/IPacketHandler.h>

TNET_BEGIN_NAMESPACE(network);

class Session
{
public:
    Session(IPacketHandler *handler, void *args);
    ~Session();
private:
    Session(const Session &);
    Session& operator=(const Session &);
public:
    IPacketHandler *_handler;
    void *_args;
};

TNET_TYPEDEF_PTR(Session);

TNET_END_NAMESPACE(network);

#endif //TNET_SESSION_H
