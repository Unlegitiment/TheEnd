#include "InteriorManager.h"
#include "../../Logger/CLoggerInstances.h"
#include "GameInterior_PROLOGUE.h"
void CGameInteriorMgr::UpdateThisPrologue() {
	
}
CGameInteriorPrologue* CGameInteriorMgr::GetPrologueInterior() {
	UpdateThisPrologue();
	return this->m_pInterior_PROG;
}
void CGameInteriorMgr::DoSanityCheck() {
}
CGameInteriorMgr::CGameInteriorMgr() {
	this->Init();
}

void CGameInteriorMgr::Init() {
	scriptLogI("%s: called! 0x%p", this);
	//SOUTH
#pragma region SOUTH_CARRIER
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_carrier" , false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_carrier_DistantLights", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int1", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int2", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int3", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int4", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int5", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_Carrier_int6", false });
	m_Map[S_AIRCRAFT_CARRIER].push_back({ "hei_carrier_LODLights", false });
#pragma endregion
#pragma region NORTH_CARRIER
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int1",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int2",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int3",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int4",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int5",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_int6",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_carrier_ladders",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_legacyfixes",false });
	m_Map[N_AIRCRAFT_CARRIER].push_back({ "m24_1_pizzasigns",false});
#pragma endregion
#pragma region NORTH_YANKTON
	m_Map[NORTH_YANKTON].push_back({ "plg_01", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01c", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01c_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01d", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01d_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01e", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01e_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01f", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01f_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01g", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01h", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01h_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01i", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01i_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01j", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01j_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01k", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01k_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01z", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue01z_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_02", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue02", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue02_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_03", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03b", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03b_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03_grv_dug", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue03_grv_dug_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue_grv_torch", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_04", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue04", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue04_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue04b", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue04b_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue04_cover", false });
	m_Map[NORTH_YANKTON].push_back({ "des_protree_end", false });
	m_Map[NORTH_YANKTON].push_back({ "des_protree_start", false });
	m_Map[NORTH_YANKTON].push_back({ "des_protree_start_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_05", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue05", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue05_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue05b", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue05b_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_06", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06b", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06b_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06_int", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06_int_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06_pannel", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue06_pannel_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue_m2_door", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue_m2_door_lod", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_occl_00", false });
	m_Map[NORTH_YANKTON].push_back({ "prologue_occl", false });
	m_Map[NORTH_YANKTON].push_back({ "plg_rd", false });
	m_Map[NORTH_YANKTON].push_back({ "prologuerd", false });
	m_Map[NORTH_YANKTON].push_back({ "prologuerdb", false });
	m_Map[NORTH_YANKTON].push_back({ "prologuerd_lod", false });
#pragma endregion
#pragma region CAYO_PERICO
	m_Map[CAYO_PERICO].push_back({ "h4_islandairstrip", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandairstrip_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_mansion", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_mansion_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxdock", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxdock_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxdock_props_2", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxtower", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_maindock", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_maindock_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_maindock_props_2", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_Vault", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandairstrip_propsb", false });
	m_Map[CAYO_PERICO].push_back({ "h4_beach", false });
	m_Map[CAYO_PERICO].push_back({ "h4_beach_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_beach_bar_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_barrack_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_checkpoint", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_checkpoint_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_Mansion_Office", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_Mansion_LockUp_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_Mansion_LockUp_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_Mansion_LockUp_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandairstrip_hangar_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_B", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandairstrip_doorsclosed", false });
	m_Map[CAYO_PERICO].push_back({ "h4_Underwater_Gate_Closed", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mansion_gate_closed", false });
	m_Map[CAYO_PERICO].push_back({ "h4_aa_guns", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_GuardFence", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_Entrance_Fence", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_B_Side_Fence", false });
	m_Map[CAYO_PERICO].push_back({ "h4_IslandX_Mansion_Lights", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxcanal_props", false });
	m_Map[CAYO_PERICO].push_back({ "h4_beach_props_party", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_06_a", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_06_b", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_06_c", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_a", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_b", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_c", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_d", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_e", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandX_Terrain_props_05_f", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_01", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_02", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_03", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_04", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_05", false });
	m_Map[CAYO_PERICO].push_back({ "H4_islandx_terrain_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_00", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_04", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_05", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_07", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_08", false });
	m_Map[CAYO_PERICO].push_back({ "h4_ne_ipl_09", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_00", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_04", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_05", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_07", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_08", false });
	m_Map[CAYO_PERICO].push_back({ "h4_nw_ipl_09", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_00", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_04", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_05", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_07", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_08", false });
	m_Map[CAYO_PERICO].push_back({ "h4_se_ipl_09", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_00", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_04", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_05", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_07", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_08", false });
	m_Map[CAYO_PERICO].push_back({ "h4_sw_ipl_09", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_mansion", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandxtower_veg", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx_sea_mines", false });
	m_Map[CAYO_PERICO].push_back({ "h4_islandx", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_01_grass_0", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_01_grass_1", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_02_grass_0", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_02_grass_1", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_02_grass_2", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_02_grass_3", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_04_grass_0", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_04_grass_1", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_04_grass_2", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_04_grass_3", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_05_grass_0", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_06_grass_0", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_00", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_01", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_02", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_03", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_04", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_05", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_06", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_07", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_08", false });
	m_Map[CAYO_PERICO].push_back({ "h4_mph4_terrain_occ_09", false });
#pragma endregion
	DoSanityCheck(); // this will eventually do something.
}

void CGameInteriorMgr::Destroy() {
	for (int i = 0; i < S_INTERIOR_MAX; i++) {
		std::vector<sIplInfo> IPLINFO = m_Map[(eGameWorldState)i];
		for (int j = 0; j < IPLINFO.size(); j++) {
			sIplInfo* info = &IPLINFO[j];
			if (info->isActive) {
				STREAMING::REMOVE_IPL(info->IPL);
			}
		}
	}
}

CGameInteriorMgr::~CGameInteriorMgr() {
	this->Destroy();
}

void CGameInteriorMgr::Update() {
	bool isCloseToCayo = false;
	bool isWaterFileLoaded = false;
	if (MISC::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).z, 4700.0f, -5150.0f, 0.0f,0) < 2000.f) {
		isCloseToCayo = true;
	}
	if (isCloseToCayo && !isWaterFileLoaded && m_Map[CAYO_PERICO][2].isActive) { // check cayo loaded
		STREAMING::LOAD_GLOBAL_WATER_FILE(1);
		isWaterFileLoaded = true;
	} else {
		STREAMING::LOAD_GLOBAL_WATER_FILE(0);
	}
	this->GetPrologueInterior()->Update();
}
