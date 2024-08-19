#include "CustomRespawn.h"
#include "../../GlobalUpdateThread.h"
void CRespawn::RespawnPlayer() {
	CPlayer* player = sGameWorld::GetInstance()->GetLocalPlayer();
	/*
	* CVector3<float> hospitalLocation = CRespawn::GetBestHospitalForDeath(player->GetCoordinates());
	* CSyncronizedScene respawn = player->StartSyncronizedScene();
	* CAnimDictionary animDict = {"anim@player_respawn@hospital"};
	* animDict.Request();
	* player->PlaySyncedScene(animDict, "death_character_1a", hospitalLocation) // this doesn't work pseudocode.
	* if(respawn.GetProgression() >= 1.0f){
	*	//were done here
	*	player->SetSyncronizedSceneEntityAsNoLongerUsed();
	*	player->SetAsMissionEntity(); // no despawn pls.
	*	respawn.SetAsNoLongerUsed();
	*	respawn.Invaldate();
	* }
	*/
}

void CRespawn::RespawnEntity(int entityHandle) {
}

void CRespawn::RespawnAtHospital(CPlayer* player) {
}

void CRespawn::Update(bool updatenow) {
}
