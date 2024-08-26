#pragma once
class CGameStreamingMgr {
public:
	CGameStreamingMgr(void);
	void Initialize();
	bool CheckForDLC(unsigned long long DLCHASH);
	
	bool isMPMapActive();
private:
	bool isMP_MAP_ACTIVE;
};