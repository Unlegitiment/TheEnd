#pragma once
#include <vector>
class CGameInteriorMgr;
class CInterior { // for our own sake just make this polymorphic recommended
private:
	using IPL = const char*;
	std::vector<IPL> m_vIPLsAssociated;
	CGameInteriorMgr* m_pInteriorMgr; // who to check the lifetime of the object.
	bool m_bIsInteriorActive;
public:
	CInterior();
	CInterior(CGameInteriorMgr* mgr);
	CGameInteriorMgr* GetInteriorManager();
	void AddEntry(IPL entry);
	void Delete();
	void Request();
	void Destroy();
	/*
	Warning: This does NOT check if the interior is actually loaded in the game it just checks the current variable stored at it.
	*/
	bool IsInteriorActive();
	std::vector<IPL>* GetAllAssociatedIPLS() { return &this->m_vIPLsAssociated; }
	~CInterior();
};