#pragma once
#include "./SHVNative/natives.h"
#include "./Ambience/CConfigureTheEndAmbience.h"
#include "./Game/Building/CBoundingBox.h"
#include "./Game/Anim/SyncronizedScene.h"
class CTheScript {
public:
	void OneTime();
	void Update();
private:
	void SetupEnvironment();
	void BoxCheck();
	void Cheat_CLEARSCRFX();
	void Cheat_GOTODELUXO();
	void ClearTraffic();
	void BlipSetup();
	void UFOSetup();
	void SetupWarp();
	void StartWarp();
	enum class CHECKPOINT {
		DREAM_SEQUENCE,
		WAKE_UP_NOW,
		INSIDE_INTERIOR,
		INSIDE_MIL_BASE,
		DRIVING_TO_LSIA,
		LEAVING_TO_CAYO,
		LEAVING_TO_NORTH_YANKTON
	};
	enum class MISSION_FAIL_CONDITION {
		NO_FAIL,
		GOD_MODE,
		VEHICLE_GODMODE_DETECTED,
		SWARMED_BASE,
		DEATH,
		INSTANT_TRANSMISSION, // teleport in real world
	};
private: // Objects
	Vehicle DELUXO = -1;
	bool isPlayerInDeluxo = false;
	Object OBJ_UFO = 0;
private://AMBIENCE
	CConfigureTheEndAmbience ambienceConfig = CConfigureTheEndAmbience();
	bool m_bIsAmbienceConfigured = false;
	bool m_bConfigureAmbience = false;
	bool m_bSetVehicleDensityNow = false;
	float m_fStartTime = 0.f;
private: // Defined Box Coordinates/State Control
	CBoundingBox box = CBoundingBox({ 51.2319, -872.6470, 60.71 }, { 47,1,100 }, { 1,0.5,0,0 });
private: //MISSION BLIP
	Blip Blip_MainObj;
	Blip Blip_SecondaryObj;
private: //STATE
	bool m_bRenderUFOEffect = false;
	int CurrentLevel = -1; // -1 is freeroam because enums start at 0;
	int CurStateOfPlayer = -1; // -1 means idle/freeroam etcc
	bool isAwoken = (CurrentLevel >= (int)CHECKPOINT::WAKE_UP_NOW);
	int FAIL_CONDITION = 0; // fail condition
private: // GLOBAL_DATA
	float m_fZGroundZCoord_UFO = 0.0f;
	CVector3<float> m_fRespawnLocation = { 0,0,0 }; // Todo -- write respawn layer for this to lay on top of.
	bool m_bDisplayHelpText = true; 
	CSynchronizedScene Scene = CSynchronizedScene();
private: //WARP RELATED ACTIONS
	enum eWarpSet {
		WARP_HAS_STARTED,
		WARP_TRANSITIONING,
		WARP_ENDING,
		EWS_SIZE
	};
	std::bitset<EWS_SIZE> m_bsWarp;
	Ped WarpPed;
};
typedef Singleton<CTheScript> sScript;
#define THEENDSCRIPT sScript::GetInstance()