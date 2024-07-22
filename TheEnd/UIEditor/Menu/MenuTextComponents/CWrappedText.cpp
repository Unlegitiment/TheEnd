#include "CWrappedText.h"
#include "../../../ScriptHookV/natives.h"
CWrappedText::CWrappedText(CTextUI& text, float minTextPosition, float maxTextPosition) :
	m_Box(CBox(text.pos,CRGBA(0,0,0,0),minTextPosition,maxTextPosition)),
	text(text)
{
	SetupWrap(minTextPosition, maxTextPosition);
}

void CWrappedText::Draw()
{
	text.Draw();
}

void CWrappedText::SetupWrap(float minText, float maxText)
{
	text.SetTextJustification(new CLeftTextWrapped(minText,maxText));
	return;
}

void CLeftTextWrapped::SetupText()
{
	HUD::SET_TEXT_JUSTIFICATION(1);
	HUD::SET_TEXT_WRAP(minX, maxX);
}

int CLeftTextWrapped::GetType()
{
	return 1;
}

void CLeftTextWrapped::NativeCaller()
{
	
}
