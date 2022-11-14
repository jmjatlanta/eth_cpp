#include "IPCConnector.h"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

IPCConnector::IPCConnector(){}

IPCConnector::~IPCConnector()
{
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
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	return true;
}

bool IPCConnector::Read(std::string& out)
{
    unsigned char buff[65535];
    memset(&buff[0], 0, 65535);
    size_t bytes = read(sock_fd, buff, 65535);
	if (bytes > 65535)
		bytes = 0;
    if (bytes > 0)
        out = std::string((char*)buff);
    return bytes > 0;
}

bool IPCConnector::Write(const std::string& in)
{
    return send(sock_fd, in.c_str(), in.size(), 0) == in.size();
}
