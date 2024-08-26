#pragma once
#include <map>
#include <vector>
#include <bitset>
#include "../../SHVNative/natives.h"
enum eGameWorldState {
	S_AIRCRAFT_CARRIER,
	N_AIRCRAFT_CARRIER,
	CAYO_PERICO,
	NORTH_YANKTON,
	DISABLE_LOS_SANTOS,
	S_INTERIOR_MAX
};
enum eInteriorStatus {
	eIS_INTERIOR_LOADED,
	eIS_INTERIOR_UNLOADED,
	eIS_INTERIOR_FORCE_CLEANUP,
	eIS_PROG_GRAVE_UNLOADED,
	eIS_PROG_GRAVE_LOADED,
	eIS_MAX
};
struct s_InteriorState {
	eGameWorldState m_Interior;
	std::bitset<eIS_MAX> m_InteriorStatus;
};
class CInterior;
class CGameInteriorPrologue;
class CGameInteriorMgr {
private:
	CGameInteriorPrologue* m_pInterior_PROG;
	using IPL = const char*;
	struct sIplInfo {
		IPL IPL;
		bool isActive;
	};
	std::map<eGameWorldState, std::vector<sIplInfo>> m_Map;
	
	std::vector<CInterior*> m_AllInteriorsLoaded; // for full scale customly added interiors.
public:
	void UpdateThisPrologue();
	CGameInteriorPrologue* GetPrologueInterior();
	void DoSanityCheck(); // check the current IPL's that are loaded like actually on the game.  this should go into init.
	template<eGameWorldState e> bool SummonInteriorOfType();
	template<eGameWorldState e> bool DisableInteriorOfType();
	CGameInteriorMgr();
	void Init();
	void Destroy();
	~CGameInteriorMgr();
	void Update();
};

template<eGameWorldState e>
inline bool CGameInteriorMgr::SummonInteriorOfType() {
	if (e == eGameWorldState::DISABLE_LOS_SANTOS) {
		STREAMING::SET_MAPDATACULLBOX_ENABLED("HeistIsland", 0);
		return true;
	}
	if (e > m_Map.size()) {
		scriptLogW("eGameWorldState passed is greater than map size!");
		return false;
	}

	std::vector<sIplInfo> m_Vector = m_Map[e];
	for (int i = 0; i < m_Vector.size(); i++) {
		sIplInfo* curIpl = &m_Vector[i];
		STREAMING::REQUEST_IPL(curIpl->IPL);
		if (STREAMING::IS_IPL_ACTIVE(curIpl->IPL)) { // we don't need to be putting out like have a billion native calls a minute. so instead we have to modify our approach a tiny bit.
			curIpl->isActive = true;
		}
		if (i == m_Vector.size() - 1 && curIpl->isActive == true) {
			scriptLogI("All IPL's are initalized for interior passed!");
			return true;
		}
		scriptLogI("curIPL Information : \n\t", curIpl->IPL, "  ", curIpl->isActive);
	}
	return false;
}

template<eGameWorldState e>
inline bool CGameInteriorMgr::DisableInteriorOfType() {
	if (e == eGameWorldState::DISABLE_LOS_SANTOS) {
		STREAMING::SET_MAPDATACULLBOX_ENABLED("HeistIsland", 1);
		return true;
	}
	if (e > m_Map.size()) { // because we are checking outside of the bounds of the array because this can result in the program not working.
		scriptLogW("eGameWorldState passed is greater than map size!");
		return false;
	}

	std::vector<sIplInfo> m_Vector = m_Map[e];
	for (int i = 0; i < m_Vector.size(); i++) {
		sIplInfo* curIpl = &m_Vector[i];
		STREAMING::REMOVE_IPL(curIpl->IPL);
		if (!STREAMING::IS_IPL_ACTIVE(curIpl->IPL)) { // we don't need to be putting out like have a billion native calls a minute. so instead we have to modify our approach a tiny bit.
			curIpl->isActive = false;
		}
		if (i == m_Vector.size() - 1 && curIpl->isActive == false) {
			scriptLogI("All IPL's are disabled for interior passed!");
			return true;
		}
		scriptLogI("curIPL Information : \n\t", curIpl->IPL, "  ", curIpl->isActive);
	}
	return false;
}
