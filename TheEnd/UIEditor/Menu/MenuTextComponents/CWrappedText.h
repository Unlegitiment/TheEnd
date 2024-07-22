#pragma once
#include "../../BoxDraw/CBoxUI.h"
#include "../../TextDraw/Text.h"
/*
* Length of text should be equal to the length of a specific box.
*/
class CLeftTextWrapped : public TextJustify {
public:
	CLeftTextWrapped(float min, float max) :
		minX(min), maxX(max) {}
	void SetupText() override;
	int GetType() override;
protected:
	float minX, maxX;
	void NativeCaller() override;
};
class CWrappedText {
public:
	/*
	* These will be equal to the position of the text;
	*/
	CWrappedText(CTextUI& text, float minTextPosition, float maxTextPosition); 
	void Draw();
private:
	void SetupWrap(float minText, float maxText);
	CBox& m_Box; //Virtualized Box mainly for Debug Purposes so that we can see where the box actually wraps.
	CTextUI& text;
};
class CWrappedDraw {
	CWrappedDraw();
	void Draw();
private:
	CWrappedText& textToDraw;
};