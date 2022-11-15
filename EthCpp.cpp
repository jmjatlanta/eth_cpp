#include "EthCpp.h"
#include "IPCConnector.h"
#include "Eth.h"

namespace EthCpp {

EthCpp::EthCpp(const std::string& filename)
{
    ipc = std::make_shared<IPCConnector>();
    if(!ipc->Open(filename))
        throw 1; //TODO
    eth.init(ipc);
    web3.init(ipc);
    les.init(ipc);
}

} // namespace EthCpp

