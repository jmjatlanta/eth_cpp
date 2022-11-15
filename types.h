#pragma once

#include <string>
#include <cstdint>

namespace EthCpp {

class Quantity
{
    public:
    Quantity(const std::string& text);
    Quantity(const uint64_t num);

    /****
     * Turn the object into its hex representation
     * @returns string representing the value in hex
     */
    std::string Encode();

    uint64_t value = 0;
};

} // namespace EthCpp

