#include "ArrowButton.h"
#define scriptAssert(cond) do{  }while(cond);
void CArrowButton::Attach()
{
	if(this->m_Text->text == EnumToStr(AB_UP)) this->m_Text->pos = CVector2(m_Box->GetDrawPos().x -0.001f, m_Box->GetDrawPos().y - 0.02f);
	else {
		this->m_Text->pos = CVector2(m_Box->GetDrawPos().x - 0.001f, m_Box->GetDrawPos().y - 0.03f);
	}
}
#include "../../../UI.h"
void CArrowButton::Draw(CTextUI* text, CBox* box)
{
	if (text == nullptr) {
		UI_DrawNotificationSTR("Text is null");
		return;
	}
	if (box == nullptr) {
		UI_DrawNotificationSTR("Box is null");
		return;
	}
	text->Draw();
	box->Draw(); 
}

CArrowButton::CArrowButton(CVector2& drawPos, eArrowBtn arrowBtn):
/*
* The issue with the following code is that it runs out of scope thus creating an issue with memory I likely could use shared_ptr because
* it would be more beneifical I just need to do more research to the lifetime of a shared_ptr because I am not sure when they actually end.
*/
m_Text(nullptr),
m_Box(nullptr)
{
	Init(drawPos, arrowBtn);
}


void CArrowButton::Init(CVector2& drawPosition, eArrowBtn arrowBtn)
{
	if (m_Box == nullptr) {
		m_Box = new CBox(drawPosition, CRGBA(0, 0, 0, 120), 0.1, 0.04);
	}
	if (m_Text == nullptr) {
		m_Text = new CTextUI(std::string(EnumToStr(arrowBtn)), drawPosition,0.514f, 3,CRGBA(255,255,255,255),CTextDropshadow(1,CRGBA(0,0,0,180)),new CMiddleJustify(), false);
		Attach();
	}
}

CBox& CArrowButton::GetBox()
{
	return *m_Box;
}

CTextUI& CArrowButton::GetText()
{
	return *m_Text;
}

void CArrowButton::SetText(CTextUI* _text)
{
	m_Text = _text;
}

void CArrowButton::SetBox(CBox* _box)
{
	m_Box = _box;
}

bool CArrowButton::GetPointIntersect(CVector2 point)
{
	return m_Box->GetIfPointIsInside(point);
}

void CArrowButton::Update()
{
	Attach();
	Draw(this->m_Text, this->m_Box);
	UpdateColor();
}

CArrowButton::~CArrowButton()
{
	if (m_Box != nullptr) {
		delete m_Box;
	}
	if (m_Text != nullptr) {
		delete m_Text;
	}
	return;
}

char* CArrowButton::EnumToStr(eArrowBtn btn)
{
	switch (btn) {
	case eArrowBtn::AB_LEFT:	return "1";
	case eArrowBtn::AB_RIGHT:	return "2";
	case eArrowBtn::AB_UP:		return "3";
	case eArrowBtn::AB_DWN:		return "4";
	};
}

void CArrowButton::UpdateColor()
{
	m_Text->colour = (m_Box->GetColour());
	m_Box->SetColour(m_Box->GetOriginalColor());
}


