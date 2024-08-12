#pragma once
#include "LocalLogger.h"
class CClientNetwork {
private:
	LocalLogger locLogger; // for debug purposes
	int sockFd = 0;
	int iResult = 0;
	struct addrinfo* result = NULL,
		* ptr = NULL;
public:
	CClientNetwork() :locLogger(LocalLogger()){}
	void StartWSA();
	void StartConnectionProcess();
	void ConnectionProcess();
	void Cleanup();
	template<typename ...Args>
	void LogInfo(eLoggerState logImportance, bool withTime, Args... a);
	void SendData(std::string& buff); // we get all data from this;
	~CClientNetwork();
};
#include <sstream>
template<typename ...Args>
inline void CClientNetwork::LogInfo(eLoggerState logImportance, bool withTime, Args ...a) {
	std::stringstream ss;
	(ss << ... << a);
	std::string mes = locLogger.GetLogMessage(logImportance, ss.str(), withTime) + '\n';
	iResult = send(sockFd, mes.c_str(), mes.size(), 0);
	if (iResult == SOCKET_ERROR) {
		locLogger.Log(ERROR2, "send failed!", true);
		closesocket(sockFd);
		return;
	}

}
