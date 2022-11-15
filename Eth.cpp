#include "Eth.h"
#include "Util.h" // string_result
#include "IPCConnector.h"
#include "rapidjson/document.h"

namespace EthCpp {

bool Eth::init(std::shared_ptr<IPCConnector> conn)
{
    this->conn = conn;
    return conn != nullptr;
}

Quantity Eth::blockNumber()
{
    std::vector<std::string> params;
    auto future = conn->AsyncWrite("eth_blockNumber", params);
    std::string response = future.get();
    return Quantity(string_result(response));
}

} // namespace EthCpp
