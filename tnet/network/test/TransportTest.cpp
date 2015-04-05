#include "../Transport.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(network);

class TransportTest : public ::testing::Test {
protected:
    TransportTest() {
    }
    virtual ~TransportTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(TransportTest, parseAddress) {
    Transport transport;
    string spec = "10.192.168.6:12345";
    string ip;
    int port;
    ASSERT_TRUE(transport.parseAddress(spec, ip, port));
    ASSERT_EQ(string("10.192.168.6"), ip);
    ASSERT_EQ(int(12345), port);

    spec = "10.192.168.6";
    ASSERT_FALSE(transport.parseAddress(spec, ip, port));
}

TNET_END_NAMESPACE(network);

