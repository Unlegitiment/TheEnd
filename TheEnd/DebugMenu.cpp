#include "DebugMenu.h"
#include "./keyboard.h"
CDebugMenu::CDebugMenu() :
	CPlayerMenu(CPlayerMenu())
{
	this->SetHeader({"DEBUG","DEBUG MENU", true}); // context to have around as many as I need to disp.
}

void CDebugMenu::Update() {
	if (this->m_bIsDBGMenuDisp) {
		this->Display();
	}
	if (IsKeyJustUp(this->KEYCOMBO)) {
		this->m_bIsDBGMenuDisp = !this->m_bIsDBGMenuDisp;
		scriptLogI("Debug menu active status: %i", this->m_bIsDBGMenuDisp);
	}
}
