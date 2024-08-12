#include "LocalLogger.h"
#include <chrono>
#include <iomanip>
#include <sstream>
static constexpr const char* LOGGER_NAME = "TheEndLocalLogger.txt";
LocalLogger::LocalLogger() : 
	file(LOGGER_NAME, std::ios::out) // this will depend on where file opens
{
}
using Clock = std::chrono::high_resolution_clock;
static std::string timePointToString(const Clock::time_point& tp, const std::string& format, bool withMs = true, bool utc = true) {
    const Clock::time_point::duration tt = tp.time_since_epoch();
    const time_t durS = std::chrono::duration_cast<std::chrono::seconds>(tt).count();
    std::ostringstream ss;
    if (const std::tm* tm = (utc ? std::gmtime(&durS) : std::localtime(&durS))) {
        ss << std::put_time(tm, format.c_str());
        if (withMs) {
            const long long durMs = std::chrono::duration_cast<std::chrono::milliseconds>(tt).count();
            ss << std::setw(3) << std::setfill('0') << int(durMs - durS * 1000);
        }
    }
    // gmtime/localtime() returned null ?
    else {
        ss << "<FORMAT ERROR>";
    }
    return ss.str();
}
void LocalLogger::Log(eLoggerState logState, std::string loggerMessage, bool formatTime = true) {
	std::string curTime = "";
	if (formatTime) {
        curTime.append(timePointToString(Clock::now(), "[%H:%M:%S]",false,true));
	}
    if (!this->file.is_open()) {
        this->file.open(LOGGER_NAME);
    }
    if (this->file.is_open()) {
        auto logMsg = GetLogMessage(logState, loggerMessage, formatTime);
        this->file.write(logMsg.c_str(), logMsg.size());
        this->file.flush();
    }
}

void LocalLogger::InfoLog(std::string& message) {
}

std::string LocalLogger::GetLogLevelToStr(eLoggerState loggerState) {
    switch (loggerState) {
        case WARN:
            return "[WARN]"; // format yellow
        case FATAL:
            return "[FATAL]"; // format for dark red
        case INFO:
            return "[INFO]"; // format dark blue
        case ERROR2:
            return "[ERROR]"; // format for red characters
        default:
            return "[INFO]";
    }
}

std::string LocalLogger::GetLogMessage(eLoggerState logState, std::string loggerMessage, bool formatTime) {
    std::string finalizedLoggerMessage = timePointToString(Clock::now(), "[%H:%M:%S]", false, true) + " " + GetLogLevelToStr(logState) + " " + loggerMessage;
    return finalizedLoggerMessage;
}
