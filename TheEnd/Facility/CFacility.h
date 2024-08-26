#pragma once
class CGameInteriorMgr;
class CFacility {
private:
	CGameInteriorMgr* m_pInteriorManager;
	const unsigned long long InteriorID = 269313;
	bool isInteriorActive = false;
public:
	CFacility(CGameInteriorMgr* mgr);
	void SummonBase();
	void SummonInteriorComponent(const char* m_component);
	void DesummonInteriorComponent(const char* m_component);
	void SetInteriorPropColor(const char* m_component, int color);
	void RefreshInterior();
	void Default();
};