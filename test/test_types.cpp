#include <gtest/gtest.h>

#include "../types.h"

#include <iostream>

bool test_eq(const EthCpp::Quantity& lhs, uint64_t rhs)
{
    if (lhs.value != rhs)
    {
        std::cerr << "Q != " << std::to_string(rhs) << ", it is equal to " << std::to_string(lhs.value) << "\n";
        return false;
    }
    return true;
}

TEST(test_types, Quantity)
{
    EthCpp::Quantity q("0x0");
    EXPECT_EQ(q.value, 0);
    q = EthCpp::Quantity("0x1");
    EXPECT_EQ(q.value, 1);
    q = EthCpp::Quantity("0xff");
    EXPECT_EQ(q.value, 255);
    q = EthCpp::Quantity("0x4b7");
    EXPECT_EQ(q.value, 1207);
}
