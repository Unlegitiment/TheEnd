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

bool CDisableScripts::RestartScript(ScrName name, int stackSize) { // The issue with Restarting Scripts is that they don't like to. lol. Shop_controller hates to restart same with veh_gen_controller etc.
    return false;
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
