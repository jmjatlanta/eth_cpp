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

int main(int argc, char** argv)
{
    EthCpp::Quantity q("0x0");
    test_eq(q, 0);
    q = EthCpp::Quantity("0x1");
    test_eq(q, 1);
    q = EthCpp::Quantity("0xff");
    test_eq(q, 255);
    q = EthCpp::Quantity("0x4b7");
    test_eq(q, 1207);
}
