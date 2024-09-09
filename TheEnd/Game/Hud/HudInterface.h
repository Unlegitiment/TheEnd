#pragma once
#include "../../SHVNative/types.h"
class CMinimap;
class CGameHelpText;
class CGameSpinner;
class CGameWeaponWheel;
class HudInterface {
private:
	CMinimap* m_pMinimap;
	CGameHelpText* m_pHelpText;
	CGameSpinner* m_pSpinner;
	CGameWeaponWheel* m_pWeaponWheel;
public:
	HudInterface();
	CGameHelpText* GetHelpText();
	CMinimap* GetMiniMap();
	CGameSpinner* GetSpinner();
	CGameWeaponWheel* GetWeaponWheel();
};
typedef Singleton<HudInterface> sHudInterface;
#define GAMEHUD sHudInterface::GetInstance()