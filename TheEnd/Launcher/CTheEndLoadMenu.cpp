#include "CTheEndLoadMenu.h"
#include "../UIEditor/TextDraw/Text.h"
#include "../UIEditor/BoxDraw/CBoxUI.h"
#include "../SHVNative/main.h"
#include "../SHVNative/natives.h"
#include "../Game/Hud/MiniMap.h"
CTheEndLoadMenu::CTheEndLoadMenu() : 
	Button1(this, CTheEndLoadMenu::HandleButton1Press), 
	Button2(this, CTheEndLoadMenu::HandleButton2Press),
	Button3(this, CTheEndLoadMenu::HandleButton3Press)
{

}

void CTheEndLoadMenu::Init() {
	this->SetHeader(__FUNCTION__);
	this->DX_Texture = createTexture(".\\TheEndAssets\\g83.png");
	this->Button1.SetText("Story Mode");
	this->Button2.SetText("The End Offline");
	this->Button3.SetText("Online (soonTM)");
	this->PushNewButton(&this->Button1);
	this->PushNewButton(&this->Button2);
	this->PushNewButton(&this->Button3);
}

void CTheEndLoadMenu::Update() {
	HUD::SET_MOUSE_CURSOR_THIS_FRAME();
	DrawFullMenu();
}
void CTheEndLoadMenu::HandleLeftPress() {
}
void CTheEndLoadMenu::HandleRightPress() {
}
void CTheEndLoadMenu::HandleButton1Press(CLoadButton* load) {
	scriptLogI("Pressed!");
}
void CTheEndLoadMenu::HandleButton2Press(CLoadButton* load) {
	scriptLogI("Pressed!");
}
void CTheEndLoadMenu::HandleButton3Press(CLoadButton* load) {
	scriptLogI("Pressed!");
}
void CTheEndLoadMenu::DrawFullMenu() {
	//Header info
	MINIMAP->SetMinimapActive(false);
	float opacity = 255;
	float f_globalscale = 2.25;
	CBox background = CBox({ 0.5,0.5 }, { 0,0,0, opacity }, 1, 1);
	background.Draw();
	//customize header to use only surrounding of box instead of the entire thing. since just concept don't worry about it.
	float screenAspect = GRAPHICS::GET_ASPECT_RATIO(1);
	drawTexture(this->DX_Texture, 0, 0, 60, 0.1*f_globalscale, 0.08*f_globalscale, 0.5, 0.5, 0.15f, 0.8f, 0, screenAspect, 1.0, 1.0, 1.0, 1.0);
	//Button load.
	for (int i = 0; i < this->GetButtons()->size(); i++) {
		CLoadButton* curButton =  (*GetButtons())[i];
		CVector2<float> location = { 0.2f + (0.3f * i), 0.35f  }; // todo - fix this so that it actually outputs right location for text. 
		DrawStylizedButton(curButton, location);
	}
}

void CTheEndLoadMenu::DrawStylizedButton(CLoadButton* loadButton, CVector2<float> position) {
	float fMouseClick = PAD::GET_CONTROL_NORMAL(0, 237); // CURSOR_ACCEPT
	float fMouseX = PAD::GET_CONTROL_NORMAL(0, 239); // CURSOR_X
	float fMouseY = PAD::GET_CONTROL_NORMAL(0, 240); // CURSOR_Y
	CVector2<float> mousePos = { fMouseX, fMouseY };
	CBox box = CBox(position, { 255,255,255,255 }, 0.20, 0.05);
	CTextUI text = CTextUI(*loadButton->GetText(), position, { 255,255,255,255 });
	text.size = 0.7f;
	text.textJustification = 0;
	CVector2<float> _newDrawLocation = { position.x, position.y + text.CharacterHeight(1) };
	box.SetNewDrawPos(_newDrawLocation);
	if (box.GetIfPointIsInside(mousePos)) {
		loadButton->SetHighlighted(true);
	} else {
		loadButton->SetHighlighted(false);
	}
	
	if (loadButton->IsHighlighted()) {
		if (fMouseClick) {
			loadButton->CallCallback();
		}
		text.colour = { 0,0,0,255 };
		text.hasOutline = false;
	} else {
		text.hasOutline = true;
	}
	text.Draw();

	box.Draw();
}
