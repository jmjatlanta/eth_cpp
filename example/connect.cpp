#include "../IPCConnector.h"
#include "../Util.h"
#include "rapidjson/document.h"

#include <signal.h>
#include <string>
#include <iostream>

static bool ctrl_c_pressed = false;
static std::string subscription;

void ctrl_c_handler(int s)
{
	ctrl_c_pressed = true;
}

/***
 * A quick example to demonstrate how to connect to the geth.ipc file in C++
 */
int main(int argc, char** argv)
{
	// handle CTRL-C
	struct sigaction sigIntHandler;
   	sigIntHandler.sa_handler = ctrl_c_handler;
   	sigemptyset(&sigIntHandler.sa_mask);
   	sigIntHandler.sa_flags = 0;
   	sigaction(SIGINT, &sigIntHandler, NULL);

	std::string ipc_filename = "/media/jmjatlanta/LinuxUSB/eth_mainnet/geth.ipc";

    if (argc > 1)
        ipc_filename = argv[1];

    std::cout << "IPC Filename: " << ipc_filename << "\n";

	// attempt to connect to the IPC file
	IPCConnector ipc;
	ipc.Open(ipc_filename);
    std::vector<std::string> params;
    params.push_back("newHeads");
    auto future = ipc.AsyncWrite("eth_subscribe", params);

    std::string result = future.get();
    subscription = EthCpp::string_result(result);
    
    // Did we get the subscription successfully?
    if (subscription.empty())
    {
        std::cout << "We did not get the subscription!\n";
    }
    else
    {
        params.clear();
        params.push_back(subscription);
        future = ipc.AsyncWrite("eth_unsubscribe", params);
        result = future.get();
        std::cout << "Result of unsubscribe: " << (EthCpp::bool_result(result)?"true":"false") << "\n";
    }
	std::cout << "Done.\n";
	return 1;
}

