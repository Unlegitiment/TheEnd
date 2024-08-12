#pragma once
#include <vector>
#include "../SHVNative/natives.h"
#include "../SHVNative/types.h"
#include "../MarkerLauncher/VisualMarker.h"
#include "./CMission.h"
#include <vector>
#pragma region UNDEFINED_SYMBOLS 
class CPauseMenu;
class CTimerBars;
class CTimerBarMgr;
class CInteractionMenu;
class CPlayerList;
class CScoreboard;
class CScoreboardMgr;
class CWarnScreen;
class CPhone;
#pragma endregion

class CTheEnd final : CMission {
	static const int NAME_BUFFER_MAX_ALLOC = 32;
	static const int CREW_BUFFER_MAX_ALLOC = 12;
	struct PlayerData {
		int m_iPedHandle;
		CVector3 m_v3PedLoc;
		float m_fPedHeading;
		const char m_NameBuffer[NAME_BUFFER_MAX_ALLOC];
		int m_iRank;
		const char m_pRsgFormattedCrewtag[CREW_BUFFER_MAX_ALLOC];
	};
public:
	CTheEnd() = default;
	void Update();
	void PrepEntities();
	enum ePauseGlitchState {
		SHOW_AND_HIDE,
		FORCE_INTO,
		PAUSE_GAME, // diff because it actually pauses it
		SHOW_HEADER,
		SHOW_PAGE,
		SHOW_PAGINATOR
	};
	enum eMissionStates {
		UFO_TAKE_UP,
		PLAYER_HAS_WOKEN,
		PLAYER_HAS_ESCAPED_BUILDING,
		PLAYER_HAS_ESCAPED_MIL_BASE,
		PLAYER_IS_DRIVING_AWAY,
		PLAYER_IS_INSIDE_APT,
		PLAYER_IS_NEAR_LSIA,
		PLAYER_IS_LEAVING_CITY,
		PLAYER_IS_IN_NORTH_YANKTON,
		PLAYER_IS_IN_CAYO_PERICO
	}; // Player will have option as to where to go Cayo or North Yankton.
	typedef int MilliSeconds;
	void SetTimeStarted(MilliSeconds ms); // MISC::GET_GAME_TIMER();
	void LoadPreMissionMenu();
	void PreMissionState();
	void PreMissionMenu(); // CPauseMenu copy; goes into PreMissionState
	void SetupSwitch(Ped from, Ped* to, CVector3 teleportLocation); // to can be null which we take a diff path
	static void FORCE_SWITCH_OFF(); // just calls STREAMING::STOP_PLAYER_SWITCH and tries to abort switch.
	int GetMissionState();
	bool GetLocalMissionActive();
	void HandlePauseGlitchState(CPauseMenu* m_Menu, ePauseGlitchState glitchType); 
	// we could make a few easter eggs like if you try to go into a GTA:O house there will be NPC's inside that freak out.
	enum ePhoneNav {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	ePhoneNav GetPhoneDirectionFromControls(); // Call in while.
	void UpdatePhonePosition(CPhone* pPhone, ePhoneNav direction);
	void HandleUp(CPhone* pPhone);
	void HandleDown(CPhone* pPhone);
	void HandleLeft(CPhone* pPhone);
	void HandleRight(CPhone* pPhone);
	~CTheEnd(); // Call Cleanup
private:
#pragma region GLOBAL_VARS
	//Globals Mission Status
	bool m_bhasEscapedMilBase;
	bool m_bhasEscapedCity;
	bool m_bis_mission_active_local;
	bool m_bisPauseActive;
	bool m_bisPauseGlitching;
	int  m_iPauseMenuGlitchState; // For the functionality purposessss
	int  m_iLevelState;
	int  m_iSwitchState;
	bool m_bisSwitchActive;
	//PauseMenu Bug
	CPauseMenu* m_pMenuToBug;
	CPauseMenu* m_pMenuDisplay; // Menu that the player spawn in after loading mission;
	//Globals
	int  m_iCutsceneProgression;
	int  m_iSyncedSceneProgress;
	bool m_bisSyncedSceneInProgress;
	CVector3 m_v3RespawnPoint = {0,0,0}; // interior location;
	bool m_bhasPlayerDiedBefore;
	int  m_iDeathsAlloted;
	int  m_iCurrentDeaths;
	int  m_iKills;
	//Local Player Data and other Hud Elements ( simulation of GTA Online System
	PlayerData m_pLocalPlayerData; // fillout this data;
	CTimerBars* m_pTimerbar;
	CTimerBarMgr* m_pTimerbarMgr; // comes from MenuInterface::GetTimerBarMgr(); might rename to HudInterface
	CInteractionMenu* m_pInteraction; // comes from MenuInterface::GetInteractionMenu();
	//Controls
	std::vector<int> m_vControlsToDisable_NORMAL; // control index: 0;
	std::vector<int> m_vControlsToDisable_FRONT; // front end controls 2;
	// Globals TimeCycle, Entity Spawning
	bool m_bisTCActive; // time cycle for the better looking assets
	bool m_bHaveAllObjectsSpawned;
	//Simulating GTA:Online Systems;
	CPlayerList* m_pPlayerListInstance; // get from MenuInterface::GetPlayerList();
	bool m_bShouldDisplayPlayerList;
	//Globals Time, Minimap
	bool m_bIsPlayerInsideInterior; //this is for explicitly the interior the player wakes in.
	int m_itimeWhenMissionStarted; //MISC::GET_GAME_TIMER(); in setup phase;
	int m_iTimeAllotedMS; // MISC::GET_GAME_TIMER() + 25000 ms; 25 mins
	int m_iCurTimeLeftMS;
	int m_iCurrentStarsLocked; //recursively sets the wanted level if -1 than it will act like this value doesn't exist and let the wanted stars disappear
	bool m_bShouldDisplayMap;
	//Scoreboard Death Options
	CScoreboard& m_pDeathScoreboard; // if the player dies while on the mission we want to display this.
	CScoreboardMgr& m_pScoreboardMgr; // MenuInterface::GetScoreboardMgr();
	bool m_bShouldDisplayScoreboard;
	//Warning Screen Options
	CWarnScreen& m_pWarnScreen;
	bool m_bShouldShowWarnScreen;
	int m_iBugState_WRN; //Warning screen predefined bug break; flickering, text changes, etc.
	//Phone Options
	CPhone* m_pPhone; // Because we want only want one phone we need this. HudInterface::GetPhone();
	int m_iPhoneSelection;
	bool m_bDoesPlayerHaveAccessToPhone;
	bool m_bIsPhoneRendering;
#pragma endregion 
};