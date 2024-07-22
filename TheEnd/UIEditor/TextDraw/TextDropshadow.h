#pragma once
#include "../../SHVNative/types.h"
class CTextDropshadow{
public:
	CTextDropshadow(int dist, CRGBA colour);
	void changeColour(CRGBA newColour);
	void changeDistance(int newDistance);
	int getDistance();
	CRGBA getColour();
	void NativeCall();
private:
	CRGBA colour;
	int distance;
};