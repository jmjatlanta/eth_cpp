#include <string>
#include <vector>
#include <atomic>
#include <future>
#include <map>

class IPCConnector
{
	public:
	IPCConnector();
	~IPCConnector();

	bool Open(const std::string& filename);
    bool Write(const std::string& methodName, const std::vector<std::string>& params);
    std::future<std::string> AsyncWrite(const std::string& methodName, const std::vector<std::string>& params);

	protected:
    void Read(); // called in read_thread
    bool Write(const std::string& in); // write the JSON to the socket
                 
	int sock_fd = -1;  // socket ID
    std::atomic<size_t> next_id; // request/response id 
    std::map<size_t, std::promise<std::string> > promise_map; // collection of promises
    std::shared_ptr<std::thread> read_thread; // reads from socket
    bool read_thread_shutdown = false; // true if shutting down
};


