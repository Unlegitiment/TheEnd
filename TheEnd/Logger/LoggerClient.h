#pragma once
#include "LocalLogger.h"
class CClientNetwork {
private:
	LocalLogger locLogger; // for debug purposes
	int sockFd = 0; // ideally we'd just abstract away these network details to a CNetworkClient (cause they aren't actually good here.)? Well we do? But I guess I just wrote the logger over this?
	int iResult = 0;
	struct addrinfo* result = NULL,
		* ptr = NULL;
public:
	static void LogPrintf(const char* fmt, ...);
	CClientNetwork() : locLogger(LocalLogger()){}
	void StartWSA();
	void StartConnectionProcess();
	void ConnectionProcess();
	void Cleanup();
	void SendData(const std::string& buff); // we get all data from this;
	~CClientNetwork();
};
