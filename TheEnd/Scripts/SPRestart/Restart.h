#pragma once
class CDisableScripts;
class CGameWorld;
class CTheEndRestartSP { // Specifically for the stuff out of scope of CDisable. 
private:
	CDisableScripts* m_pScriptDisabler;
	CGameWorld* m_pGameWorld;
public:
	CTheEndRestartSP(CDisableScripts* disabler, CGameWorld* gameworld);
	void RestartFreemode_SP();
	void StopFreemode_SP();

};