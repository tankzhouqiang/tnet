#ifndef TNET_IPACKETHANDLER_H
#define TNET_IPACKETHANDLER_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class IPacketHandler
{
public:
    IPacketHandler();
    ~IPacketHandler();
private:
    IPacketHandler(const IPacketHandler &);
    IPacketHandler& operator=(const IPacketHandler &);
public:

private:
};

TNET_TYPEDEF_PTR(IPacketHandler);

TNET_END_NAMESPACE(network);

#endif //TNET_IPACKETHANDLER_H
