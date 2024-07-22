#pragma once
#include "../../TextDraw/Text.h"
#include "../../BoxDraw/CBoxUI.h"

class MenuContext {
public:
	MenuContext();
	void SetMenuCtxStr(std::string& text);
	void SetMenuContext(CTextUI* text);
	void SetNewBox(CBox* newBox);
	void SetInfo(bool _newInstance);
	
	CBox& GetBox();
	CTextUI& GetText();
	std::string& GetString() const;
	bool DoesInfo();
private:
	CTextUI*	m_Text;
	CBox*		m_Box;
	bool		m_bHasInfoSymbol;
};
class MenuContextDisplay {
public:
	MenuContextDisplay();
	void Draw(CTextUI& text, CBox& box, bool hasGTApadding = true);
	void Attach(CTextUI& text, CBox& _box);
private:
	
};
class MenuContextMgr {
public:
	MenuContextMgr();
	void Update();
	void SetText(CTextUI* text);
	void SetBox(CBox* box);
	void SetUsePadding(bool _newBool);
	void SetUseInfo(bool useInfo);
	void SetUpDefaults(CVector2 drawPos, float len, float height);
private:
	void Attach();
	bool useGTAPadding;
	/*
	* To avoid the fucking shitty ass while(true) shit so that you can actually take visual change with objects.
	*/
	void SHVInit();
	MenuContext* m_Text;
	MenuContextDisplay& m_Display;
};