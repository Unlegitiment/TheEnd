#include "PlayerMenu.h"
#include "../UIEditor/BoxDraw/CBoxUI.h"
#include "../UIEditor/TextDraw/Text.h"
#include <sstream>
CPlayerMenu::CPlayerMenu() {
}

void CPlayerMenu::SetHeader(const sHeaderInformation& header) {
	if (this->header == nullptr) {
		this->header = new sHeaderInformation();
		*this->header = header;
	} else {
		*this->header = header;
	}
}

void CPlayerMenu::AddMenuItem(const sMenuItem& menuItem) {
	this->MenuItems.push_back(menuItem);
	scriptLogI("Pushing item. 0x%p", &menuItem);
}

void CPlayerMenu::Display() {
	if (this->header != nullptr) {
		DisplayHeader();
	}
	for (int i = 0; i < this->MenuItems.size(); i++) {
		bool isSelected = false;
		if (i == m_iSelectedIndex) {
			isSelected = true;
		}
		auto& it = MenuItems[i];
		DisplayItem(it, i, isSelected);
	}
}

void CPlayerMenu::SetSelected(int _new) {
	this->m_iSelectedIndex = _new;
}

int CPlayerMenu::GetSelected() {
	return this->m_iSelectedIndex;
}

CPlayerMenu::sMenuItem* CPlayerMenu::GetItem(int index) {
	if (index > this->MenuItems.size()) {
		return nullptr;
	} else {
		return &this->MenuItems[index];
	}
}

void CPlayerMenu::DisplayItem(sMenuItem& menuItem, int index, bool selected) {
	float fY = (this->MenuScreenPosition.y + (fGlobalHeight * index)); // I think?
	CVector2<float> fDrawPosition = {this->MenuScreenPosition.x, fY};
	CBox box = CBox(fDrawPosition, {0,0,0,175}, fGlobalWidth, fGlobalHeight);

	CTextUI textL = CTextUI(menuItem.MenuLeft, { box.GetCornerPos(box.TOPLEFT).x + 0.005f, (box.GetCornerPos(box.TOPLEFT).y + (box.GetHeight() / 2)) - CTextUI::CharacterHeight(0.65, 0.35f)}, {255,255,255,255});
	textL.size = 0.35f;
	textL.hasOutline = false;
	textL.dropShadow = { 0,{0,0,0,0} };
	if (selected) {
		textL.colour = { 0,0,0,255 };
		box.SetColour({ 240,240,240,255 });
	}
	box.Draw();
	textL.Draw();

}
#include "../SHVNative/natives.h"
void CPlayerMenu::DisplayHeader() {
	float fSubHeaderY = (this->MenuScreenPosition.y - (fGlobalHeight / 2.0f)) - 0.019f;
	float fMainHeaderY = (fSubHeaderY- (fGlobalHeight / 2.0f)) - 0.045f;
	CVector2<float> screenPosMainHeader = { this->MenuScreenPosition.x, fMainHeaderY };
	CVector2<float> screenPosSubHeader = { this->MenuScreenPosition.x, fSubHeaderY };
	CBox box = CBox(screenPosSubHeader, { 0,0,0,175 }, this->fGlobalWidth, 0.03f);
	CBox header = CBox(screenPosMainHeader, { 45, 110, 185, 255 }, this->fGlobalWidth, 0.1f);
	float fSizeHeader = 0.6f;
	float fSize = 0.35f;
	float fPosYHeader = CTextUI::CharacterHeight(0.75, fSizeHeader);
	float fPosYSubHeader = CTextUI::CharacterHeight(fSize * 2.0f, fSize);
	CTextUI MainHeader = CTextUI(this->header->pHeaderString, {header.GetCornerPos(header.TOPLEFT).x + 0.005f, fMainHeaderY - fPosYHeader}, {255,255,255,255});
	MainHeader.size = fSizeHeader;
	CTextUI SubHeader = CTextUI(this->header->pSubHeaderString, { box.GetCornerPos(box.TOPLEFT).x + 0.0035f, fSubHeaderY - fPosYSubHeader }, { 255,255,255,255 });
	if (this->header->bDoesContainIndex) {
		std::stringstream myBuff;
		myBuff << this->m_iSelectedIndex + 1 << "/" << this->MenuItems.size();
		CTextUI ObjectText = CTextUI(myBuff.str(), { box.GetCornerPos(box.TOPRIGHT).x, fSubHeaderY - fPosYSubHeader}, {255,255,255,255});
		ObjectText.textJustification = 2;
		HUD::SET_TEXT_WRAP(0.0, box.GetCornerPos(box.TOPRIGHT).x - 0.003f);
		ObjectText.Draw();
	}
	SubHeader.size = fSize;
	SubHeader.Draw();
	MainHeader.Draw();
	header.Draw();
	box.Draw();
}
