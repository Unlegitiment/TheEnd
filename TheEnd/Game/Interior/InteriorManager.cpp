#include "InteriorManager.h"
#include "../../Logger/CLoggerInstances.h"
void CGameInteriorMgr::DoSanityCheck() {
}
CGameInteriorMgr::CGameInteriorMgr() {
	this->Init();
}

void CGameInteriorMgr::Init() {
	Logger->GetNetworkLogger()->LogInfo(INFO, true, __FUNCTION__, ": called! 0x", this);
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
	
}
