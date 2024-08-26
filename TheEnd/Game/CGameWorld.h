#pragma once
#include	"../SHVNative/types.h"
#include	<bitset>
#include	<vector>
class CDoor; // Door
class CDoorSystem; //Custom Replacement of the door system already present
class CVehicleFactory; // All spawned vehicles go through here
class CGameMissionMgr; // All custom missions go through this.
class CGameScriptMgr; // learn about scripts
class CGameWaterState; // for cayo water etc.
class CGameWorldLightMgr; // Blackout state
class CGameWorldWeatherMgr; // Weather
class CGameWorldTimeMgr; // Time
class CGameWorldTimeCycleMgr; // Screen effects.
class CGameTimeCycle; // timecycle for activation effects etc.
class CGameInteriorMgr; // interiors specifically the ones for buildings. outside interiors like map expansions are handled elsewhere.
class CGameExplosionMgr; // explosion mgr. uhh idk what this is for and it'll probably be deleted.
class CPlayer; // For the player because why not lol also this should extend CGameEntity;
class CGameStreamingMgr;
typedef std::vector<const char*> IPLsLoaded; // this is useless just a nice convience. 
/* As I am winding down tonight lets have a little chat. 
* right so the purpose of this class is so that I can get my custom objects to work nicely with the game's natives.
* So the more advanced part of this is that the events will get triggered.
* However as this is out of scope of this specific project this codefile will probably be dorment until 1.0 when i work on rewriting stuff.
* CDoorSystem will be a stand in replacement of Rockstar's door system for simplicity of I want more control over the doors. 
* CVehicleFactory will be drop in replacement for Rockstars Vehicle methods one again for same control just my control
* CGameMissionMgr will be all custom missions TheEnd included will run through it. Every mission will push a function to the call stack that simply does stuff once.
* CGameScriptMgr will hook into all scripts and get their runtime environments. and will have the ability to terminate any script that is uncooperative.
* CGameWaterState will just be our written version of the WATER based natives.
* CGameWorldLightMgr will be for the blackout sequence which you can probably write this in like 8 minutes lol.
* CGameWorldWeatherMgr will simply check the weather and report back to the script as to what the weather is doing. also if its frozen. Will be updateable
* CGameWorldTimeMgr will be for all time related objects. So interping in time etc.
* CGameWorldTimeCycleMgr will include all running instances of timecycle modifiers.
* CGameTimeCycle is just the object that will go into the Manager;
* CGameInteriorMgr is the way that we will be processing interiors. Interiors can be loaded through a destinct hash key that is bounded to the Interior's data. All interiors will have some sort of requirements or bit controls related to disabling weapons while inside etc.
* CGameExplosionMgr likely will get trashed considering that we don't really need a manager for these objects as they exist for one frame and the particles stay for a bit but thats it.
* CPlayer - This will take a while however its going to contain all active ways to get Player, getting the players position locally which likely means calling the ENTITY::GET_ENTITY_COORDS() every frame lul or at least when they request for it.
* //**SPECULATION AS TO WHAT WILL HAPPEN AFTER v1.0**\\
* CGameStateManager will probably be for anything unrelated to this or might be an entire superclass that contains all objects aformentioned about weather, time, timecycles, interiors, etc.
* CGameWorld or CGameEnvironment might be different.
* CGameHudManager will also probably exist and that will contain the CMinimap, CPauseMenuStatus (REGULAR), And any text objects that are rendered.
* CGameTextManager - this will be part of a global rewrite of all the previous hud code. as I simply don't want to deal with it anymore lul. 
* CGameText - Goes into the Manager. Manager will be the sole one responsible for allowing the game text to Draw.
* CGameBox - Goes into the CGameBoxMgr
* CGameBoxMgr - is a class that allows control over all HudObjects that include boxes. // KEEP IN MIND RIGHT THESE ARE SO WE CAN ACTUALLY DO SOME COOL STUFF WITH THE HUD IN THE GAME.
* CFileWriter - probably for save files.
* CFileFinder - Once again save files probably
* CNetPlayer - maybe if we learn netcode lol
* CNetPlayerMgr - maybe if we get bored enough to actually write multiplayer.
* CGang - If we as well do the rewrite these will likely be added. 
* CGangMgr - CGang's are likely going to be not like actual "gangs" but more of like a group of npcs that are HOSTILE, NEUTRAL, or FRIENDLY toward the player.
* CGameWorldStateManager - Likely will have stuff todo with global effects. More grandular effects like the water with cayo map etc. Building off of the other systems.
* CInteractionMenu - Yes I've not forgotten about you glorious king. Interaction Menu will be written but as you can see i've got a lot of shit on my plate at the moment.
* CInteractionMenuMgr - More like memory arenas for registering interaction menus.
* CEvents, CGameControlEvent, CGameNetEvent<TYPE>, CGameEventDispatcher, CGameEventHandler, CGameNativeCallEvent<NATIVE_HASH> // all of these will likely be written. in the final stages
* CGameEntity - Will be a super object of all peds created.
* CGameCamera - Once again more control over game the better.
* CGameFollowCam - References the follow cam in all instances. 
* CGameSRLLoader - SRL or SRI is just more cinematic stuff
* CGameSwitch - Handles the game's switch code and logic
* CGameSwitchManager - Makes sure we don't have a switch active once we are in DLL_UNLOAD so we can escape!
* CGamePed - Subclass of CGameEntity;
* CGameVehicle - Subclass of CGameEntity
* CScriptMemTracker - Final Stages of memory debug stuff.
* CGameStreaming - Streaming related stuff. 
* CGameStreamingManager - The streamer's reporter. what is loaded, deloaded, map files, etc. NOT A CULLER TRASHCAN!
* CScriptUUID - Once again this is more for the stuff that I want to happen however it would be pretty nice in an environment like this. However I just don't know how to do it?
* CTheScript - This is just our main injection points, Update loops etc. All threads go through here. Likely have a constexpr array of all possible functions that need to be executed when the program starts. 
*/
class CGameWorld {

public:
	enum eGameWorldAdditionState {
		eGWBS_WORLD_LOAD_CAYO,
		eGWBS_WORLD_LOAD_NORTH,
		eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH,
		eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH, // this is as the recent patch goes added an IPL for this.
		eGWBS_WORLD_DISABLE_LOS_SANTOS,
		eGWBS_WORLD_LOADED_CAYO,
		eGWBS_WORLD_LOADED_NORTH,
		eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_SOUTH,
		eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_NORTH, // this is as the recent patch goes added an IPL for this.
		eGWBS_WORLD_DISABLED_LOS_SANTOS,
		eGWBS_MAX
	};
	int FindEntityInWorld(CVector3<float>& location);
	std::bitset<eGWBS_MAX>* GetGameInteriorInformation();
	
	void Update(); // defer this to a third thread. same with all systems that go under this.
	void Init();
	void Destroy();
	~CGameWorld();
	CGameInteriorMgr* GetInteriorManager();
	static CPlayer* GetLocalPlayer();
	static CVehicleFactory* GetVehicleFactory();
	void WORLD_LOAD_CAYO();
	void OnEnterSp();
	void OnEnterMp();
	bool IsMpMapActive();
private:
	void GameWorldStateCheck();
	void WORLD_LOAD_S_CARRIER();
	void WORLD_LOAD_N_CARRIER();
	void WORLD_DISABLE_LOS_SANTOS();
	void WORLD_LOAD_NY();
	void ConfigureWorldState();
	bool DoClassSanityCheck();
	
	bool m_bMpMapActive;
	CGameMissionMgr*	m_pMissionMgr; // All missions that are active and the state.
	CGameScriptMgr*		m_pScriptMgr; //  All scripts go thru this. 
	static CGameWorld*	m_pWorldInstance; // the global world instance.
	CDoorSystem*		m_pWorldDoorSystem; // all doors.
	CVehicleFactory*	m_pVehicleFactory; // For all vehicles.
	IPLsLoaded			m_vIPLsLoaded; // All IPLS that are not interiors go thru this.
	CGameInteriorMgr*	m_pInteriorManager;
	CGameExplosionMgr*	m_pExplostionManager;
	CPlayer*			m_pPlayer;
	CGameStreamingMgr*		m_pStreamingManager;
	std::bitset<eGWBS_MAX>	m_GameStateInformation;
};