#include "Restart.h"
#include "../CDisable.h"
#include "../../Game/CGameWorld.h"
CTheEndRestartSP::CTheEndRestartSP(CDisableScripts* disabler, CGameWorld* gameworld) {
	this->m_pGameWorld = gameworld;
	this->m_pScriptDisabler = disabler;

    this->m_pScriptDisabler->PushBackScript("shop_controller"           );
    this->m_pScriptDisabler->PushBackScript("blip_controller"           );
    this->m_pScriptDisabler->PushBackScript("vehicle_gen_controller"            );
    this->m_pScriptDisabler->PushBackScript("launcher_Racing"           );
    this->m_pScriptDisabler->PushBackScript("mission_triggerer_A"           );
    this->m_pScriptDisabler->PushBackScript("mission_triggerer_B"           );
    this->m_pScriptDisabler->PushBackScript("mission_triggerer_C"           );
    this->m_pScriptDisabler->PushBackScript("mission_triggerer_D"           );
    this->m_pScriptDisabler->PushBackScript("mission_repeat_controller"         );
}

void CTheEndRestartSP::RestartFreemode_SP() { // restore all world stuff to defaults.
	if (this->m_pGameWorld->IsMpMapActive()) this->m_pGameWorld->OnEnterSp();
	this->m_pScriptDisabler->RestartAllScripts();
	
}

void CTheEndRestartSP::StopFreemode_SP() { // give the entire freemode experience the finger.
    if(!this->m_pGameWorld->IsMpMapActive())this->m_pGameWorld->OnEnterMp();
    this->m_pScriptDisabler->Update();
}
