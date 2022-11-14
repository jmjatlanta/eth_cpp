#include "../IPCConnector.h"
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

void parse_results(const std::string& in)
{
    if (!in.empty())
    {
        rapidjson::Document doc;
        doc.Parse(in.c_str());
        if (!doc.IsObject())
        {
            std::cerr << "Invalid JSON document\n";
            return;
        }
        if (doc.HasMember("result"))
        {
            if (!doc["result"].IsString())
            {
                std::cerr << "Result is not a string.\n";
                return;
            }
            subscription = doc["result"].GetString();
            std::cout << "Subscription: " << subscription << "\n";
        }
        else
            std::cout << "Result: " << in << "\n";
    }
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

	std::string ipc_filename = "full/path/to/geth.ipc";

	// attempt to connect to the IPC file
	IPCConnector ipc;
	ipc.Open(ipc_filename);
	ipc.Write( "{\"id\": 1, \"method\": \"eth_subscribe\", \"params\": [\"newHeads\"]}" );

	for(int i = 0; i < 1000; ++i)
	{
		if (ctrl_c_pressed)
			break;
		std::string result;
		if (ipc.Read(result))
		{
            parse_results(result);
		}
	}
	// unsubscribe
    if (!subscription.empty())
    {
        std::string msg = "{\"id\": 1, \"method\": \"eth_unsubscribe\", \"params\": [\"" + subscription + "\"]}";
        ipc.Write(msg);
        std::string result;
        for(int i = 0; i < 10; i++)
        {
            if (ipc.Read(result))
            {
                std::cout << "Result of unsubscribe: " << result << "\n";
                break;
            }
        }
    }
	std::cout << "Done.\n";
	return 1;
}

