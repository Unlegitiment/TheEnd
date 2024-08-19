#include "GameInterior_PROLOGUE.h"
#include "../../SHVNative/natives.h"
CGameInteriorPrologue::CGameInteriorPrologue(CGameInteriorMgr* mymgr) {
	this->m_pInteriorMgr = mymgr;
	this->Init();
}

void CGameInteriorPrologue::Init() {
	scriptLogI("called! At: 0x",this);
	this->m_vPreloadedIPLs.push_back("plg_01 ");
	this->m_vPreloadedIPLs.push_back("prologue01 ");
	this->m_vPreloadedIPLs.push_back("prologue01_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01c ");
	this->m_vPreloadedIPLs.push_back("prologue01c_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01d ");
	this->m_vPreloadedIPLs.push_back("prologue01d_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01e ");
	this->m_vPreloadedIPLs.push_back("prologue01e_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01f ");
	this->m_vPreloadedIPLs.push_back("prologue01f_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01g ");
	this->m_vPreloadedIPLs.push_back("prologue01h ");
	this->m_vPreloadedIPLs.push_back("prologue01h_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01i ");
	this->m_vPreloadedIPLs.push_back("prologue01i_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01j ");
	this->m_vPreloadedIPLs.push_back("prologue01j_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01k ");
	this->m_vPreloadedIPLs.push_back("prologue01k_lod ");
	this->m_vPreloadedIPLs.push_back("prologue01z ");
	this->m_vPreloadedIPLs.push_back("prologue01z_lod ");
	this->m_vPreloadedIPLs.push_back("plg_02 ");
	this->m_vPreloadedIPLs.push_back("prologue02 ");
	this->m_vPreloadedIPLs.push_back("prologue02_lod ");
	this->m_vPreloadedIPLs.push_back("plg_03 ");
	this->m_vPreloadedIPLs.push_back("prologue03 ");
	this->m_vPreloadedIPLs.push_back("prologue03_lod ");
	this->m_vPreloadedIPLs.push_back("prologue03b ");
	this->m_vPreloadedIPLs.push_back("prologue03b_lod ");
	this->m_vPreloadedIPLs.push_back("prologue03_grv_dug ");
	this->m_vPreloadedIPLs.push_back("prologue03_grv_dug_lod");
	this->m_vPreloadedIPLs.push_back("prologue_grv_torch ");
	this->m_vPreloadedIPLs.push_back("plg_04 ");
	this->m_vPreloadedIPLs.push_back("prologue04 ");
	this->m_vPreloadedIPLs.push_back("prologue04_lod ");
	this->m_vPreloadedIPLs.push_back("prologue04b ");
	this->m_vPreloadedIPLs.push_back("prologue04b_lod ");
	this->m_vPreloadedIPLs.push_back("prologue04_cover ");
	this->m_vPreloadedIPLs.push_back("des_protree_end ");
	this->m_vPreloadedIPLs.push_back("des_protree_start ");
	this->m_vPreloadedIPLs.push_back("des_protree_start_lod ");
	this->m_vPreloadedIPLs.push_back("plg_05 ");
	this->m_vPreloadedIPLs.push_back("prologue05 ");
	this->m_vPreloadedIPLs.push_back("prologue05_lod ");
	this->m_vPreloadedIPLs.push_back("prologue05b ");
	this->m_vPreloadedIPLs.push_back("prologue05b_lod ");
	this->m_vPreloadedIPLs.push_back("plg_06 ");
	this->m_vPreloadedIPLs.push_back("prologue06 ");
	this->m_vPreloadedIPLs.push_back("prologue06_lod ");
	this->m_vPreloadedIPLs.push_back("prologue06b ");
	this->m_vPreloadedIPLs.push_back("prologue06b_lod ");
	this->m_vPreloadedIPLs.push_back("prologue06_int ");
	this->m_vPreloadedIPLs.push_back("prologue06_int_lod ");
	this->m_vPreloadedIPLs.push_back("prologue06_pannel ");
	this->m_vPreloadedIPLs.push_back("prologue06_pannel_lod ");
	this->m_vPreloadedIPLs.push_back("prologue_m2_door ");
	this->m_vPreloadedIPLs.push_back("prologue_m2_door_lod ");
	this->m_vPreloadedIPLs.push_back("plg_occl_00 ");
	this->m_vPreloadedIPLs.push_back("prologue_occl ");
	this->m_vPreloadedIPLs.push_back("plg_rd ");
	this->m_vPreloadedIPLs.push_back("prologuerd ");
	this->m_vPreloadedIPLs.push_back("prologuerdb ");
	this->m_vPreloadedIPLs.push_back("prologuerd_lod ");
}

void CGameInteriorPrologue::Update() {
}

void CGameInteriorPrologue::SummonGrave() {
}

void CGameInteriorPrologue::SummonBaseInterior() {
}

void CGameInteriorPrologue::SummonInteriorAtIndex(int index) {
}

void CGameInteriorPrologue::Destroy() {
}

std::vector<CGameInteriorPrologue::IPL> CGameInteriorPrologue::GetAllIplsAssociated() {
	return this->m_vPreloadedIPLs;
}
