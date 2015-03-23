#include <glog/logging.h>
#include <gtest/gtest.h>
using namespace std;
using namespace ::testing;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "BEGIN RUN CASE IN CONFIG TEST";

    return RUN_ALL_TESTS();
}

