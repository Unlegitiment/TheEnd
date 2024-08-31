#include "Hud.h"
#include "../Game/Hud/MiniMap.h"
#include "../SHVNative/types.h"
#include "../keyboard.h"
CTheEndLoadMenu* CTheEndHud::GetLoadingMenu() {
    return &this->mMenu;
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
    if (DoesDisplayMenu) {
        this->mMenu.Update();
    }
    if (!DoesDisplayMenu && !MINIMAP->IsMiniMapActive()) {
        MINIMAP->SetMinimapActive(true);
    }
    if (IsKeyJustUp(VK_F13)) {
        DoesDisplayMenu = !DoesDisplayMenu;
    }
}