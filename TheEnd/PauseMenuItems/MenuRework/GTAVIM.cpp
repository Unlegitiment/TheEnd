#include "GTAVIM.h"
#include "../../UIEditor/BoxDraw/CBoxUI.h"
#include "../../UIEditor/TextDraw/Text.h"
#include "../../SHVNative/natives.h"
CGTAVMenu::CGTAVMenu(const CVector2<float>& __menubasepos) : MenuPos((CVector3<float>&)__menubasepos), m_Header(CGTAVHeader("", "", "")){
}

void CGTAVMenu::AddItem(baseMenuItem* item) {
	this->items.push_back(item);
}

void CGTAVMenu::Show() {
	this->m_bIsMenuShown = true;
	this->m_Header.Draw();
	for (int i = 0; i < items.size(); i++) {
		baseMenuItem* menuItem = items[i];
	}
}

void CGTAVMenu::Hide() {
	
}

CGTAVMenu::CGTAVHeader::CGTAVHeader(const char* param0, const char* param1, const char* param2) : MenuPlayerName(param0), MenuName(param1), MenuIndex(param2), baseHeader({ 0.5,0.5 }) {
}

void CGTAVMenu::CGTAVHeader::Draw() { // we know our offset so we just draw at the coordinate specified  by the offset. 
	float test = 0.6f;
	float fText = 0.35f;
	CBox mainBox = CBox(this->GetOffset(), { 45, 110, 185, 255 }, 0.225f, 0.1f);
	CVector2<float> fSubHeaderLocation = { this->GetOffset().x, this->GetOffset().y + mainBox.GetHeight() / 2.0f };
	CBox subheader = CBox(fSubHeaderLocation, { 0,0,0, 255 }, 0.225f, 0.03f);
	CVector2<float> HeaderPosition = { mainBox.GetCornerPos(mainBox.TOPLEFT).x + 0.005f, mainBox.GetCornerPos(mainBox.TOPLEFT).y + (mainBox.GetHeight() / 2.0f) - CTextUI::CharacterHeight(test*2.0f, test)};
	CTextUI textRenderable_Player = CTextUI(this->MenuPlayerName, HeaderPosition, {255,255,255,255});
	textRenderable_Player.size = test;
	CVector2<float> fMNamePos = {subheader.GetCornerPos(mainBox.TOPLEFT).x + 0.0035f, subheader.GetDrawPos().y - CTextUI::CharacterHeight(fText*2.0F, fText)};
	CTextUI textRenderable_MenuName = CTextUI(this->MenuName, fMNamePos, {255,255,255,255});
	textRenderable_MenuName.size = fText;
	CVector2<float> fMIdPos = { 1.0, subheader.GetDrawPos().y - CTextUI::CharacterHeight(fText * 2.0F, fText) };

	CTextUI textRenderable_MenuId = CTextUI(this->MenuIndex, fMIdPos, {255,255,255,255});
	textRenderable_MenuId.size = fText;
	mainBox.Draw();
	subheader.Draw();
	textRenderable_Player.Draw();
	textRenderable_MenuName.Draw();
	textRenderable_MenuId.textJustification = 2;
	HUD::SET_TEXT_WRAP(0.0, subheader.GetCornerPos(subheader.BOTTOMRIGHT).x - 0.0025f);
	textRenderable_MenuId.Draw();
}

