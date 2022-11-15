#include <gtest/gtest.h>

#include "../EthCpp.h"
#include "../Eth.h"

TEST(test_block, connector)
{
    EthCpp::EthCpp connector("/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc");

    EthCpp::Quantity qty = connector.eth.blockNumber();
    EXPECT_EQ(qty.value, 0);	
}
