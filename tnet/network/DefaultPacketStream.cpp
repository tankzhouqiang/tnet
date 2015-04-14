#include <tnet/network/DefaultPacketStream.h>

using namespace std;
TNET_BEGIN_NAMESPACE(network);

DefaultPacketStream::DefaultPacketStream() { 
}

DefaultPacketStream::~DefaultPacketStream() { 
}

bool DefaultPacketStream::encode(Packet *packet, 
                                 util::DataBuffer *dataBuffer) 
{
    assert(packet);
    assert(dataBuffer);
    DefaultPacket *defaultPacket = dynamic_cast<DefaultPacket*> (packet);
    assert(defaultPacket);
    uint32_t bodyLen = defaultPacket->getBodyLen();
    dataBuffer->writeUInt32(bodyLen);
    dataBuffer->writeUInt32(defaultPacket->getSessionId());
    dataBuffer->writeUInt32(defaultPacket->getSessionId());
    memcpy(dataBuffer->getFree(), defaultPacket->getBody(), bodyLen);
    return true;
}

bool DefaultPacketStream::decode(util::DataBuffer *dataBuffer, 
            Packet *packet)
{
    assert(dataBuffer);
    DefaultPacket *defaultPacket = new DefaultPacket();
    uint32_t bodyLen = dataBuffer->readUInt32();
    cout << "33333333333333333" << bodyLen << endl;
    defaultPacket->setBodyLen(bodyLen);
    uint32_t sessionId = dataBuffer->readUInt32();
    cout << "33333333333333333" << sessionId << endl;
    defaultPacket->setSessionId(sessionId);
    uint32_t packetType = dataBuffer->readUInt32();
    defaultPacket->setPacketType(packetType);
    void *packetBody = malloc(bodyLen);
    dataBuffer->readBytes(packetBody, bodyLen);
    defaultPacket->setBody(packetBody);
    packet = defaultPacket;
    return true;
}

TNET_END_NAMESPACE(network);

