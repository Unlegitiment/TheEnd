#pragma once
/*
Purpose: More gradular control over the Prologue interior.
*/
#include <vector>
class CGameInteriorMgr;
class CGameInteriorPrologue {
private:
	CGameInteriorMgr* m_pInteriorMgr;
	using IPL = const char*;
	std::vector<IPL> m_vPreloadedIPLs;
	bool isInteriorActive;
	bool isGraveActive;
	std::vector<IPL> NY_SECTIONS_LOADED; //Only triggered through SummonInteriorAtIndex;
	
public:
	CGameInteriorPrologue(CGameInteriorMgr* mymgr);
	void Init();
	void Update();
	void SetGraveActive(bool _val);
	bool GetGraveActive();
	bool IsInteriorActive();
	void SummonGrave();
	void SummonBaseInterior();
	void SummonInteriorAtIndex(int index); // for the loading of a specific section. it can be weird btw.
	void Destroy();
	std::vector<IPL> GetAllIplsAssociated();
};