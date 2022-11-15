#include <gtest/gtest.h>

#include "../EthCpp.h"
#include "../Eth.h"
#include "../Web3.h"

TEST(test_web3, clientVersion)
{
    EthCpp::EthCpp connector("/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc");

    std::string result = connector.web3.clientVersion();
    EXPECT_TRUE(!result.empty());
}
