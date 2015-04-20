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
    cout << "encode bodylen" << bodyLen << endl;
    dataBuffer->writeUInt32(bodyLen);
    dataBuffer->writeUInt32(defaultPacket->getSessionId());
    dataBuffer->writeUInt32(defaultPacket->getPacketType());
    dataBuffer->writeBytes(defaultPacket->getBody(), bodyLen);
    return true;
}

Packet* DefaultPacketStream::decode(util::DataBuffer *dataBuffer) {
    assert(dataBuffer);
    cout << "bodyLen decode"  << endl;
    DefaultPacket *defaultPacket = new DefaultPacket();
    uint32_t bodyLen = dataBuffer->readUInt32();
    defaultPacket->setBodyLen(bodyLen);
    uint32_t sessionId = dataBuffer->readUInt32();
    defaultPacket->setSessionId(sessionId);
    uint32_t packetType = dataBuffer->readUInt32();
    defaultPacket->setPacketType(packetType);
    void *packetBody = malloc(bodyLen);
    cout << "bodyLen5555555" << bodyLen << endl;
    if (!dataBuffer->readBytes(packetBody, bodyLen)) {
        LOG(ERROR) << "read packet body error." << endl;
        return NULL;
    }
    cout << "bodyLen666666666666" << bodyLen << endl;
    defaultPacket->setBody(packetBody);
    defaultPacket->setIsOwnBody(true);
    return defaultPacket;
}

TNET_END_NAMESPACE(network);

