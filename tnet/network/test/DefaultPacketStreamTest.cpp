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
    DefaultPacket decodePacket;
    ASSERT_TRUE(defaultPacketStream.decode(&dataBuffer, &decodePacket));
    ASSERT_EQ((uint32_t)1, decodePacket.getSessionId());
    ASSERT_EQ((int32_t)2, decodePacket.getPacketType());
    ASSERT_EQ((int32_t)9, decodePacket.getBodyLen());
    char *decodeBuf = (char*) decodePacket.getBody();
    for (uint32_t i = 0; i < 9; ++i) {
        ASSERT_EQ(buf[i], *(decodeBuf + i));
    }
    free(decodeBuf);
}

TNET_END_NAMESPACE(network);

