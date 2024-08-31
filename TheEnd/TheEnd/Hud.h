#pragma once
#include "../Launcher/CTheEndLoadMenu.h"
class CTheEndHud {
private:
	CTheEndLoadMenu mMenu = CTheEndLoadMenu();
	bool DoesDisplayMenu = false;
public:
	CTheEndLoadMenu* GetLoadingMenu();
	bool IsLoadingMenuActive();
	void SetLoadingMenuActive(bool _new);
	void OneTick();
	void Update();
};
typedef Singleton<CTheEndHud> sEndHud;
#define EHUD sEndHud::GetInstance()