#include "MiniMap.h"
#include "../../SHVNative/natives.h"
CMinimap::CMinimap() : m_bIsMinimapActive(true) {
    this->Init();
}

void CMinimap::Init() {
    this->m_bIsMinimapActive = HUD::IS_MINIMAP_RENDERING();
}

void CMinimap::Update() {
    return;
}

void CMinimap::SetMinimapActive(bool active) {
    this->m_bIsMinimapActive = active;  
    HUD::DISPLAY_RADAR(this->m_bIsMinimapActive);
}

bool CMinimap::IsMiniMapActive() {
    return this->m_bIsMinimapActive;
}
