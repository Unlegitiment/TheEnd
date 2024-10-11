#pragma once
#include "LocalLogger.h"
#include "LoggerClient.h"
#define RBlack		"\033[30m"  // Black Text
#define RRed		"\033[31m"  // Red Text
#define RGreen		"\033[32m"  // Green Text
#define RYellow		"\033[33m"  // Yellow Text
#define RBlue		"\033[34m"  // Blue Text
#define RPurple		"\033[35m"  // Purple Text
#define RCyan		"\033[36m"  // Cyan Text

#define RIRed		"\033[41m"  // Inversed Red Text
#define RIGreen		"\033[42m\033[30m"  // Inversed Green Text
#define RIYellow	"\033[43m\033[30m"  // Inversed Yellow Text
#define RIBlue		"\033[44m"  // Inversed Blue Text
#define RIPurple	"\033[45m"  // Inversed Purple Text
#define RICyan		"\033[46m"  // Inversed Cyan Text

#define RHIBlack		"\033[90m"			//Black
#define RHIRed			"\033[91m"			//Red
#define RHIGreen		"\033[92m"			//Green
#define RHIYellow		"\033[93m"			//Yellow
#define RHIBlue			"\033[94m"			//Blue
#define RHIPurple		"\033[95m"			//Purple
#define RHICyan			"\033[96m"			//Cyan
#define RHIWhite		"\033[97m"			//White

#define RNorm		"\033[0m"		// Normal Text
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
#define scriptLog(...) netLogger->LogInfo(INFO, true, __FUNCTION__,": " ,__VA_ARGS__)