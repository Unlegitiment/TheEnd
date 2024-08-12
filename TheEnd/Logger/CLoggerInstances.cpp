#include "CLoggerInstances.h"
CLogger* CLogger::m_Logger = new CLogger();
CLogger::CLogger():
    locLogger(LocalLogger()),
    networkLogger(CClientNetwork())
{
}

CClientNetwork* CLogger::GetNetworkLogger() {
    return &this->networkLogger;
}

LocalLogger* CLogger::GetLocalLogger() {
    return &this->locLogger;
}

CLogger* CLogger::GetInst() {
    return CLogger::m_Logger;
}
