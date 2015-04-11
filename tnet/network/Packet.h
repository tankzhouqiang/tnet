#ifndef TNET_PACKET_H
#define TNET_PACKET_H

#include <tnet/common/Common.h>

TNET_BEGIN_NAMESPACE(network);

class PacketHeader {
public:
    PacketHeader（）
    : _sessionId(0) ,_type(-1)  ,_dataLen（-1）
    {
    }
public:
    uint32_t _sessionId;
    int _type;
    int _dataLen;
};

class Packet
{
public:
    Packet();
    ~Packet();
private:
    Packet(const Packet &);
    Packet& operator=(const Packet &);
public:
    void setSessionId(uint64_t sessionId) {
        _header._sessionId = sessionId;
    }
    uint64_t getSessionId() const {
        return _header._sessionId;
    }
    void setPacketType(uint32_t packetType) {
        _header._type = packetType;
    }
    uint32_t getPacketType() const {
        return _header._type;
    }
    
private:
    PacketHeader _header;
};

TNET_TYPEDEF_PTR(Packet);

TNET_END_NAMESPACE(network);

#endif //TNET_PACKET_H
