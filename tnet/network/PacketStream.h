#ifndef TNET_PACKETSTREAM_H
#define TNET_PACKETSTREAM_H

#include <tnet/common/Common.h>
#include <tnet/network/Packet.h>

TNET_BEGIN_NAMESPACE(network);

class PacketStream
{
public:
    PacketStream();
    ~PacketStream();
private:
    PacketStream(const PacketStream &);
    PacketStream& operator=(const PacketStream &);
public:
    virtual Packet* createPacket() = 0;
    virtual bool encode() = 0;
    virtual bool decode() = 0;
private:
};

TNET_TYPEDEF_PTR(PacketStream);

TNET_END_NAMESPACE(network);

#endif //TNET_PACKETSTREAM_H
