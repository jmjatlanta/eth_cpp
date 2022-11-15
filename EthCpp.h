#pragma once

#include "Eth.h"
#include "Web3.h"
#include "Les.h"

#include <string>
#include <memory>

class IPCConnector;

namespace EthCpp
{

class EthCpp
{
    public:
    EthCpp(const std::string& filename);

    Eth eth;
    Web3 web3;
    Les les;

    protected:
    std::shared_ptr<IPCConnector> ipc = nullptr;

};

} // namespace EthCpp

