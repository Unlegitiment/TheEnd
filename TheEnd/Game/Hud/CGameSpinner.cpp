#include "CGameSpinner.h"
#include "../../SHVNative/natives.h"
void CGameSpinner::SetText(const char* text) {
	this->m_Text = text;
}
const char* CGameSpinner::GetText() {
	return this->m_Text;
}
void CGameSpinner::StartRender() {
	HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(this->m_Text);
	HUD::END_TEXT_COMMAND_BUSYSPINNER_ON((int)this->m_Text);
}

void CGameSpinner::ForceStopRender() {
	HUD::BUSYSPINNER_OFF();
}
