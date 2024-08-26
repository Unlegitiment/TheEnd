#include "CDisable.h"
#include "../SHVNative/natives.h"
#include <map>
void CDisableScripts::PushBackScript(ScrName name) {
    m_AllScriptsToDisable.push_back({ false,name });
}

void CDisableScripts::Update() {
    for (int i = 0; i < m_AllScriptsToDisable.size(); i++) {
        ScrInfo* info = &m_AllScriptsToDisable[i]; // we use a pointer to make sure that we set the variables.
        MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(info->name);
        info->isDisabled = true;
    }
    scriptLogI("called.");
}
void CDisableScripts::RestartAllScripts() {
    std::map<ScrName, CDisableScripts::StackSize> m_ScriptMap;
    m_ScriptMap["shop_controller"] = SHOP_CONTROLLER;
    m_ScriptMap["blip_controller"] = DEFAULT;
    m_ScriptMap["vehicle_gen_controller"] = DEFAULT;
    m_ScriptMap["launcher_Racing"] = DEFAULT;
    m_ScriptMap["mission_triggerer_A"] = DEFAULT;
    m_ScriptMap["mission_triggerer_B"] = DEFAULT;
    m_ScriptMap["mission_triggerer_C"] = DEFAULT;
    m_ScriptMap["mission_triggerer_D"] = DEFAULT;
    m_ScriptMap["mission_repeat_controller"] = DEFAULT;
    m_ScriptMap["mission_Race"] = DEFAULT;
    scriptLogI("called. Restarting all Scripts for Freemode SP Experience.");
    for (int i = 0; i < m_AllScriptsToDisable.size(); i++) {
        ScrInfo* info = &m_AllScriptsToDisable[i];
        int stackSize = m_ScriptMap[info->name];
        int iAttempt = 0;
        scriptLogI("Current Script Information: \n\tName: ", info->name, " \n\tSize: ", stackSize);
        while (!CDisableScripts::RestartScript(info->name, (StackSize)stackSize)) {
            iAttempt++;
            if (iAttempt >= 11) {
                break; continue; // i wonder how this will work lul!
            }
            WAIT(0);
        }
        info->isDisabled = false;
    }
}

void CDisableScripts::StaggeredLoop(int* updateTimer) { // Todo -- Fix this as Update is either not called at all or can't be called.
    if (MISC::GET_GAME_TIMER() > (*updateTimer + 30000)) { // every 10 seconds we run this loop to determine the scripts nature.
        scriptLogI("called. Called on ", *updateTimer);
        this->Update();
        *updateTimer = MISC::GET_GAME_TIMER();
    }
}

void CDisableScripts::ClearAllScripts() {
}

void CDisableScripts::Destroy() {
}

bool CDisableScripts::RestartScript(ScrName name, StackSize stackSize) { // The issue with Restarting Scripts is that they don't like to. lol. Shop_controller hates to restart same with veh_gen_controller etc.
    ScrInfo info = { false, name };
    SCRIPT::REQUEST_SCRIPT(name);
    int iAttempts = 0;
    while (!SCRIPT::HAS_SCRIPT_LOADED(name)) {
        iAttempts += 1;
        scriptLogI(": Attempting Load. Attempt: ", iAttempts);
        if (iAttempts >= 11) {
            scriptLogE("Error encountered! Script: ", info.name, " could not be loaded in 10 attempts!");
            return false;
        }
        WAIT(0);
    }
    SYSTEM::START_NEW_SCRIPT(info.name, stackSize);
    SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(info.name);
    
    scriptLogI(info.name, ": Attempt Successful");
    return true;
}
std::string booltostr(bool b) {
    return b==true ? "TRUE" : "FALSE";
}
std::string CDisableScripts::GetLogStatement() {
    std::string buffer = "";
    for (ScrInfo _curinfo : m_AllScriptsToDisable) {
        buffer.append("\n\t");
        buffer.append(_curinfo.name);
        buffer.append("\t\t");
        buffer.append(booltostr(_curinfo.isDisabled));   
    }

    return buffer;
}
