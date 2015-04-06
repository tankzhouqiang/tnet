#include "../Lock.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(util);

class LockTest : public ::testing::Test {
protected:
    LockTest() {
    }
    virtual ~LockTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(LockTest, ThreadMutex) {
    ThreadMutex lock;
    ASSERT_EQ(0, lock.lock());
    ASSERT_EQ(EBUSY, lock.trylock());
    ASSERT_EQ(0, lock.unlock());
    ASSERT_EQ(0, lock.trylock());
    ASSERT_EQ(0, lock.unlock());
}

TNET_END_NAMESPACE(util);

