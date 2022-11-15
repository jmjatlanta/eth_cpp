#include "types.h"
#include <sstream>
#include <vector>

namespace EthCpp {

uint64_t to_uint64(const std::vector<unsigned char>& in)
{
    uint64_t retVal = 0;
    switch(in.size())
    {
        case(0):
            break;
        case(2):
            retVal = (in[0] << 8) | in[1];
            break;
        case (4):
            retVal = (in[0] << 8) | in[1] | in[2] | in[3];
            break;
        case(6):
            retVal = (in[0] << 8) | in[1] | in[2] | in[3] | in[4] | in[5];
            break;
    }
    return retVal;
}

Quantity::Quantity(const std::string& in)
{
    if (in.find("0x") != 0)
        throw 1;
    value = 0;
    std::string val = in;
    if (val.size() % 2 != 0)
        val = "0x0" + val.substr(2);
    value = std::strtoull(val.c_str(), nullptr, 16);
}

Quantity::Quantity(uint64_t in)
{
    value = in;
}

}
