#pragma once
#include "../../SHVNative/types.h"
class CBox {
public:
	enum Corner {
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		CORNER_MAX
	};
	CBox();
	CBox(CVector2 _drawPos, CRGBA _colour, float _length, float _height);

	void SetNewDrawPos(CVector2 drawPos);
	void SetWidth(float Width);
	void SetHeight(float height);
	float GetWidth();
	float GetHeight();
	void Draw();
	CVector2& GetDrawPos();
	CVector2& GetCornerPos(Corner cornerToGet);
	CRGBA GetColour() ;
	void SetColour(CRGBA __newColour__);
	void ShowDebugInfo(float x, float yOffset);
	void DrawDebugText(const std::string& debugText, float x, float yOffset, int lineIndex);
	bool GetIfPointIsInside(CVector2 point);
	CRGBA GetOriginalColor();
	void SetNewOriginalColor(CRGBA newColor);
private:
	void UpdateCornerPos();
	CVector2 drawPos;
	CVector2 corners[CORNER_MAX];
	CRGBA colour;
	CRGBA originalColor;
	float width, height;

};