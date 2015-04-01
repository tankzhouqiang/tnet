#include "../Thread.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(util);

class ThreadTest : public ::testing::Test {
protected:
    ThreadTest() {
    }
    virtual ~ThreadTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

void testFunc(int x, int *y) {
    *y = x * x;
}

TEST_F(ThreadTest, simpleProcess) {
    for (int i = 0; i < 10; ++i) {
        int y = 0;
        ThreadPtr threadPtr = Thread::createThread(tr1::bind(&testFunc, 10, &y));
        ASSERT_TRUE(threadPtr);
        ASSERT_TRUE(threadPtr->getId());
        threadPtr->join();
        ASSERT_TRUE(!threadPtr->getId());
        ASSERT_EQ(100, y);
    }
}

TNET_END_NAMESPACE(util);

