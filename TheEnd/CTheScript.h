#pragma once
#include "./SHVNative/natives.h"
#include "./Ambience/CConfigureTheEndAmbience.h"
#include "./Game/Building/CBoundingBox.h"
#include "./Game/Anim/SyncronizedScene.h"
#include "CaptureSys/include.h"
#include "./Game/Music/MusicInterface.h"
#include "./AI//EnemyAI.h"
#include "./MenuAPI/PlayerMenu.h"
class CTheScript {
private:
	enum TEST_VAL {
		DOES_NEED_WARP,
		WARP_CAYO,
		TEST_VAL_MAX
	};
	bool m_bIsPlayerMenuShowing = false;
	std::bitset<TEST_VAL_MAX> m_BitWarpSet; // For a Later script.
public:
	void OneTime();
	void Update();
private:
	void MenuNav();
	void TimeCopy(float fLaunch, int targetHours, int targetMinutes, int targetSeconds); // FROM CConfigureTheEndAmbience;
	void SendTextMessage();
	std::string GetZoneWherePlayerIs();
	void WarpStateManagement();
	void SetupEnvironment();
	void BoxCheck();
	void CheatHelper();
	void Cheat_CLEARSCRFX();
	void Cheat_GOTODELUXO();
	void Cheat_ChangeScore();
	void Cheat_ResetGlobals();
	void UT_2();
	void UT_3();
	void ClearTraffic();
	void BlipSetup();
	void UFOSetup();
	void SetupWarp();
	void StartWarp();
	void LockFirstPerson();
	bool isPlayerInElevator();
private: // used for like one second of the mission. when the player gets outside. I don't want to bully them too hard.
	int iFrameCountdown = 50;
	int iFrameStart = 0;
	bool AreIFramesActive = false;
private: // Mission Later component based stuff.
	bool isPadDisabled = false;
	bool m_bHasTextMessageBeenSent = false;
private:
	enum class CHECKPOINT {
		DREAM_SEQUENCE,
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
private: // Music
	
	enum eMusicMood {
		ACTION,
		AIRBORNE,
		SILENT,
		SUSPENSE,
		VEHICLE_CHASE
	};
	CMusicTrack m_CurrentScore = CMusicTrack("MP_MC_CMH_IAA_FINALE_START", {
		"MP_MC_CMH_ADV_ACTION",
		"MP_MC_CMH_ADV_AIRBORNE",
		"MP_MC_CMH_ADV_SILENT",
		"MP_MC_CMH_ADV_SUSPENSE",
		"MP_MC_CMH_ADV_VEHICLE_CHASE"
		});
	bool m_bIsMusicActive = false;
	bool m_bCanMusicPlay = true;
private: // Player Interactable
	CPlayerMenu m_PlayerMenu = CPlayerMenu();
	bool m_bDoesPlayerMenuNeedSetup = true;
	int m_iPlayerSelection = 0;
	bool m_bHasSwitchBeenInit = false;
private: // Enemy AI Move to Seperate Class
	CMilitaryAI AI = CMilitaryAI();
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
	Blip Blip_MainObj; // CBlip::AddBlipForCoord(); || CBlipMgr::AddBlipForCoord(CVector3); // this would add it to an vector of all blips.
	Blip Blip_SecondaryObj;
private: //STATE
	bool isPlayerAwake = false;
	bool m_bRenderUFOEffect = false;
	int CurrentLevel = -1; // -1 is freeroam because enums start at 0;
	int CurStateOfPlayer = -1; // -1 means idle/freeroam etcc
	int FAIL_CONDITION = 0; // fail condition
	bool m_bLockFirstPerson; // GameInterface::GetGlobals()->AddGlobal<bool, MyFPLock>();// what type is it? and what Function is it calling.
	CWeaponCapture m_WeaponCapture = *WEAP_CAP; // CaptureInterface::GetWeaponCapture()->Capture();  CaptureInterface::GetStatCapture()->Capture(); 
private: // GLOBAL_DATA
	bool m_bDoesNeedToGetWeapon = false; // move to class
	bool m_bDoesHaveWeapon = false;
	float m_fZGroundZCoord_UFO = 57.5193f; // this val was acquired via MISC::GET_GROUND_Z_AT_COORD however due to collision this value gets invalidated sometimes thus the static value was created,.
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