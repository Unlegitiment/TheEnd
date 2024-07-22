#pragma once
#include "../../BoxDraw/CBoxUI.h" //Should reference Text Lib?
#include "../../TextDraw/Text.h"
#include "../Menu.h"
class CArrowButton {
public:
	enum eArrowBtn {
		AB_LEFT		= 1,
		AB_RIGHT	= 2,
		AB_UP		= 3,
		AB_DWN		= 4
	};
	CArrowButton(CVector2& drawPos, eArrowBtn arrowBtn);
	//This will effectively be a constructor as the previous two don't do what I'd like them to do;
	void Init(CVector2& drawPositon, eArrowBtn arrowButton); 
	CBox& GetBox();
	CTextUI& GetText();
	void SetText(CTextUI* _text);
	void SetBox(CBox* _box); 
	bool GetPointIntersect(CVector2 point);
	void Update();
	/*
	* This is a one time use item after that call Update because that will get Ideal DrawPosition for the box;
	*/
	void Attach();
	static void Draw(CTextUI* text, CBox* box);
	~CArrowButton(); 
	char* EnumToStr(eArrowBtn btn);
private:
	void UpdateColor();
	CBox*		m_Box;
	CTextUI*	m_Text;
};
