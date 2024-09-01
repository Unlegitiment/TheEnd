#pragma once
#include "../Launcher/CTheEndLoadMenu.h"
#include "./CFadeScreen.h"
class CTheEndHud {
private:
	CTheEndLoadMenu mMenu = CTheEndLoadMenu();
	CFade m_Fade = CFade();
	bool DoesDisplayMenu = false;
public:
	CTheEndLoadMenu* GetLoadingMenu();
	CFade* GetFade();
	bool IsLoadingMenuActive();
	void SetLoadingMenuActive(bool _new);
	void OneTick();
	void Update();
};
typedef Singleton<CTheEndHud> sEndHud;
#define EHUD sEndHud::GetInstance()