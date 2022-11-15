#pragma once

#include "types.h"
#include <memory>

class IPCConnector;

namespace EthCpp {

class Web3 
{
    public:
    Web3() {};

    bool init(std::shared_ptr<IPCConnector> conn);

    std::string clientVersion();

    protected:
    std::shared_ptr<IPCConnector> conn = nullptr;
};

} // namespace EthCpp

