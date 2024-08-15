#include "VisualMarker.h"
#include "../ScaleformHelper/CScaleform.h"
CVisMarker::CVisMarker(CMarkerInfo& markerInfo, CMissionMarker& marker) :
	m_Marker(marker),
	m_Handler(markerInfo)
{
	
}

void CVisMarker::DrawMarkerInfo(CVector3<float> rotation, CVector3<float> scale) {
	
	CScaleform markerInfoScaleform = CScaleform("MP_MISSION_NAME_FREEMODE");
	markerInfoScaleform.BeginMethod("SET_MISSION_INFO");
	markerInfoScaleform.LiteralStringPush(m_Handler.getMissionType());
	markerInfoScaleform.LiteralStringPush(m_Handler.getMissionName());
	markerInfoScaleform.LiteralStringPush(m_Handler.getPlayerInfo());
	markerInfoScaleform.LiteralStringPush(m_Handler.getPercentage());
	markerInfoScaleform.LiteralStringPush(m_Handler.getDebugVal());
	markerInfoScaleform.BoolPush(m_Handler.getifRockstarVerified());
	markerInfoScaleform.LiteralStringPush(m_Handler.getPlayerReq());
	markerInfoScaleform.LiteralStringPush(m_Handler.getRP());
	markerInfoScaleform.LiteralStringPush(m_Handler.getCash());
	markerInfoScaleform.LiteralStringPush(m_Handler.getTime()); // die please!
	markerInfoScaleform.EndFunction();
	markerInfoScaleform.Draw3DSolid(m_Marker.getPos(), rotation, 1, 1, 1, scale, 0);
}

void CVisMarker::DrawMarker() {
	m_Marker.Draw();
}

void CVisMarker::DrawAll(CVector3<float> MarkerInfoRotation, CVector3<float> MarkerInfoScale) { // Reason for MarkerInformation being outside the CMarkerInfo class is because to draw the Scaleform in 3D I have to have a rotation and in some cases like if you don't want the scaleform to be static than I have to take it as a parameter. 
	DrawMarker();
	DrawMarkerInfo(MarkerInfoRotation, MarkerInfoScale);
}

void CVisMarker::DrawDebugInformation() {
}

CMarkerInfo& CVisMarker::getMarkerInfo() {
	return this->m_Handler;
}

CMissionMarker& CVisMarker::getMarker() {
	return this->m_Marker;
}
