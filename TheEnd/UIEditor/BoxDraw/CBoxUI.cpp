#include "CBoxUI.h"
#include "../../SHVNative/natives.h"
CBox::CBox() :
	drawPos(CVector2<float>(0,0)),
	colour(CRGBA<float>(0,0,0,0)),
	width(0.f),
	height(0.f),
	corners{ CVector2<float>(0,0),CVector2<float>(0,0), CVector2<float>(0,0), CVector2<float>(0,0) },
	originalColor(colour)
{
}
CBox::CBox(CVector2<float> _drawPos, CRGBA<float> _colour, float _length, float _height):
	drawPos(_drawPos),
	colour(_colour),
	width(_length),
	height(_height),
	corners{CVector2<float>(0,0),CVector2<float>(0,0), CVector2<float>(0,0), CVector2<float>(0,0)},
	originalColor(_colour)
{
	this->UpdateCornerPos();
	return;
}

void CBox::SetNewDrawPos(CVector2<float> drawPos)
{
	this->drawPos = drawPos;
	UpdateCornerPos();
}

void CBox::SetWidth(float Width)
{
	this->width = Width;
	UpdateCornerPos()  ;
}

void CBox::SetHeight(float height)
{
	this->height = height;
	UpdateCornerPos();
}

float CBox::GetWidth()
{
	return this->width;
}

float CBox::GetHeight()
{
	return this->height;
}

void CBox::Draw()
{
	
	GRAPHICS::DRAW_RECT(this->drawPos.x, this->drawPos.y, this->width, this->height, this->colour.r, this->colour.g, this->colour.b, this->colour.a, false);
}

CVector2<float>& CBox::GetDrawPos()
{
	return this->drawPos;
}

CVector2<float>& CBox::GetCornerPos(Corner cornerToGet)
{
	if (cornerToGet > Corner::CORNER_MAX - 1) cornerToGet = Corner::TOPLEFT;
	if (cornerToGet < Corner::TOPLEFT) cornerToGet = Corner::TOPLEFT;
	return corners[cornerToGet];
}

CRGBA<float> CBox::GetColour()
{
	return this->colour;
}

void CBox::SetColour(CRGBA<float> __newColour__)
{
	this->colour = __newColour__;
}
#include "../TextDraw/Text.h"
void CBox::DrawDebugText(const std::string& debugText, float x, float yOffset, int lineIndex)
{
	CTextUI debugTextUI(debugText, CVector2(x, ((0.61f + yOffset) * lineIndex) / 900.0F), CRGBA<float>(255, 255, 255, 200));

	debugTextUI.Draw();
}

void CBox::ShowDebugInfo(float x, float yOffset)
{
	// 0.1f Height Change
	DrawDebugText("dPos: " + drawPos.toStr(), x, yOffset, 7);
	DrawDebugText("Corners:", x,yOffset,8);
	DrawDebugText("		TLPos: " + corners[TOPLEFT].toStr(), x, yOffset, 9);
	DrawDebugText("		TRPos: " + corners[TOPRIGHT].toStr(), x, yOffset, 10);
	DrawDebugText("		BLPos: " + corners[BOTTOMLEFT].toStr(), x, yOffset, 11);
	DrawDebugText("		BRPos: " + corners[BOTTOMRIGHT].toStr(), x, yOffset, 12);
	DrawDebugText("COL: " + colour.toStr(), x, yOffset, 13);
	DrawDebugText("WID: " + std::to_string(width), x, yOffset, 14);
	DrawDebugText("HGT: " + std::to_string(height), x, yOffset, 15);
}

bool CBox::GetIfPointIsInside(CVector2<float> point)
{
	if (point.x >= GetCornerPos(TOPLEFT).x && point.x <= GetCornerPos(TOPRIGHT).x) {
		if (point.y <= GetCornerPos(BOTTOMLEFT).y && point.y >= GetCornerPos(TOPLEFT).y) {
			return true;
		}
	}
	return false;
}

CRGBA<float> CBox::GetOriginalColor()
{
	return originalColor;
}

void CBox::SetNewOriginalColor(CRGBA<float> newColor)
{
	this->originalColor = newColor;
}

void CBox::UpdateCornerPos()
{
	this->corners[Corner::TOPLEFT].x = this->drawPos.x - (this->width / 2.0F);
	this->corners[Corner::TOPLEFT].y = this->drawPos.y - (this->height / 2.0F);

	this->corners[Corner::TOPRIGHT].x = this->corners[Corner::TOPLEFT].x + this->width;
	this->corners[Corner::TOPRIGHT].y = this->corners[Corner::TOPLEFT].y;

	this->corners[Corner::BOTTOMLEFT].x = this->corners[Corner::TOPLEFT].x;
	this->corners[Corner::BOTTOMLEFT].y = this->corners[Corner::TOPLEFT].y + this->height;

	this->corners[Corner::BOTTOMRIGHT].x = this->corners[Corner::TOPRIGHT].x;
	this->corners[Corner::BOTTOMRIGHT].y = this->corners[Corner::TOPRIGHT].y + this->height;
}
