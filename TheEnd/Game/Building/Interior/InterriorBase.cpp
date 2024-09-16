#include "InterriorBase.h"
#include "../../../SHVNative/natives.h"
#include "./InteriorMgr.h"
baseInterior::baseInterior(CInteriorMgr* mgr) : m_pManager(mgr), m_State(""){
}

void baseInterior::UpdateMgr() {
	if (this->m_pManager) {
		scriptLogI("[INTERIOR] Updating the Manager's Data");
		this->m_pManager->ForceUpdate();
	}
}

void baseInterior::PushIPL(const char* IPL) {
	if (STREAMING::IS_IPL_ACTIVE(IPL)) {
		this->m_IPLS.Add({ IPL, true });
	} else {
		this->m_IPLS.Add({ IPL, false });
	}
}

void baseInterior::Trigger() {
	scriptLogI("called");
	for (int i = 0; i < this->m_IPLS.GetVector().size(); i++) {
		auto* x = &this->m_IPLS[i];
		scriptLogI("[INTERIOR] Requesting IPL: ", x->ipl); // this is kinda annoying
		STREAMING::REQUEST_IPL(x->ipl);
		x->isIPLActive = true;
	}
	UpdateMgr();
}

void baseInterior::Despawn() {
	scriptLogI("");
	for (int i = 0; i < this->m_IPLS.GetVector().size(); i++) {
		auto* x = &this->m_IPLS[i];
		STREAMING::REMOVE_IPL(x->ipl);
		x->isIPLActive = false;
		scriptLogI("[INTERIOR] Removing IPL: ", x->ipl); // this is kinda annoying
	}
	UpdateMgr();
}

void baseInterior::RemoveIPL(int index) {
	sIPLInfo* ipl = &this->m_IPLS[index];
	this->m_IPLS.GetSet().erase(*ipl); // find it then remove it lul
}

void baseInterior::RemoveIPL(const char* ipl) {
	sIPLInfo y = { ipl, STREAMING::IS_IPL_ACTIVE(ipl) };
	auto x = this->m_IPLS.GetSet().find(y);
	this->m_IPLS.GetSet().erase(x);
}

CInteriorMgr* baseInterior::GetManager() {
	return this->m_pManager;
}

baseInterior::sInteriorInformation::sInteriorInformation(const char* interiorName) {
	this->m_strInteriorName = interiorName; // ugh me want die!
}
