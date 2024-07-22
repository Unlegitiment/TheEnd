#pragma once
class CMarkerInfo {
public:
	CMarkerInfo(const char* name, const char* type, const char* pInfo, const char* percent, const char* dbgval, bool isRockstarVerf, const char* preq, const char* rp, const char* cash, const char* times); // player info and time must be left empty if cash and rp is to be filled in
	const char* getMissionName();
	const char* getMissionType();
	const char* getPlayerInfo();
	const char* getPercentage();
	const char* getDebugVal();
	bool getifRockstarVerified();
	const char* getPlayerReq();
	const char* getRP();
	const char* getCash();
	const char* getTime();
private:
	const char* missionName;
	const char* missionType;
	const char* playerInfo;
	const char* percentage;
	const char* debugVal;
	bool isRockstarVerified;
	const char* playerReq;
	const char* RP;
	const char* cashmul;
	const char* time;
};