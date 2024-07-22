#include "TextJustify.h"
#include "../../SHVNative/natives.h"
void CLeftJustify::SetupText()
{
	HUD::SET_TEXT_JUSTIFICATION(1);
}

void CLeftJustify::NativeCaller()
{
	HUD::SET_TEXT_JUSTIFICATION(this->GetType());
}


CRightJustify::CRightJustify(float start, float end) 
	:
	m_Start(start),
	m_End(end)
{

}

void CRightJustify::SetupText()
{
	HUD::SET_TEXT_JUSTIFICATION(2);
	HUD::SET_TEXT_WRAP(m_Start, m_End);
}

void CRightJustify::NativeCaller()
{
}


void CMiddleJustify::SetupText()
{
	HUD::SET_TEXT_JUSTIFICATION(0);
}

void CMiddleJustify::NativeCaller()
{
}

