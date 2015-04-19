#ifndef TNET_DEFAULTPACKET_H
#define TNET_DEFAULTPACKET_H

#include <tnet/common/Common.h>
#include <tnet/network/Packet.h>

TNET_BEGIN_NAMESPACE(network);


class DefaultPacket : public Packet
{
public:
    DefaultPacket();
    ~DefaultPacket();
private:
    DefaultPacket(const DefaultPacket &);
    DefaultPacket& operator=(const DefaultPacket &);
public:
    void setBody(void *body) {
        _body = body;
    }
    void* getBody() const {
        return _body;
    }
    void setIsOwnBody(bool isOwnBody = false) {
        _isOwnBody = isOwnBody;
    }
private:
    bool _isOwnBody;
    void *_body;
};

TNET_TYPEDEF_PTR(DefaultPacket);

TNET_END_NAMESPACE(network);

#endif //TNET_DEFAULTPACKET_H
