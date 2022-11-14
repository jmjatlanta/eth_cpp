#include <string>

class IPCConnector
{
	public:
	IPCConnector();
	~IPCConnector();

	bool Open(const std::string& filename);
    
    /***
     * @brief read one entry from incoming socket
     * @param out what was read
     * @return true on success
     */
    bool Read(std::string& out);
    bool Write(const std::string& in);

	protected:
	int sock_fd = -1;
};


