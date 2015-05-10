#ifndef TNET_TIMEOUTPACKET_H
#define TNET_TIMEOUTPACKET_H

#include <tnet/common/Common.h>
#include <tnet/network/Packet.h>

TNET_BEGIN_NAMESPACE(network);

class TimeoutPacket : public Packet
{
public:
    TimeoutPacket();
    ~TimeoutPacket();
private:
    TimeoutPacket(const TimeoutPacket &);
    TimeoutPacket& operator=(const TimeoutPacket &);
public:
    
private:
};

TNET_TYPEDEF_PTR(TimeoutPacket);

TNET_END_NAMESPACE(network);

#endif //TNET_TIMEOUTPACKET_H
