#include "../TcpConnection.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(network);

class TcpConnectionTest : public ::testing::Test {
protected:
    TcpConnectionTest() {
    }
    virtual ~TcpConnectionTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(TcpConnectionTest,  checkTimeout) {
    Packet packet1;
    Packet packet2;
    Packet packet3;
    TcpConnection connection;
    packet1.setTimeout(1000 * 1000);
    packet1.setSessionId(0);
    packet2.setTimeout(2 * 1000 * 1000);
    packet2.setSessionId(1);
    packet3.setTimeout(3 * 1000 * 1000);
    packet3.setSessionId(2);
    list<Packet*>& packetList = connection.getPacketList();
    packetList.push_back(&packet1);
    packetList.push_back(&packet2);
    packetList.push_back(&packet3);
    connection.checkTimeout();
    ASSERT_EQ((size_t)3, packetList.size());
    sleep(1);
    connection.checkTimeout();
    ASSERT_EQ((size_t)2, packetList.size());
    list<Packet*>::iterator it = packetList.begin();
    ASSERT_EQ((uint64_t)1, (*it)->getSessionId());
    it++;
    ASSERT_EQ((uint64_t)2, (*it)->getSessionId());
    sleep(1);
    connection.checkTimeout();
    ASSERT_EQ((size_t)1, packetList.size());
    it = packetList.begin();
    ASSERT_EQ((uint64_t)2, (*it)->getSessionId());
    sleep(1);
    connection.checkTimeout();
    ASSERT_EQ((size_t)0, packetList.size());
}

TNET_END_NAMESPACE(network);

