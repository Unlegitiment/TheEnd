#include "GameInterior.h"
#include "../../SHVNative/natives.h"
CInterior::CInterior() : CInterior(nullptr){
}

CInterior::CInterior(CGameInteriorMgr* mgr) :
	m_pInteriorMgr(mgr),
	m_bIsInteriorActive(false)
{
}

CGameInteriorMgr* CInterior::GetInteriorManager() {
	return this->m_pInteriorMgr;
}

void CInterior::AddEntry(IPL entry) {
	this->m_vIPLsAssociated.push_back(entry);
	scriptLogI("Called with param: ", entry, " \n\tUpdating m_vIPLsAssociated");
}

void CInterior::Delete() {
	for (IPL i : m_vIPLsAssociated) {
		scriptLogI("called! \n\t", i);
		STREAMING::REMOVE_IPL(i);  // I guess the Ipl isn't active?
	}
	m_bIsInteriorActive = false;
}

void CInterior::Request() {
	for (IPL i : m_vIPLsAssociated) {
		if (!STREAMING::IS_IPL_ACTIVE(i)) STREAMING::REQUEST_IPL(i); // i would run against a db of all known interiors but yk not really worth it.
	}
	m_bIsInteriorActive = true;
}

void CInterior::Destroy() {
	this->Delete();
}

bool CInterior::IsInteriorActive() {
	return m_bIsInteriorActive;
}

CInterior::~CInterior() {
	Destroy();
	
}
