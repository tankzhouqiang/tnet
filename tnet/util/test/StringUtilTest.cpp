#include "../StringUtil.h"
#include "gtest/gtest.h"

using namespace std;
using namespace::testing;

TNET_BEGIN_NAMESPACE(util);

class StringUtilTest : public ::testing::Test {
protected:
    StringUtilTest() {
    }
    virtual ~StringUtilTest() {
    }
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(StringUtilTest, split) {
    vector<string> result1 = StringUtil::split("abc\t\tefg\thgi", "\t");
    ASSERT_EQ((size_t)3, result1.size());
    ASSERT_EQ(string("abc"), result1[0]);
    ASSERT_EQ(string("efg"), result1[1]);
    ASSERT_EQ(string("hgi"), result1[2]);

    vector<string> result2 = StringUtil::split("abc\t\tefg\thgi", "\t", false);
    ASSERT_EQ((size_t)4, result2.size());
    ASSERT_EQ(string("abc"), result2[0]);
    ASSERT_EQ(string(""), result2[1]);
    ASSERT_EQ(string("efg"), result2[2]);
    ASSERT_EQ(string("hgi"), result2[3]);

    vector<string> result3 = StringUtil::split("abc\tefg\thgi\t\t", "\t", true);
    ASSERT_EQ((size_t)3, result3.size());
    ASSERT_EQ(string("abc"), result3[0]);
    ASSERT_EQ(string("efg"), result3[1]);
    ASSERT_EQ(string("hgi"), result3[2]);

    vector<string> result4 = StringUtil::split("abc\tefg\thgi\t\t", "\t", false);
    ASSERT_EQ((size_t)5, result4.size());
    ASSERT_EQ(string("abc"), result4[0]);
    ASSERT_EQ(string("efg"), result4[1]);
    ASSERT_EQ(string("hgi"), result4[2]);
    ASSERT_EQ(string(""), result4[3]);
    ASSERT_EQ(string(""), result4[4]);
}

TNET_END_NAMESPACE(util);

