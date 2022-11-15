#include "Les.h"

namespace EthCpp {

bool Les::init(std::shared_ptr<IPCConnector> conn)
{
    this->conn = conn;
    return conn != nullptr;
}

std::string Les::serverInfo()
{
    std::vector<std::string> params;
    auto future = conn->AsyncWrite("les_serverInfo", params);
    return future.get();
}

std::string Les::clientInfo()
{
    std::vector<std::string> params;
    auto future = conn->AsyncWrite("les_clientInfo", params);
    return future.get();
}

std::string Les::priorityClientInfo()
{
    std::vector<std::string> params;
    auto future = conn->AsyncWrite("les_priorityClientInfo", params);
    return future.get();
}

std::string Les::addBalance()
{
    //TODO
    return "";
}
std::string Les::setClientParams()
{
    //TODO
    return "";
}
std::string Les::setDefaultParams()
{
    //TODO
    return "";
}
std::string Les::latestCheckpoint()
{
    //TODO
    return "";
}
std::string Les::GetCheckpoint()
{
    //TODO
    return "";
}
std::string Les::GetCheckpointContractAddress()
{
    //TODO
    return "";
}

} // namespace EthCpp
