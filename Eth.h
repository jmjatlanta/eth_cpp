#pragma once

#include "types.h"
#include <memory>

class IPCConnector;

namespace EthCpp {

class Eth
{
    public:
    Eth() {};

    bool init(std::shared_ptr<IPCConnector> conn);

    Quantity blockNumber();

    protected:
    std::shared_ptr<IPCConnector> conn = nullptr;
};

} // namespace EthCpp

