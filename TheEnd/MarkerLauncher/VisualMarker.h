#pragma once
#include "../Marker/CMissionMarker.h"
#include "../MissionVisuals/MarkerInfo.h"
/*
* Purpose: Contains the Scaleform information and the Marker Information. USE THIS! Ignore CMarker unless you're making custom marker implementation
*/
class CVisMarker { 
public:
	CVisMarker(CMarkerInfo& markerInfo, CMissionMarker& marker);
	void DrawMarkerInfo(CVector3<float> rotation, CVector3<float> scale);
	void DrawMarker();
	void DrawAll(CVector3<float> MarkerInfoRotation, CVector3<float> MarkerInfoScale);
	void DrawDebugInformation(); // 2D might ignore because its not important.
	CMarkerInfo& getMarkerInfo();
	CMissionMarker& getMarker();
private:
	CMarkerInfo& m_Handler;
	CMissionMarker& m_Marker;
};