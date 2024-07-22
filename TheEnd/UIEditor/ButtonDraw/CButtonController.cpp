/*
Notes for 2/6/24 ( and beyond ) :
	1.)Fix Logger ( Borke because file can't be found? ) 
	2.)Fix All Singleton(s)
	3.)Wrap Up products that I am doing (mainly like for example the NEXT_JOB_SELECT should be fixed;
	4.)Advance furthor into design pattern MVC/ MVVM
	5.)Maybe write or use a JSON Parser and download stuff from a webserver.
*/


#include "CButtonController.h"
#include "../../SHVNative/natives.h"
#define UNUSED_PARAM(x)

CButtonMgr::CButtonMgr(CButtonUI& buttonToSetup) :
	button(buttonToSetup),
	view(CButtonView())
{
	
	view.Draw(buttonToSetup, drawDebug);
}

//CButtonMgr::CButtonMgr(const CBox& box, const CTextUI* ltextUI) :
//	button(CButtonUI(const_cast<CBox&>(box))),
//	view(CButtonView())
//
//{
//	button.SetText(button.ETEXT_LEFT, ltextUI);
//}

void CButtonMgr::FlagDebugSymbols(bool newDebug)
{
	this->drawDebug = newDebug;
}

void CButtonMgr::handleMouse(CRGBA highlightColour, float mousePosX, float mousePosY)
{
	CVector2 mousePos = CVector2(mousePosX, mousePosY);
	if (button.GetBox().GetIfPointIsInside(mousePos)) {
		button.GetBox().SetColour(highlightColour);		
		return;
	}
	button.GetBox().SetColour(button.GetBox().GetOriginalColor());
}


void CButtonMgr::UpdateDrawPos(CVector2 drawPosition)
{
	button.SetNewDrawPos(drawPosition);
	Update();
}

void CButtonMgr::SetHeight(float _height)
{
	button.GetBox().SetHeight(_height);
	Update();
}

void CButtonMgr::SetWidth(float _width)
{
	button.GetBox().SetWidth(_width);
	Update();
}

void CButtonMgr::Update()
{
	for (int i = 0; i < button.ETEXT_MAX; i++) {
		if (button.GetText(static_cast<CButtonUI::eText>(i)) == NULL)continue;
		UpdateButtonAtIndex(i);
	}
}
void CButtonMgr::SetNewColor(CRGBA __newColor)
{
	this->button.GetBox().SetColour(__newColor);
}
bool CButtonMgr::isIndexValid(int index)
{
	if (index < CButtonUI::eText::ETEXT_MAX) {
		return true;
	}
	return false;
}
void CButtonMgr::UpdateButtonAtIndex(int index) {
	if (!isIndexValid(index)) { return; }
	button.IdealDraw(static_cast<CButtonUI::eText>(index), button.GetText(static_cast<CButtonUI::eText>(index)));
	
}

CButtonView::CButtonView()
{
}

void CButtonView::Draw(CButtonUI& xd,bool drawDebug)
{
	xd.GetBox().Draw();
	if(drawDebug) xd.GetBox().ShowDebugInfo(0.3f, 17);
	for (int i = 0; i < xd.ETEXT_MAX; i++) {
		if (xd.GetText(static_cast<CButtonUI::eText>(i)) == NULL) continue;
		xd.GetText(static_cast<CButtonUI::eText>(i))->Draw();
		if(drawDebug)
		xd.GetText(static_cast<CButtonUI::eText>(i))->DrawDebugInfo((i * 0.3f)+0.01f);
	}
}
