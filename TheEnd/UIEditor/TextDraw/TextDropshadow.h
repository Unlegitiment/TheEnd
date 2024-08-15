#pragma once
#include "../../SHVNative/types.h"
class CTextDropshadow{
public:
	CTextDropshadow(int dist, CRGBA<float> colour);
	void changeColour(CRGBA<float> newColour);
	void changeDistance(int newDistance);
	int getDistance();
	CRGBA<float> getColour();
	void NativeCall();
private:
	CRGBA<float> colour;
	int distance;
};