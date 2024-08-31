#include "HudInterface.h"
#include "./CGameHelpText.h"
#include "./MiniMap.h"
#include "./CGameSpinner.h"
#include <cassert>
HudInterface::HudInterface() :
    m_pHelpText(new CGameHelpText()),
    m_pMinimap(MINIMAP),
    m_pSpinner(new CGameSpinner())
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
