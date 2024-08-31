#pragma once
class CHelpText {
protected:
	bool m_bIsHelpTextShowing;
	const char* m_TextString;
	bool m_bCanHelpTextShow;
public:
	void SetCanHelpTextShow(bool b);
	bool CanHelpTextShow();
	void SetHelpText(const char* text);
	const char* GetHelpText();
	bool IsHelpTextShowing();
	void SetHelpTextActive(bool b);
};