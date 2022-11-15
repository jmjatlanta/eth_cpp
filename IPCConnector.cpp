#include "IPCConnector.h"
#include "rapidjson/document.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

IPCConnector::IPCConnector()
{
    next_id = 1;
    read_thread = std::make_shared<std::thread>(&IPCConnector::Read, this);
}

IPCConnector::~IPCConnector()
{
    read_thread_shutdown = true;
    if (read_thread != nullptr)
        read_thread->join();
	if (sock_fd >= 0)
		close(sock_fd);
}

bool IPCConnector::Open(const std::string& filename)
{
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0); // 0 = socket picks protocol
	if (sock_fd < 0)
	{
		std::cerr << "sock_fd < 0\n";
		return false;
	}
	sockaddr_un remote;
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, filename.c_str());
	if (connect(sock_fd, (sockaddr*)&remote, filename.size() + sizeof(remote.sun_family)) < 0)
	{
		std::cerr << "Unable to connect\n";
		return false;
	}
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	return true;
}

size_t get_id(const std::string& json)
{
    rapidjson::Document d;
    d.Parse(json.c_str());
    if (d.HasMember("id") && d["id"].IsUint64())
    {
        return d["id"].GetUint64();
    }
    return 0;
}

void IPCConnector::Read()
{
    while(!read_thread_shutdown)
    {
        unsigned char buff[65535];
        memset(&buff[0], 0, 65535);
        size_t bytes = read(sock_fd, buff, 65535);
        if (bytes > 65535)
            bytes = 0;
        if (bytes > 0)
        {
            std::string out = std::string((char*)buff);
            auto id = get_id(out);
            if (id > 0)
            {
                try {
                    auto& promise = promise_map.at(id);
                    promise.set_value(out);
                } catch(...)
                {
                    std::cout << "Did not find promise for id " << std::to_string(id) << "\n";
                }
            }
        }
    }
    return;
}

bool IPCConnector::Write(const std::string& in)
{
    return send(sock_fd, in.c_str(), in.size(), 0) == in.size();
}

bool IPCConnector::Write(const std::string& methodName, const std::vector<std::string>& params)
{
    std::string json = "{\"jsonrpc\":\"2.0\",\"method\":\"" + methodName + "\",\"params\":[],\"id\":"
            + std::to_string(next_id++) + "}";
    return Write(json);
}

std::future<std::string> IPCConnector::AsyncWrite(const std::string& methodName, const std::vector<std::string>& params)
{
         size_t id = next_id++;
         auto& promise = promise_map[id];
         std::stringstream ss;
         ss << "{\"jsonrpc\":\"2.0\",\"method\":\"" + methodName + "\",\"params\":[";
         bool is_first = true; 
         for(auto& p : params)
             ss << (is_first?"":",") << "\"" << p << "\"";
         ss << "],\"id\":" << std::to_string(id) << "}";
         auto success = Write(ss.str());
         return promise.get_future();
}
