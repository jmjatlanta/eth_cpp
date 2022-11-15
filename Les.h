#pragma once
#include "IPCConnector.h"

#include <string>
#include <memory>

namespace EthCpp {

class Les
{
    public:
    bool init(std::shared_ptr<IPCConnector> conn);

    std::string serverInfo();
    std::string clientInfo();
    std::string priorityClientInfo();
    std::string addBalance();
    std::string setClientParams();
    std::string setDefaultParams();
    std::string latestCheckpoint();
    std::string GetCheckpoint();
    std::string GetCheckpointContractAddress();

    protected:
    std::shared_ptr<IPCConnector> conn;
};

} // namespace EthCpp

