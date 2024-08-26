#pragma once
#include "../../SHVNative/types.h"
class CPlayer {
private:
	typedef int					PlayerIndex;
	typedef int					PlayerModelIndex;
	typedef unsigned long long	PlayerModel;
	typedef int					PlayerVehicle;
	struct PlayerInfos{
		PlayerIndex			iPlayerIndex; // PLAYER::PLAYER_ID();
		PlayerModelIndex	iPlayerModelIndex;
		PlayerModel			iPlayerModelInfo;
		PlayerVehicle*		iVehicleInformation; // nullable
		bool				bIsPlayerInVehicle;
		bool				bIsPlayerAttemptingToGetIntoVehicle;
		PlayerVehicle		iAttemptedVehicleEntrance;
		bool				bIsInInterior;
		CVector3<float>		m_vPlayerPosition = {0,0,0};
	}PlayerInfo;
public:
	CPlayer();
	void Init();
	PlayerInfos* GetAllInformationAboutPlayer() { return &this->PlayerInfo; }
	void Update();
	void SetCoordinates(CVector3<float> _newCoords);
	void Destroy();
};