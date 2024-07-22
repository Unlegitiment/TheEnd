#include "TheEnd.h"
#include "../UIEditor/TextDraw/Text.h"
#include "../SHVNative/natives.h"
#include "../keyboard.h"
#include "../SHVNative/enums.h"
bool CTheEnd::isMissionActive = false;
void CTheEnd::Run(int byteSelect) {
	CVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	if (1 << 0 & byteSelect) {
		this->SetMissionActive(true); // kewl.
		while (this->GetMissionActive()) {
			this->RequestAllModels();

		}
	} else {
		if (playerCoords.Dist(this->markerPos) < this->marker.getScale().x) { // we might have issues with coords because they sometimes have issues with Dist calcs try flipping the operation.
			CTextUI("Player is registered as in coords", CVector2(0.3, 0.3), CRGBA(255, 255, 255, 255)).Draw();
			if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
				this->OnTransition();//Trigger Transition (this enables the mission active
			}
		}
	}
}

void CTheEnd::OnTransition() {
	CVector3 positionToWarpTo = { 0,0,0 }; // Todo: Make it that of the coords in the interior
	int switchState = STREAMING::GET_PLAYER_SWITCH_STATE();
	STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, ePlayerSwitchTypes::SWITCH_TYPE_LONG);
	if (switchState == 8) { // we maxed on height
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), positionToWarpTo.x, positionToWarpTo.y, positionToWarpTo.z, 1, 0, 0, 1);
		STREAMING::ALLOW_PLAYER_SWITCH_DESCENT();
		STREAMING::SWITCH_TO_MULTI_SECONDPART(PLAYER::PLAYER_PED_ID()); //yesyyes
		this->Run((1 << 0)); //workie
	}
}

void CTheEnd::RequestAllModels() {

}

void CTheEnd::PrepareModels() {//this is gonna load models into the vectors to be used in request models

}

void CTheEnd::Destroy() {
	/*
		for(Hash h : this->m_models){GAME::SET_MODEL_AS_NO_LONGER_NEEDED(&h);} // go fuck yorself
		for(Hash h : this->m_vehicles){GAME::DELETE_VEHICLE(&h);} // go fuck yorself
		for(Hash h : this->m_peds){GAME::DELETE_PED(&h);} // go fuck yorself
	*/
}


/*
*
switch(missionState){
case eMissionState::EMS_PRELOAD:
	this->RequestAllModels();
	missionState = eMissionState::ePauseMenu_Active;
	break;
case eMissionState::ePauseMenu_Active;
	this->ActivatePauseMenu();
	if(static_cast<CMissionMenu>(PauseMenuInterface::GetPauseMenuMgr()->GetActiveMenu()).IsButtonPressed(CMissionMenu::ePauseButtons::START_JOB)){
		missionState = eMissionState::CheckPoint1;
	}
	break;
case eMissionState::CheckPoint1:
	this->DoWakeUpAnimation(); // take while here
	//do nothing until player is outside interior
	BoundingBox box = BoundingBox({interiorPos}, {interiorRot});
	if(!box.isCoordInside(playerCoords)){
		missionState = eMissionState::CheckPoint2;
	}
	break;
case eMissionState::CheckPoint2: // we are outside and surrounded by military
	BoundingBox box = BoundingBox({milPos});
	this->SummonAllPedsRelativeToPlayer((1 << 0)); // send a bit manip that allows the player to be attacked by military.
	if(ENTITY::GET_HEALTH(PLAYER::PLAYER_PED_ID()) < 0){
		static_cast<CScoreboardMenu>(PauseMenuInterface::GetPauseMenuMgr()->SummonScoreboard((1 << CScoreboardMenu::PLAYER_DEATH))).Draw();
		StatsMgr::GetPlayerStats().IncrementDeath(1);
	if(!box.isCoordsInside(playerCoords)){
		missionState = eMissionState::CheckPoint3;
	}
	break;
case eMissionState::CheckPoint3: // outside military base swarmed with police Escape to LSIA
	doOnce(MINIMAP::SET_WAYPOINT({LSIA_LOC}));
	RenderMissionText("~y~Escape ~w~to LSIA");
	PAD::ENABLE_CONTROL(eControl::PhoneUp);
	if(LSIA_LOC.Dist(playerCoords) < 250){
		doOnce(RenderTextMessage("iFruit", "Welcome to your new phone! Where we spy on your data! Stop running...", eContactPFP::IFRUIT_CONTACT_TXD));
	}
	if(LSIA_LOC.Dist(playerCoords)< 100){ // also add checks in here to prevent overlapping since Checkpoint4 can send back here.
		doOnce(RenderTextMessage("???", "So you were the project they were working on all this time. We could meet however it appears you have your hands tied. Goodbye friend.", eContactPFP::UNKNOWN_CONTACT));
	}
	if(LSIA_LOC.Dist(playerCoords) < 50){
		missionState = eMissionState::CheckPoint4;
	}
	break;
case eMissionState::Checkpoint4: // we are at the airport if we have cops we must wait to lose them.
	if(PLAYER::GET_WANTED_LEVEL() > 0){
		RenderMissionText("Lose the cops.");
	}
	if(LSIA_LOC.Dist(playerCoords) > 100){
		missionState = eMissionStateCheckPoint3;
	}
	if()
	break;
}
*/