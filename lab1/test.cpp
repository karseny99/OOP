#include <gtest/gtest.h>
#include "box_cap.h"

TEST(test_01, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(32, 64, 16) == 13824);
}

TEST(test_02, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(32768, 1, 1) == 0);
}

TEST(test_03, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(6, 10, 11) == 224);
}

TEST(test_04, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(0, 0, 0) == 0);
}

TEST(test_05, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(2, 2, 2) == 1);
}

TEST(test_06, basic_test_set) 
{
    ASSERT_TRUE(box_capacity(2100, 2100, 2100) == 3906984375);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}