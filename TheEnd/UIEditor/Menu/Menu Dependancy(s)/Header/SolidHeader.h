#pragma once
#include "../../../BoxDraw/CBoxUI.h"
#include "../../../TextDraw/Text.h"
/*
* Smaller Header typically a subheader however can be bigger;
*/
class SSHeader {
public:
	SSHeader();
	CBox& GetBox();
	CTextUI& GetLeftText();
	CTextUI& GetRightText();

	void SetBox(CBox* box);
	void SetLeftText(CTextUI* left);
	void SetRightText(CTextUI* right);
private:
	CBox* m_Box;
	CTextUI* m_TextL;
	CTextUI* m_TextR;
};


class SSHeaderView {
public:
	SSHeaderView();
	void SetPadding(float paddingX, float paddingY);
	CVector2 GetPadding();
	void Draw(CBox* box, CTextUI* m_TextL, CTextUI* m_TextR);
private:
	float _paddingX_;
	float _paddingY_;
};

class SSHeaderController final {
public:
	SSHeaderController();
	SSHeaderController(SSHeader* header, SSHeaderView* hView); 
	void Update();
	void Init();
	
	void SetPadding(float x, float y);
	CVector2 GetPadding();
	void SetBox(CBox* box);
	CBox& GetBox();
	CTextUI& GetTextLeft();
	CTextUI& GetTextRight();

	void SetTextLeft(CTextUI* newText);
	void SetTextRight(CTextUI* newText);

	~SSHeaderController();
private:
	SSHeader*		m_Header;
	SSHeaderView*	m_View;
};