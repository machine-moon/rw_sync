#include <gtest/gtest.h>

// Example function to be tested
int add(int a, int b)
{
    return a + b;
}

// Test case
TEST(AdditionTest, HandlesPositiveInput)
{
    EXPECT_EQ(add(1, 2), 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}