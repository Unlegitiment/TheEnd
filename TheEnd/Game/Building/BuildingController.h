#pragma once 
#include <vector>
#include "../../SHVNative/types.h"

class CGameBuildingController {
	
	typedef CVector3<float> vEnterLocation;
	typedef CVector3<float> vExitLocation;
	typedef float			fMarkerRadius;
	typedef CBoundingBox	bbBoundBox;
	struct sBuilding {
		vEnterLocation mEnterPosition;
		vExitLocation  mExitLoc;
		fMarkerRadius  mDisplayMarkerRadius;
		bbBoundBox	   mEnterBox;
	};
};