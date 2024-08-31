#include "CGameHelpText.h"
#include "../../SHVNative/natives.h"
const char* CGameHelpText::GetHelpString() {
	return this->m_TextString;
}

void CGameHelpText::SetHelpText(const char* text) {
	this->m_TextString = text; // kys
}

void CGameHelpText::RenderNow() {
	if (this->CanHelpTextShow()) {
		this->SetHelpTextActive(true);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(this->m_TextString);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 0, -1);
	}
}

bool CGameHelpText::CanHelpTextRender() {
	return this->m_bCanHelpTextShow;
}

void CGameHelpText::SetHelpTextCanRender(bool b) {
	this->m_bCanHelpTextShow = b;
}

void CGameHelpText::RenderForTime(float fDelta, int msToDisplay) {
	if (fDelta < MISC::GET_GAME_TIMER() + msToDisplay) { // ok
		RenderNow();
	}
}
