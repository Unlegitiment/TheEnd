#include "CPlayer.h"
#include "../../SHVNative/natives.h"
CPlayer::CPlayer() : PlayerInfo(CPlayer::PlayerInfos()){
	this->Init();
}

void CPlayer::Init() {
	this->PlayerInfo.bIsInInterior = false;
	this->PlayerInfo.iPlayerIndex = PLAYER::PLAYER_ID();
	this->PlayerInfo.iPlayerModelIndex = PLAYER::PLAYER_PED_ID();
	this->PlayerInfo.iVehicleInformation = nullptr;
	this->PlayerInfo.m_vPlayerPosition = ENTITY::GET_ENTITY_COORDS(this->PlayerInfo.iPlayerModelIndex, 1);
}

void CPlayer::Update() {
	this->PlayerInfo.m_vPlayerPosition = ENTITY::GET_ENTITY_COORDS(this->PlayerInfo.iPlayerModelIndex, 1);
}

void CPlayer::SetCoordinates(CVector3<float> _newCoords) {
	ENTITY::SET_ENTITY_COORDS(this->PlayerInfo.iPlayerModelIndex, _newCoords.x, _newCoords.y, _newCoords.z, 1, 0, 0, 0);
}

void CPlayer::Destroy() {
}
