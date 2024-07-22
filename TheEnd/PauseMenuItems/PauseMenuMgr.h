#pragma once
#include "Generic/PauseMenu.h"
#include <map>
class CPauseMenuMgr { // no singleton so we force implementors to go through PauseInterface.
private:
	std::map<int, CPauseMenu*> m_Menus;
public:
	void RegisterPauseMenu(CPauseMenu* menu);
	CPauseMenu* GetMenu(int id);

};