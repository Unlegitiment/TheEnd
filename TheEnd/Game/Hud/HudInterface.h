#pragma once
#include "../../SHVNative/types.h"
class CMinimap;
class CGameHelpText;
class CGameSpinner;
class HudInterface {
private:
	CMinimap* m_pMinimap;
	CGameHelpText* m_pHelpText;
	CGameSpinner* m_pSpinner;
public:
	HudInterface();
	CGameHelpText* GetHelpText();
	CMinimap* GetMiniMap();
	CGameSpinner* GetSpinner();
};
typedef Singleton<HudInterface> sHudInterface;
#define GAMEHUD sHudInterface::GetInstance()