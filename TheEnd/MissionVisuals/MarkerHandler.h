#pragma once
#include "MarkerInfo.h"
class MarkerHandler { 
public:
	MarkerHandler(CMarkerInfo& markerInfo);
	void DrawMarker(float x, float y, float z); // uses predefined size of visual marker;
private:
	const float xSize = 6.f;
	const float ySize = 6.f;
	const float zSize = 0.4f; // not sure. 
};