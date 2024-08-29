#pragma once
#include <string>
class CLoadMenu;
class CLoadButton {
private:
	CLoadMenu* m_pOwner;
	std::string m_sText;
	bool m_bIsHighlighted;
	using Func = void(*)(CLoadButton*); // Ok Whatever lets go.
	Func MyCallback;
	friend class CLoadMenu;
public:
	void CallCallback();
	void SetFunction(Func call_back);
	CLoadMenu* GetOwner();
	std::string* GetText();
	bool IsHighlighted();
	void SetHighlighted(bool stat);
	void SetText(std::string text);
	CLoadButton(CLoadMenu* menu, Func callback);
};