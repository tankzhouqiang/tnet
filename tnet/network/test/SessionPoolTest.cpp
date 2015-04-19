#include "../SessionPool.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(network);

class SessionPoolTest : public ::testing::Test {
protected:
    SessionPoolTest() {
    }
    virtual ~SessionPoolTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

class SimpleIPacketHandler : public IPacketHandler
{
public:
    virtual void handlePacket(Packet *packet, void *args) {
        return;
    }
};

TEST_F(SessionPoolTest, simple) {
    SessionPool pool;
    SimpleIPacketHandler handler;
    int32_t args = 1;
    ASSERT_EQ(uint32_t(0), pool.allocateSession(&handler, 
                    (void*)&args));
    SimpleIPacketHandler handler2;
    int32_t args2 = 2;
    ASSERT_EQ(uint32_t(1), pool.allocateSession(&handler2, 
                    (void*)&args2));
    
    Session *session2 = pool.getSession(1);
    ASSERT_TRUE(session2 != NULL);
    ASSERT_EQ(session2->_handler, &handler2);
    ASSERT_EQ((int32_t)2, *(int32_t*)(session2->_args));
    Session *session1 = pool.getSession(0);
    ASSERT_TRUE(session1 != NULL);
    ASSERT_EQ(session1->_handler, (IPacketHandler*)&handler);
    ASSERT_EQ((int32_t)1, *(int32_t*)(session1->_args));
    delete session1;
    delete session2;
    Session *session3 = pool.getSession(1);
    ASSERT_TRUE(session3 == NULL);
    Session *session4 = pool.getSession(3);
    ASSERT_TRUE(session4 == NULL);
}

TNET_END_NAMESPACE(network);

