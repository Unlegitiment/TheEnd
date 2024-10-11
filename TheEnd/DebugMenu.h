#pragma once
#include "./MenuAPI/PlayerMenu.h"
#include "./SHVNative/types.h"
class CDebugMenu : public CPlayerMenu {
private:
	DWORD KEYCOMBO = VK_F14;
	bool m_bIsDBGMenuDisp = false;
public:
	CDebugMenu();
	void Update();
};
typedef Singleton<CDebugMenu> sDebug;
#define DBG sDebug::GetInstance()