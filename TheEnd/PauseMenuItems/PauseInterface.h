#pragma once
#include "./PauseMenuMgr.h"
class MenuInterface {
public:
	static CPauseMenuMgr* GetPauseMgr();
	~MenuInterface() {
		delete MenuInterface::GetPauseMgr();
	}
private:
	static CPauseMenuMgr* MenuMgr;
};