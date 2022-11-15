#include "Web3.h"
#include "Util.h"
#include "IPCConnector.h"
#include <future>

namespace EthCpp {

bool Web3::init(std::shared_ptr<IPCConnector> conn)
{
    this->conn = conn;
    return conn != nullptr;
}

std::string Web3::clientVersion()
{
    std::vector<std::string> params;
    std::future<std::string> response = conn->AsyncWrite("web3_clientVersion", params);
    return string_result(response.get());
}

} // namespace EthCpp
