#pragma once
#include "../../SHVNative/types.h"
class CGameWorld;
class CGameWater;
class CGameWaterManager {
private:
	CGameWorld* m_pWorldInstance;
	enum eGameWaterState {
		EGWS_LOS_SANTOS,
		EGWS_HEIST_ISLAND
	};
	eGameWaterState m_CurWaterState;
public:
	CGameWaterManager(CGameWorld* worldmanager);
	void ChangeActiveGlobalWaterState(eGameWaterState wtrState); // YOU CANNOT PIPE A CHANGE HERE. FOR BOTH WATER STATES DOESN'T WORK.
	eGameWaterState GetCurWaterState(); // validate with the STREAMING::GET_CURRENT_GLOBAL_WATER_STATE();
	CGameWater* GetWaterAtCoordinate(CVector3<float> pos); // So this is for the points where like say we have a water at a point and we want to modify certain characteristics about it.
	
};