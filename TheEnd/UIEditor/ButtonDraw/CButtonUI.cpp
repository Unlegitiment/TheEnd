#include "CButtonUI.h"
CButtonUI::CButtonUI(CBox& __button__)
	: 
	m_Box(__button__),
	m_Buttons {  } //when we zero everything it has some adverse side effects
{
}

//CButtonUI::CButtonUI(CBox& __button__, CHighlightContext __highlightContext__)
//	: 
//	m_HighlightCtx(__highlightContext__),
//	m_Box(__button__),
//	m_Buttons{ 0 }
//{
//}

CButtonUI CButtonUI::CreateDraw(CBox& __box__)
{
	return CButtonUI(__box__);
}

CButtonUI::~CButtonUI()
{
	for (int i = 0; i < ETEXT_MAX; i++) {
		delete m_Buttons[i];
	}
	
}

void CButtonUI::SetNewDrawPos(CVector2<float> __drawPos__)
{
	this->m_Box.SetNewDrawPos(__drawPos__);
	
}

CBox& CButtonUI::GetBox() 
{
	return m_Box;
}


void CButtonUI::SetNewBox(CBox& __box)
{
	this->m_Box = __box;
	return;
}

CTextUI* CButtonUI::GetText(eText textToReq) 
{
	if (textToReq > eText::ETEXT_MAX-1) textToReq = eText::ETEXT_LEFT;
	if (textToReq < eText::ETEXT_LEFT) textToReq = eText::ETEXT_LEFT;
	return this->m_Buttons[textToReq];
}

void CButtonUI::SetText(eText textToSet, const CTextUI* textToInput)
{
	
	if (textToSet > eText::ETEXT_MAX - 1) textToSet = eText::ETEXT_LEFT;
	if (textToSet < eText::ETEXT_LEFT) textToSet = eText::ETEXT_LEFT;
	IdealDraw(textToSet, const_cast<CTextUI*>(textToInput));
	//LOGGER_INSTANCE.Log(Logger::LogSeverity::LG_CRASH, "The crash line will be performed just after");
	m_Buttons[static_cast<size_t>(textToSet)] = const_cast<CTextUI*>(textToInput);
	return;
}
void CButtonUI::IdealDraw(CButtonUI::eText textToSet, CTextUI* textToInput) {
	//LOGGER_INSTANCE.InfoLog("IdealDraw Called with param(s): " +textToSet + reinterpret_cast<unsigned long long>(&textToInput));
	if (textToSet == eText::ETEXT_LEFT) {
		CVector2 topLeft = m_Box.GetCornerPos(CBox::TOPLEFT);
		//CVector2 bottomLeft = m_Box.GetCornerPos(CBox::BOTTOMLEFT);
		textToInput->pos = CVector2(topLeft.x + topLeft._paddingX_ + 0.0F, (topLeft.y + (m_Box.GetHeight() / 2.0F)) - (textToInput->size / 20.0F));
	}
	if (textToSet == eText::ETEXT_MIDDLE) {
		CVector2 drawPos = m_Box.GetDrawPos();
		textToInput->pos = CVector2<float>(drawPos.x, (drawPos.y -0.001 - (textToInput->size / 20.0F)));
	}
	if (textToSet == eText::ETEXT_RIGHT) {
		CVector2 topRight = m_Box.GetCornerPos(CBox::TOPRIGHT);
		textToInput->pos = CVector2(topRight.x - topRight._paddingX_ + 0.0F, (topRight.y + (m_Box.GetHeight() / 2.0F)) - (textToInput->size / 20.0F));
	}
	return;
}
//void CButtonUI::Draw()
//{
//}
