#include "../EthCpp.h"
#include "../Eth.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    EthCpp::EthCpp connector("/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc");

    EthCpp::Quantity qty = connector.eth.blockNumber();
    std::cout << "Quantity: " << qty.value << "\n";
}
