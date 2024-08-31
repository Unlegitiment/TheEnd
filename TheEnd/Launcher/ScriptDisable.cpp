#include "ScriptDisable.h"
#include "../SHVNative/natives.h"
CTheEndScriptDisabler::CTheEndScriptDisabler() :
    m_pScriptDisabler(CDisableScripts()),
    m_iStaggeredLoopTimer(0),
    m_bCanStaggeredLoopRun(false)
{
    this->Init();
}
void CTheEndScriptDisabler::SetDisablerActive(bool _new) {
    this->m_bCanStaggeredLoopRun = _new;
}
bool CTheEndScriptDisabler::CanDisablerRun() {
    return this->m_bCanStaggeredLoopRun;
}
CDisableScripts* CTheEndScriptDisabler::GetScriptDisabler() {
    return &this->m_pScriptDisabler;
}
void CTheEndScriptDisabler::Init() {
    this->m_pScriptDisabler.PushBackScript("shop_controller"); // SHOP
    this->m_pScriptDisabler.PushBackScript("blip_controller"); // BLIP
    this->m_pScriptDisabler.PushBackScript("vehicle_gen_controller"); // PV
    this->m_pScriptDisabler.PushBackScript("launcher_Racing"); // RACING_LAUNCHER
    this->m_pScriptDisabler.PushBackScript("mission_triggerer_A"); // MISSION #1
    this->m_pScriptDisabler.PushBackScript("mission_triggerer_B"); // MISSION #2
    this->m_pScriptDisabler.PushBackScript("mission_triggerer_C"); // MISSION #3
    this->m_pScriptDisabler.PushBackScript("mission_triggerer_D"); // MISSION #4
    this->m_pScriptDisabler.PushBackScript("mission_repeat_controller"); // MISSION_REPEAT
    this->m_pScriptDisabler.PushBackScript("mission_Race"); // RACING
    this->m_iStaggeredLoopTimer = MISC::GET_GAME_TIMER();
    scriptLogI("Initalized!");
}
void CTheEndScriptDisabler::Update() {
    if(this->m_bCanStaggeredLoopRun) this->m_pScriptDisabler.StaggeredLoop(&this->m_iStaggeredLoopTimer);
}
