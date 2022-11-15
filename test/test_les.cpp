#include <gtest/gtest.h>

#include "../EthCpp.h"
#include "../Eth.h"

TEST(test_les, info)
{
    EthCpp::EthCpp connector("/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc");

    std::string result = connector.les.serverInfo();
    EXPECT_TRUE(!result.empty());
    std::cout << "info test result: " << result << "\n";
}
