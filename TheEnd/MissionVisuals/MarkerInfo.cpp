#include "MarkerInfo.h"

CMarkerInfo::CMarkerInfo(const char* name, const char* type, const char* pInfo, const char* percent, const char* dbgval, bool isRockstarVerf, const char* preq, const char* rp, const char* cash, const char* times)
    :
    missionName(name),
    missionType(type),
    playerInfo(pInfo),
    percentage(percent),
    debugVal(dbgval),
    isRockstarVerified(isRockstarVerf),
    playerReq(preq),
    RP(rp),
    cashmul(cash),
    time(times)
{

}

const char* CMarkerInfo::getMissionName() {
    return missionName;
}

const char* CMarkerInfo::getMissionType() {
    return missionType;
}

const char* CMarkerInfo::getPlayerInfo() {
    return playerInfo;
}

const char* CMarkerInfo::getPercentage() {
    return percentage;
}

const char* CMarkerInfo::getDebugVal() {
    return debugVal;
}

bool CMarkerInfo::getifRockstarVerified() {
    return isRockstarVerified;
}

const char* CMarkerInfo::getPlayerReq() {
    return playerReq;
}

const char* CMarkerInfo::getRP() {
    return RP;
}

const char* CMarkerInfo::getCash() {
    return cashmul;
}

const char* CMarkerInfo::getTime() {
    return time;
}

