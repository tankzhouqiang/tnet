#ifndef TNET_PACKET_H
#define TNET_PACKET_H

#include <tnet/common/Common.h>
#include <tnet/util/TimeUtility.h>

TNET_BEGIN_NAMESPACE(network);

class PacketHeader {
public:
    static const int PACKET_HEADER_LEN = 12;
public:
    PacketHeader()
        : _bodyLen(0)
        , _sessionId(0) 
        ,_type(0)
    {
    }
    PacketHeader(char *buf)
    {
        _bodyLen = *(uint32_t*)buf;
        _sessionId = *(uint32_t*)(buf + 4);
        _type = *(uint32_t*)(buf + 8);
    }
public:
    uint32_t _bodyLen;
    uint32_t _sessionId;
    uint32_t _type;
};

class Packet
{
public:
    Packet();
    virtual ~Packet();
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
    
    void setBodyLen(int bodyLen) {
        _header._bodyLen = bodyLen;
    }
    int getBodyLen() const {
        return _header._bodyLen;
    }
    void setSendTime(int64_t sendTime) {
        _sendTime = sendTime;
    }
    int64_t getSendTime() const {
        return _sendTime;
    }

private:
    PacketHeader _header;
    int64_t _sendTime;
};

TNET_TYPEDEF_PTR(Packet);

TNET_END_NAMESPACE(network);

#endif //TNET_PACKET_H
