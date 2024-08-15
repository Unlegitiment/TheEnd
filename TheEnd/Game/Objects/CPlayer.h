#pragma once

class CPlayer {
private:
	typedef int					PlayerIndex;
	typedef int					PlayerModelIndex;
	typedef unsigned long long	PlayerModel;
	typedef int					PlayerVehicle;
	struct {
		PlayerIndex			iPlayerIndex; // PLAYER::PLAYER_ID();
		PlayerModelIndex	iPlayerModelIndex;
		PlayerModel			iPlayerModelInfo;
		PlayerVehicle* iVehicleInformation; // nullable
		bool				bIsPlayerInVehicle;
		bool				bIsPlayerAttemptingToGetIntoVehicle;
		PlayerVehicle		iAttemptedVehicleEntrance;
		bool				bIsInInterior;
	}PlayerInfo;
public:
	CPlayer();
	void Init();
	void Update();
	void Destroy();
};