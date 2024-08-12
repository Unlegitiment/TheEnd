#pragma once
#include <fstream>
//Purpose is to provide a local logger incase we don't launch the network logger properly and this will only use the network's logger since the setup for the network logger might take longer than expected or could take way longer than we want it to.
enum eLoggerState {
	FATAL,
	ERROR2,
	WARN,
	INFO
};
class LocalLogger {
private:
	std::ofstream file;

public:
	LocalLogger();
	void Log(eLoggerState logState, std::string loggerMessage, bool formatTime);
	void InfoLog(std::string& message);
	std::string GetLogLevelToStr(eLoggerState loggerState);
	std::string GetLogMessage(eLoggerState logState, std::string loggerMessage, bool formatTime);
	
};