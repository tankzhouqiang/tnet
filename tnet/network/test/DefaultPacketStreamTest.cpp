#include "../DefaultPacketStream.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(network);

class DefaultPacketStreamTest : public ::testing::Test {
protected:
    DefaultPacketStreamTest() {
    }
    virtual ~DefaultPacketStreamTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(DefaultPacketStreamTest, simpleProcess) {
    DefaultPacket *packet = new DefaultPacket();
    packet->setSessionId(1);
    packet->setPacketType(2);
    char buf[10] = "123456789";
    packet->setBodyLen(9);
    packet->setBody(buf);
    DefaultPacketStream defaultPacketStream;
    util::DataBuffer dataBuffer;
    ASSERT_TRUE(defaultPacketStream.encode(packet, &dataBuffer));
    delete packet;
    DefaultPacket *decodePacket;
    ASSERT_TRUE(defaultPacketStream.decode(&dataBuffer, decodePacket));
    DefaultPacket *defaultPacket = dynamic_cast<DefaultPacket*> (decodePacket);
    assert(defaultPacket);
    cout << defaultPacket->getSessionId() << endl;
    ASSERT_EQ((uint32_t)1, defaultPacket->getSessionId());
    ASSERT_EQ((int32_t)2, defaultPacket->getPacketType());
    ASSERT_EQ((int32_t)10, defaultPacket->getBodyLen());
    char *decodeBuf = (char*) defaultPacket->getBody();
    for (uint32_t i = 0; i < 9; ++i) {
        ASSERT_EQ(buf[i], *(decodeBuf + i));
    }
    free(decodeBuf);
    delete defaultPacket;
}

TNET_END_NAMESPACE(network);

