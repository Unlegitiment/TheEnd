#include "CGameWorld.h"
#include "../GlobalUpdateThread.h"
#include "./Interior/InteriorManager.h"
int CGameWorld::FindEntityInWorld(CVector3<float>& location) {
    return 0;
}

std::bitset<CGameWorld::eGWBS_MAX>* CGameWorld::GetGameInteriorInformation() {
    return &this->m_GameStateInformation;
}

void CGameWorld::Update() {
    this->GameWorldStateCheck();
}

void CGameWorld::Init() {
    this->m_pInteriorManager = new CGameInteriorMgr();
    
}

void CGameWorld::Destroy() {
    delete this->m_pInteriorManager; // we clean up heap here.
}

CGameWorld::~CGameWorld() {
    scriptLogI("called!");
    this->m_pInteriorManager->Destroy();
}

CGameInteriorMgr* CGameWorld::GetInteriorManager() {
    return this->m_pInteriorManager;
}

CPlayer* CGameWorld::GetLocalPlayer() {
    return sGameWorld::GetInstance()->m_pPlayer;
}

CVehicleFactory* CGameWorld::GetVehicleFactory() {
    return sGameWorld::GetInstance()->m_pVehicleFactory;
}
#define scriptLog(...) netLogger->LogInfo(INFO, true, __FUNCTION__,": " ,__VA_ARGS__)
void CGameWorld::GameWorldStateCheck() {
    WORLD_LOAD_S_CARRIER();
    WORLD_LOAD_N_CARRIER();
    WORLD_DISABLE_LOS_SANTOS();
    WORLD_LOAD_NY();
}

void CGameWorld::WORLD_LOAD_S_CARRIER() {
    if (this->m_GameStateInformation.test(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH) && !this->m_GameStateInformation.test(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_SOUTH)) {
        if (this->GetInteriorManager()->SummonInteriorOfType<eGameWorldState::S_AIRCRAFT_CARRIER>()) { //  alright we only need to check it once.
            scriptLogI("Enabling Interior: SOUTH_CARRIER");
            this->m_GameStateInformation.set(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_SOUTH, true);
            this->m_GameStateInformation.set(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH, false);
        }
    } else if (this->m_GameStateInformation.test(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_SOUTH) && !this->m_GameStateInformation.test(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH)) {
        if (this->GetInteriorManager()->DisableInteriorOfType<eGameWorldState::S_AIRCRAFT_CARRIER>()) {
            scriptLogI("Disabling Interior: SOUTH_CARRIER");
            this->m_GameStateInformation.set(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_SOUTH, false);
            this->m_GameStateInformation.set(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH, false);
        }
    }
}

void CGameWorld::WORLD_LOAD_N_CARRIER() {
    if (this->m_GameStateInformation.test(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH) && !this->m_GameStateInformation.test(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_NORTH)) {
        if (this->GetInteriorManager()->SummonInteriorOfType<eGameWorldState::N_AIRCRAFT_CARRIER>()) { //  alright we only need to check it once.
            scriptLogI("Enabling Interior: NORTH_CARRIER");
            this->m_GameStateInformation.set(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_NORTH, true);
            this->m_GameStateInformation.set(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH, false);
        }
    } else if (this->m_GameStateInformation.test(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_NORTH) && !this->m_GameStateInformation.test(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH)) {
        if (this->GetInteriorManager()->DisableInteriorOfType<eGameWorldState::N_AIRCRAFT_CARRIER>()) {
            scriptLogI("Disabling Interior: NORTH_CARRIER");
            this->m_GameStateInformation.set(eGWBS_WORLD_LOADED_AIRCRAFT_CARRIER_NORTH, false);
            this->m_GameStateInformation.set(eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH, false);
        }
    }
}

void CGameWorld::WORLD_DISABLE_LOS_SANTOS() { // its easy just enable heist island cullbox.
    int LOADBIT = eGWBS_WORLD_DISABLE_LOS_SANTOS;
    int LOADEDBIT = eGWBS_WORLD_DISABLED_LOS_SANTOS;
    const char* mInteriorName = "LOS_SANTOS";

    if (this->m_GameStateInformation.test(LOADBIT) && !this->m_GameStateInformation.test(LOADEDBIT)) {
        if (this->GetInteriorManager()->SummonInteriorOfType<DISABLE_LOS_SANTOS>()) { //  alright we only need to check it once.
            scriptLogI("Enabling Interior: ", mInteriorName);
            this->m_GameStateInformation.set(LOADEDBIT, true);
            this->m_GameStateInformation.set(LOADBIT, false);
        }
    } else if (this->m_GameStateInformation.test(LOADEDBIT) && !this->m_GameStateInformation.test(LOADBIT)) {
        if (this->GetInteriorManager()->DisableInteriorOfType<DISABLE_LOS_SANTOS>()) { // fuck y'all.
            scriptLogI("Disabling Interior: ", mInteriorName);
            this->m_GameStateInformation.set(LOADEDBIT, false);
            this->m_GameStateInformation.set(LOADBIT, false);
        }
    }
}

void CGameWorld::WORLD_LOAD_NY() {
    int LOADBIT = eGWBS_WORLD_LOAD_NORTH;
    int LOADEDBIT = eGWBS_WORLD_LOADED_NORTH;
    const char* mInteriorName = "NORTH_YANKTON";

    if (this->m_GameStateInformation.test(LOADBIT) && !this->m_GameStateInformation.test(LOADEDBIT)) {
        if (this->GetInteriorManager()->SummonInteriorOfType<NORTH_YANKTON>()) { //  alright we only need to check it once.
            scriptLogI("Enabling Interior: ", mInteriorName);
            this->m_GameStateInformation.set(LOADEDBIT, true);
            this->m_GameStateInformation.set(LOADBIT, false);
        }
    } else if (this->m_GameStateInformation.test(LOADEDBIT) && !this->m_GameStateInformation.test(LOADBIT)) {
        if (this->GetInteriorManager()->DisableInteriorOfType<NORTH_YANKTON>()) {
            scriptLogI("Disabling Interior: ", mInteriorName);
            this->m_GameStateInformation.set(LOADEDBIT, false);
            this->m_GameStateInformation.set(LOADBIT, false);
        }
    }
}

void CGameWorld::WORLD_LOAD_CAYO() { // two methods we either A) use the preexisting options which is just like two things or we load the ipls ourself. I choose just doing A because its easier. however having another way to launch would be nice.

}
void CGameWorld::OnEnterSp() {
    this->m_bMpMapActive = false;
    scriptLogI("called!");
    DLC::ON_ENTER_SP();
}
void CGameWorld::OnEnterMp() {
    this->m_bMpMapActive = true;
    scriptLogI("called!");
    DLC::ON_ENTER_MP();
}
bool CGameWorld::IsMpMapActive() {
    return this->m_bMpMapActive;
}

/*
    STREAMING::REMOVE_IPL("h4_mph4_terrain_01_grass_0");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_01_grass_1");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_02_grass_0");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_02_grass_1");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_02_grass_2");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_02_grass_3");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_04_grass_0");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_04_grass_1");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_04_grass_2");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_04_grass_3");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_05_grass_0");
    STREAMING::REMOVE_IPL("h4_mph4_terrain_06_grass_0");
    STREAMING::REQUEST_IPL("h4_ne_ipl_00");
    STREAMING::REQUEST_IPL("h4_ne_ipl_01");
    STREAMING::REQUEST_IPL("h4_ne_ipl_02");
    STREAMING::REQUEST_IPL("h4_ne_ipl_03");
    STREAMING::REQUEST_IPL("h4_ne_ipl_04");
    STREAMING::REQUEST_IPL("h4_ne_ipl_05");
    STREAMING::REQUEST_IPL("h4_ne_ipl_06");
    STREAMING::REQUEST_IPL("h4_ne_ipl_07");
    STREAMING::REQUEST_IPL("h4_ne_ipl_08");
    STREAMING::REQUEST_IPL("h4_ne_ipl_09");
    STREAMING::REQUEST_IPL("h4_nw_ipl_00");
    STREAMING::REQUEST_IPL("h4_nw_ipl_01");
    STREAMING::REQUEST_IPL("h4_nw_ipl_02");
    STREAMING::REQUEST_IPL("h4_nw_ipl_03");
    STREAMING::REQUEST_IPL("h4_nw_ipl_04");
    STREAMING::REQUEST_IPL("h4_nw_ipl_05");
    STREAMING::REQUEST_IPL("h4_nw_ipl_06");
    STREAMING::REQUEST_IPL("h4_nw_ipl_07");
    STREAMING::REQUEST_IPL("h4_nw_ipl_08");
    STREAMING::REQUEST_IPL("h4_nw_ipl_09");
    STREAMING::REQUEST_IPL("h4_se_ipl_00");
    STREAMING::REQUEST_IPL("h4_se_ipl_01");
    STREAMING::REQUEST_IPL("h4_se_ipl_02");
    STREAMING::REQUEST_IPL("h4_se_ipl_03");
    STREAMING::REQUEST_IPL("h4_se_ipl_04");
    STREAMING::REQUEST_IPL("h4_se_ipl_05");
    STREAMING::REQUEST_IPL("h4_se_ipl_06");
    STREAMING::REQUEST_IPL("h4_se_ipl_07");
    STREAMING::REQUEST_IPL("h4_se_ipl_08");
    STREAMING::REQUEST_IPL("h4_se_ipl_09");
    STREAMING::REQUEST_IPL("h4_sw_ipl_00");
    STREAMING::REQUEST_IPL("h4_sw_ipl_01");
    STREAMING::REQUEST_IPL("h4_sw_ipl_02");
    STREAMING::REQUEST_IPL("h4_sw_ipl_03");
    STREAMING::REQUEST_IPL("h4_sw_ipl_04");
    STREAMING::REQUEST_IPL("h4_sw_ipl_05");
    STREAMING::REQUEST_IPL("h4_sw_ipl_06");
    STREAMING::REQUEST_IPL("h4_sw_ipl_07");
    STREAMING::REQUEST_IPL("h4_sw_ipl_08");
    STREAMING::REQUEST_IPL("h4_sw_ipl_09");
    STREAMING::REMOVE_IPL("h4_islandairstrip");
    STREAMING::REMOVE_IPL("h4_islandx_mansion");
    STREAMING::REMOVE_IPL("h4_islandxdock");
    STREAMING::REMOVE_IPL("h4_islandxdock_props_2");
    STREAMING::REMOVE_IPL("h4_islandxtower");
    STREAMING::REMOVE_IPL("h4_islandx_maindock");
    STREAMING::REMOVE_IPL("h4_islandx_maindock_props_2");
    STREAMING::REMOVE_IPL("h4_IslandX_Mansion_Vault");
    STREAMING::REMOVE_IPL("h4_beach");
    STREAMING::REMOVE_IPL("h4_beach_bar_props");
    STREAMING::REMOVE_IPL("h4_islandx_checkpoint");
    STREAMING::REMOVE_IPL("h4_islandx_Mansion_Office");
    STREAMING::REMOVE_IPL("h4_islandx_Mansion_LockUp_01");
    STREAMING::REMOVE_IPL("h4_islandx_Mansion_LockUp_02");
    STREAMING::REMOVE_IPL("h4_islandx_Mansion_LockUp_03");
    STREAMING::REMOVE_IPL("h4_islandairstrip_hangar_props");
    STREAMING::REMOVE_IPL("h4_IslandX_Mansion_B");
    STREAMING::REMOVE_IPL("h4_islandairstrip_doorsclosed");
    STREAMING::REMOVE_IPL("h4_Underwater_Gate_Closed");
    STREAMING::REMOVE_IPL("h4_mansion_gate_closed");
    STREAMING::REMOVE_IPL("h4_aa_guns");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_01");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_02");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_03");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_04");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_05");
    STREAMING::REQUEST_IPL("H4_islandx_terrain_06");
    STREAMING::LOAD_GLOBAL_WATER_FILE(1);
    STREAMING::SET_MAPDATACULLBOX_ENABLED("prologue", 1);
*/
