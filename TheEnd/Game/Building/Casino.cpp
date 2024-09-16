#include "Casino.h"

CCasino::CCasino() : baseInterior(nullptr), m_State() {
	this->Init();
}

void CCasino::Init() {
	this->PushIPL("hei_dlc_casino_door");
	this->PushIPL("vw_dlc_casino_door"); // everyday i wish to relief myself of this trash code!
}

void CCasino::Trigger() {
	::baseInterior::Trigger();
	this->m_State.m_bHasCasinoDoorsLoaded = true;
}

void CCasino::Despawn() {
	::baseInterior::Despawn();
	this->m_State.m_bHasCasinoDoorsLoaded = false;
}

CCasino::sCasinoState::sCasinoState() : sInteriorInformation("MP_SCRIPT_CASINO") {
}
