#pragma once
#include <vector>
#include <string>
class CDisableScripts {
private:
	using ScrName = const char*;
	struct ScrInfo {
		bool isDisabled;
		ScrName name;
	};
	std::vector<ScrInfo> m_AllScriptsToDisable;
	bool m_ForceRefresh;
public:
    enum StackSize {
        MICRO = 128,
        MINI = 512,
        DEFAULT = 1424,
        SPECIAL_ABILITY = 1828,
        FRIEND = 2050,
        SHOP = 2324,
        CELLPHONE = 2552,
        VEHICLE_SPAWN = 3568,
        CAR_MOD_SHOP = 3750,
        PAUSE_MENU_SCRIPT = 3076,
        APP_INTERNET = 4592,
        MULTIPLAYER_MISSION = 5050,
        CONTACTS_APP = 4000,
        INTERACTION_MENU = 9800,
        SCRIPT_XML = 8344,
        PROPERTY_INT = 19400,
        ACTIVITY_CREATOR_INT = 15900,
        SMPL_INTERIOR = 2512,
        WAREHOUSE = 14100,
        IE_DELIVERY = 2324,
        SHOP_CONTROLLER = 3800,
        AM_MP_YACHT = 5000,
        INGAMEHUD = 4600,
        TRANSITION = 8032,
        FMMC_LAUNCHER = 27000,
        MULTIPLAYER_FREEMODE = 85000,
        MISSION = 62500,
        MP_LAUNCH_SCRIPT = 34750
    };
	void PushBackScript(ScrName name);
	void Update();
    void RestartAllScripts();
    void StaggeredLoop(int* updateTimer);
	void ClearAllScripts();
	void Destroy();
	static bool RestartScript(ScrName name, StackSize stackSize); // this is in development a nullsub rn
	std::string GetLogStatement();
};