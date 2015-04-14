#ifndef TNET_DEFAULTPACKETSTREAM_H
#define TNET_DEFAULTPACKETSTREAM_H

#include <tnet/common/Common.h>
#include <tnet/network/DefaultPacket.h>
#include <tnet/util/DataBuffer.h>

TNET_BEGIN_NAMESPACE(network);

class DefaultPacketStream
{
public:
    DefaultPacketStream();
    ~DefaultPacketStream();
private:
    DefaultPacketStream(const DefaultPacketStream &);
    DefaultPacketStream& operator=(const DefaultPacketStream &);
public:
    /*override*/ virtual bool encode(Packet *packet, 
            util::DataBuffer *dataBuffer);
    /*override*/ virtual bool decode(util::DataBuffer *dataBuffer, 
            Packet *packet);

private:
};

TNET_TYPEDEF_PTR(DefaultPacketStream);

TNET_END_NAMESPACE(network);

#endif //TNET_DEFAULTPACKETSTREAM_H
