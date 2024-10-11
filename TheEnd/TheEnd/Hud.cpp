#include "Hud.h"
#include "../Game/Hud/MiniMap.h"
#include "../SHVNative/types.h"
#include "../keyboard.h"
#include "../SHVNative/natives.h"
CTheEndLoadMenu* CTheEndHud::GetLoadingMenu() {
    return &this->mMenu;
}
CTheEndHud::CTheEndHud() :
    CheatMenu(MISC::GET_HASH_KEY("PAUSE_MENU"))
{
}
CFade* CTheEndHud::GetFade() {
    return &this->m_Fade;
}
bool CTheEndHud::IsLoadingMenuActive() {
    return this->DoesDisplayMenu;
}
void CTheEndHud::SetLoadingMenuActive(bool _new) {
    this->DoesDisplayMenu = _new;
}
void CTheEndHud::OneTick() {
    this->mMenu.Init();
}

void CTheEndHud::Update() {
    this->GetFade()->Update();
    if (DoesDisplayMenu) {
        this->mMenu.Update();
    }
    if (!DoesDisplayMenu && !MINIMAP->IsMiniMapActive()) {
        MINIMAP->SetMinimapActive(true);
    }
    if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(CheatMenu)) {
        DoesDisplayMenu = !DoesDisplayMenu;
    }

    
}
