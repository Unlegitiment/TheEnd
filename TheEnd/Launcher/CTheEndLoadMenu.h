#pragma once
#include "./GameLoadMenu.h"
#include "../SHVNative/types.h"
class CTheEndLoadMenu : private CLoadMenu {
public:
	CTheEndLoadMenu();
	void Init();
	void Update();
private:
	int m_iSelection = 0;
	int DX_Texture = 0;
	CLoadButton Button1;
	CLoadButton Button2;
	CLoadButton Button3;
private:
	void HandleLeftPress();
	void HandleRightPress();
	static void HandleButton1Press(CLoadButton* load); // oh yeah we could make this an enum or just like void the shit?
	static void HandleButton2Press(CLoadButton* load);
	static void HandleButton3Press(CLoadButton* load);
	void DrawFullMenu();
	void DrawStylizedButton(CLoadButton* loadButton, CVector2<float> position);
};
// we can also have background of the MenuPage that can be indeed activated. however for now we are just gonna define background as a big black box. 
