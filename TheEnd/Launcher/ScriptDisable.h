#pragma once
#include "../Scripts/CDisable.h"
#include "../SHVNative/types.h"
class CTheEndScriptDisabler {
public:
	using ScrName = const char*;
	CTheEndScriptDisabler();
	void SetDisablerActive(bool _new);
	bool CanDisablerRun();
	CDisableScripts* GetScriptDisabler();	
	int GetLastUpdateTime() { return this->m_iStaggeredLoopTimer; }
	void Init();
	void Update();
private:
	CDisableScripts m_pScriptDisabler;
	int m_iStaggeredLoopTimer;
	bool m_bCanStaggeredLoopRun;
};
typedef Singleton<CTheEndScriptDisabler> sEndScriptDisabler;
#define SCRIPT_MGR sEndScriptDisabler::GetInstance()