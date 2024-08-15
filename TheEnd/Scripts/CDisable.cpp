#include "CDisable.h"
#include "../SHVNative/natives.h"
void CDisableScripts::PushBackScript(ScrName name) {
    m_AllScriptsToDisable.push_back({ false,name });
}

void CDisableScripts::Update() {
    for (ScrInfo info : m_AllScriptsToDisable) {
            MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(info.name);
            info.isDisabled = true;
    }
}

void CDisableScripts::ClearAllScripts() {
}

void CDisableScripts::Destroy() {
}

bool CDisableScripts::RestartScript(ScrName name, StackSize stackSize) { // The issue with Restarting Scripts is that they don't like to. lol. Shop_controller hates to restart same with veh_gen_controller etc.
    ScrInfo info = { false, name };
    SCRIPT::REQUEST_SCRIPT(name);
    static int iAttempts = 0;
    while (!SCRIPT::HAS_SCRIPT_LOADED(name)) {
        iAttempts += 1;
        Logger->GetNetworkLogger()->LogInfo(INFO, true, info.name, ": Attempting Load. Attempt: ", iAttempts);
        if (iAttempts >= 11) {
            Logger->GetNetworkLogger()->LogInfo(ERROR2, true, "Error encountered! Script: ", info.name, " could not be loaded in 10 attempts!");
            return false;
        }
        WAIT(0);
    }
    SYSTEM::START_NEW_SCRIPT(info.name, stackSize);
    SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(info.name);
    
    Logger->GetNetworkLogger()->LogInfo(INFO, true, info.name, ": Attempt Succesful");
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
