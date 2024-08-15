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
	CBox(CVector2<float> _drawPos, CRGBA<float> _colour, float _length, float _height);

	void SetNewDrawPos(CVector2<float> drawPos);
	void SetWidth(float Width);
	void SetHeight(float height);
	float GetWidth();
	float GetHeight();
	void Draw();
	CVector2<float>& GetDrawPos();
	CVector2<float>& GetCornerPos(Corner cornerToGet);
	CRGBA<float> GetColour() ;
	void SetColour(CRGBA<float> __newColour__);
	void ShowDebugInfo(float x, float yOffset);
	void DrawDebugText(const std::string& debugText, float x, float yOffset, int lineIndex);
	bool GetIfPointIsInside(CVector2<float> point);
	CRGBA<float> GetOriginalColor();
	void SetNewOriginalColor(CRGBA<float> newColor);
private:
	void UpdateCornerPos();
	CVector2<float> drawPos;
	CVector2<float> corners[CORNER_MAX];
	CRGBA<float> colour;
	CRGBA<float> originalColor;
	float width, height;

};