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
static std::string timePointToString() {
    // Get current time point
    auto now = std::chrono::system_clock::now();

    // Get the time as time_t for basic hour, min, sec
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Break it into hours, minutes, and seconds
    std::tm* now_tm = std::localtime(&now_time_t);

    // Extract milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // Create stringstream to format time
    std::ostringstream oss;
    oss << '['
        << std::setw(2) << std::setfill('0') << now_tm->tm_hour << ':'
        << std::setw(2) << std::setfill('0') << now_tm->tm_min << ':'
        << std::setw(2) << std::setfill('0') << now_tm->tm_sec << ':'
        << std::setw(3) << std::setfill('0') << milliseconds.count() // Milliseconds
        << ']';

    return oss.str();
}
void LocalLogger::Log(eLoggerState logState, std::string loggerMessage, bool formatTime = true) {
	std::string curTime = "";
	if (formatTime) {
        curTime.append(timePointToString());
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
    case eLoggerState::WARN:
            return "[WARN]"; // format yellow
    case eLoggerState::FATAL:
            return "[FATAL]"; // format for dark red
    case eLoggerState::INFO:
            return "[INFO]"; // format dark blue
    case eLoggerState::ERROR2:
            return "[ERROR]"; // format for red characters
        default:
            return "[INFO]";
    }
}

std::string LocalLogger::GetLogMessage(eLoggerState logState, std::string loggerMessage, bool formatTime) {
    
    std::string finalizedLoggerMessage = timePointToString() + " " + GetLogLevelToStr(logState) + " " + loggerMessage;
    return finalizedLoggerMessage;
}
