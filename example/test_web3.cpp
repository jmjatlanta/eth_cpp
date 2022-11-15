#include "../EthCpp.h"
#include "../Eth.h"
#include "../Web3.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    EthCpp::EthCpp connector("/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc");

    std::string result = connector.web3.clientVersion();
    std::cout << "Result: " << result << "\n";
}
