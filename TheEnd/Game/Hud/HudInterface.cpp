#include "HudInterface.h"
#include "./CGameHelpText.h"
#include "./MiniMap.h"
#include "./CGameSpinner.h"
#include "./CWeaponWheel.h"
#include <cassert>
HudInterface::HudInterface() :
    m_pHelpText(new CGameHelpText()),
    m_pMinimap(MINIMAP),
    m_pSpinner(new CGameSpinner()),
    m_pWeaponWheel(new CGameWeaponWheel())
{
}
CGameHelpText* HudInterface::GetHelpText() {
    assert(this->m_pHelpText, scriptLogI("Couldn't find pointer to help text object might not be setup!"));
    
    return this->m_pHelpText;
}

CMinimap* HudInterface::GetMiniMap() {
    return this->m_pMinimap;
}

CGameSpinner* HudInterface::GetSpinner() {
    assert(m_pSpinner);
    return this->m_pSpinner;
}

CGameWeaponWheel* HudInterface::GetWeaponWheel() {
    assert(this->m_pWeaponWheel);
    return this->m_pWeaponWheel;
}
