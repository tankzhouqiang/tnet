#ifndef TNET_PACKET_H
#define TNET_PACKET_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class Packet
{
public:
    Packet();
    ~Packet();
private:
    Packet(const Packet &);
    Packet& operator=(const Packet &);
public:

private:
};

TNET_TYPEDEF_PTR(Packet);

TNET_END_NAMESPACE(network);

#endif //TNET_PACKET_H
