#pragma once
#include "LocalLogger.h"
#include "LoggerClient.h"
class CLogger {
private:
	LocalLogger locLogger;
	CClientNetwork networkLogger;
	static CLogger* m_Logger;
public:
	CLogger();
	CClientNetwork* GetNetworkLogger();
	LocalLogger* GetLocalLogger();
	static CLogger* GetInst();
};