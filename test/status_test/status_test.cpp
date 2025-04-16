
#include <cstddef>
#include <gtest/gtest.h>

#include "mdn/status.h"

using namespace std;
using namespace testing;

class mdnStatusTest : public ::testing::Test {};

class mdnStatusTestDeathTest : public mdnStatusTest {};

#ifdef MDN_STATUS_SAFE_MODE
TEST_F(mdnStatusTest, InvalidArguments) {
    ASSERT_EQ(mdn_Status_getStr(MDN_STATUS_ENUM_COUNT), nullptr);
}
#endif  // MDN_STATUS_SAFE_MODE

TEST_F(mdnStatusTest, GetStr) {
    ASSERT_STREQ(mdn_Status_getStr(MDN_STATUS_ERROR_MEM_ALLOC), "Memory allocation failed");
}

TEST_F(mdnStatusTest, NoMissingStringsInTable) {
    for (size_t idx = MDN_STATUS_SUCCESS; idx < MDN_STATUS_ENUM_COUNT; ++idx) {
        ASSERT_NE(mdn_Status_getStr(static_cast<mdn_Status_t>(idx)), nullptr);
    }
}

TEST_F(mdnStatusTest, AssertSuccess) {
    mdn_Status_assert(MDN_STATUS_SUCCESS);
}

TEST_F(mdnStatusTestDeathTest, AssertFailure) {
    ASSERT_EXIT(mdn_Status_assert(MDN_STATUS_ERROR_BAD_ARGUMENT),
                ExitedWithCode(MDN_STATUS_ERROR_BAD_ARGUMENT),
                "Function called with a bad argument");
}

TEST_F(mdnStatusTestDeathTest, AssertUnknown) {
    ASSERT_EXIT(mdn_Status_assert(MDN_STATUS_ENUM_COUNT), ExitedWithCode(MDN_STATUS_ENUM_COUNT), "unknown status");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
