#include "TextDropshadow.h"
#include "../../SHVNative/natives.h"
CTextDropshadow::CTextDropshadow(int dist, CRGBA<float> colour)
	:
	distance(dist),
	colour(colour)
{
	this->NativeCall();
}

void CTextDropshadow::NativeCall()
{
	HUD::SET_TEXT_DROPSHADOW(distance, colour.r, colour.g, colour.b, colour.a);
}

void CTextDropshadow::changeColour(CRGBA<float> newColour)
{
	this->colour = newColour;
	this->NativeCall();
}

void CTextDropshadow::changeDistance(int newDistance)
{
	this->distance = newDistance;
	this->NativeCall();
}

int CTextDropshadow::getDistance()
{
	return this->distance;
}

CRGBA<float> CTextDropshadow::getColour()
{
	return this->colour;
}
