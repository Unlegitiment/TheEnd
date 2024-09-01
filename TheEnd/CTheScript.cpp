#include "CTheScript.h"
#include "./Game/Objects/CPlayer.h"
#include "./Game/CGameWorld.h"
#include "./Launcher/ScriptDisable.h"
#include "./keyboard.h"
#include "./UIEditor/TextDraw/Text.h"
#include "./Game/Hud/CGameHelpText.h"
#include "./Game/Hud/CGameSpinner.h"
#include "./Game/Hud/HudInterface.h"
#include "./TheEnd/Hud.h"
/*
	TODO -- Write up a quick class to do vehicles and their modifications. 
	Also cause shop controller is annoying for this we might just have to void the shop controller when we get close and restart it when we are done. Or Leave the area. 
		Cause I don't know how shop controller works or at least how it tracks conflicts with the models so I can't write my own to get around the controller yet. 
	Write up a Deluxo Class as a part of that vehicle class. As we have the CVehicle class. 
	Maybe write up a CTheEndDeluxo that just deals with the respawning and management of the Launcher?
*/
void CTheScript::OneTime() {
	MISC::GET_GROUND_Z_FOR_3D_COORD(-1725.449f, -190.3516f, 103.0902f, &this->m_fZGroundZCoord_UFO, 1, 0); // for a nice onetime calc
	STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("DELUXO"));
	DELUXO = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), 47.2755f, -862.1296f, 30.05f, 340.8, 1, 0, 1);
	VEHICLE::SET_VEHICLE_MOD_COLOR_1(DELUXO, 4, 0, 0); 
	VEHICLE::SET_VEHICLE_MOD_COLOR_2(DELUXO, 4, 0);
	VEHICLE::SET_SPECIAL_FLIGHT_MODE_ALLOWED(DELUXO, 0);
	VEHICLE::SET_DISABLE_HOVER_MODE_FLIGHT(DELUXO, 0);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(DELUXO, "OUTATIME");
}

bool isWithinCircle(float x, float y, float circleX, float circleY, float radius) {
	// Calculate the squared distance from the point to the circle's center
	float dx = x - circleX;
	float dy = y - circleY;
	float distanceSquared = dx * dx + dy * dy;

	// Compare squared distance with squared radius
	return distanceSquared <= radius * radius;
}

void CTheScript::Update() {
	this->isPlayerInDeluxo = PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), DELUXO, 0);
	if (this->isPlayerInDeluxo) {
		m_bSetVehicleDensityNow = this->isPlayerInDeluxo;
		BoxCheck();
	}
	if (m_bSetVehicleDensityNow) {
		ClearTraffic();
	}
	SetupEnvironment();
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("CLEARSCRFX"))) {
		this->Cheat_CLEARSCRFX();
	}
	CVector3<float> pos = WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition;
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("GOTODELUXO"))) {
		this->Cheat_GOTODELUXO();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DEVSTAR_UT1")) || this->CurrentLevel == (int)CHECKPOINT::DREAM_SEQUENCE) {
		m_bRenderUFOEffect = true;
		float fLaunch = MISC::GET_GAME_TIMER();
		WORLD->SetTimePersist(true, { 0,0,0 });
		WORLD->SetBlackoutState(false);
		if (!HUD::DOES_BLIP_EXIST(Blip_MainObj)) {
			scriptLogI("Main Obj blip does not exist!");
			BlipSetup();
		}
		this->CurrentLevel = (int)CHECKPOINT::DREAM_SEQUENCE;
		UFOSetup();
	}
	if (m_bRenderUFOEffect) {
		GRAPHICS::DRAW_MARKER(1, -1725.449f, -190.3516f, this->m_fZGroundZCoord_UFO - 2.0f, 0, 0, 0, 0, 0, 0, 10, 10, 55, 93, 182, 229, 60, 0, 0, 0, 0, nullptr, nullptr, 0);
		GRAPHICS::DRAW_LIGHT_WITH_RANGEEX(-1725.449f, -190.3516f, this->m_fZGroundZCoord_UFO, 255, 255, 255, 10, 10, 64);
	}
	if (isWithinCircle(pos.x, pos.y, -1725.309, -190.1009, 4.80) && CurrentLevel == (int)CHECKPOINT::DREAM_SEQUENCE) { //ok ive had enough of this shit
		GAMEHUD->GetHelpText()->SetHelpText("Press ~INPUT_CONTEXT~ to wake up.");
		GAMEHUD->GetHelpText()->SetHelpTextCanRender(m_bDisplayHelpText);
		GAMEHUD->GetHelpText()->RenderNow();
		if (PAD::IS_CONTROL_JUST_PRESSED(0, 51)) {
			m_bDisplayHelpText = false;
			SetupWarp();
		}
		if (Scene.GetSceneProgression() >= 0.95) {
			scriptLogI("Finished ready for warp");
			m_bDisplayHelpText = true;
			Scene.Destroy();
			this->StartWarp();
		}
	}
	if (m_bsWarp.test(WARP_HAS_STARTED)) {
		if (STREAMING::GET_PLAYER_SWITCH_STATE() == 5) {
			STREAMING::SWITCH_TO_MULTI_SECONDPART(WarpPed);
			m_bsWarp.set(WARP_TRANSITIONING, 1);
			ambienceConfig.ClearAll();
			m_bsWarp.reset(WARP_HAS_STARTED);
		}
	}
	if (m_bsWarp.test(WARP_TRANSITIONING)) {
		GAMEHUD->GetSpinner()->ForceStopRender();
		GAMEHUD->GetSpinner()->SetText("Transitioning");
		GAMEHUD->GetSpinner()->StartRender();
		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 1);
		WORLD->GetLocalPlayer()->SetCoordinates({ -1873.391, 3748.26, -99.3408 });
		if (STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
			GAMEHUD->GetSpinner()->ForceStopRender();
			m_bsWarp.set(WARP_ENDING, 1);
			m_bsWarp.reset(WARP_TRANSITIONING);
		}
	}
	//END ANIMATION WAKE: 0.763802
	if (m_bsWarp.test(WARP_ENDING)) {
		PED::DELETE_PED(&this->WarpPed);
		m_bsWarp.reset(WARP_ENDING);
	}
	CTextUI(std::to_string(STREAMING::GET_PLAYER_SWITCH_STATE()), { 0.5,0.525 }, { 255,255,255,255 }).Draw();
	if (IsKeyJustUp(VK_MULTIPLY) || MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("STOPSYNC"))) {
		scriptLogI("Cancelling Script Scene");
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}
	if (IsKeyJustUp(VK_ADD)) {
		EHUD->GetFade()->DoWhiteScreenFade(false);
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("TESTANIM"))) {
		SetupWarp();
	}
	if (this->CurrentLevel == (int)CHECKPOINT::INSIDE_INTERIOR) {
		static bool isSceneRunning = false;
		static bool hasWarpDone = false;
		static bool hasAmbienceCleared = false;
		static bool hasConfiguredScene = false;
		if (!hasAmbienceCleared) {
			scriptLogI("TEST");
			this->ambienceConfig.ClearAll();
			this->isAwoken = true;
			this->m_bConfigureAmbience = false;
			this->m_bIsAmbienceConfigured = false;

			HUD::REMOVE_BLIP(&this->Blip_MainObj);
			hasAmbienceCleared = true;
		}
		while ((!STREAMING::HAS_ANIM_DICT_LOADED("switch@michael@wakes_up_screaming"))) {
			STREAMING::REQUEST_ANIM_DICT("switch@michael@wakes_up_screaming");
			DLC::ON_ENTER_MP();
			WAIT(0);
		}
		if (!hasWarpDone) {
			//ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1873.391, 3748.26, -99.8408, 1, 0, 0, 0);
			hasWarpDone = true;
		}
		if (!hasConfiguredScene) {
			//this->m_iSceneId = PED::CREATE_SYNCHRONIZED_SCENE(-1873.391, 3748.2637, -99.8408, 0.0, 0.0, -8.9672, 2);
			hasConfiguredScene = true;
		}
		if (!isSceneRunning) {
			scriptLogI("Scene is not running. Must start running scene!");
			//TASK::TASK_SYNCHRONIZED_SCENE(PLAYER::PLAYER_PED_ID(), m_iSceneId, "switch@michael@wakes_up_screaming", "001671_02_mics2_1_wakes_up_screaming_exit", 0, 1.0, 0, 1, 1, 0);
			isSceneRunning = true;
		}
		//CTextUI(std::to_string(PED::GET_SYNCHRONIZED_SCENE_PHASE(this->m_iSceneId)), { 0.5,0.5 }, { 255,255,255,255 }).Draw();
		/*if (PED::GET_SYNCHRONIZED_SCENE_PHASE(this->m_iSceneId) >= 0.85f) {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
		}*/
	}
}

void CTheScript::SetupEnvironment() {
	if (this->m_bConfigureAmbience) {
		this->ambienceConfig.DoAll(m_fStartTime);
		if (ambienceConfig.isAllConfigured()) {
			scriptLogI("Ambience is all configured");
			this->CurrentLevel = (int)CHECKPOINT::DREAM_SEQUENCE;
			m_bIsAmbienceConfigured = true;
			m_bConfigureAmbience = false;
		}
	}
}

void CTheScript::BoxCheck() {
	if (!this->box.isEntityInside(PLAYER::PLAYER_PED_ID())) {
		if (!m_bIsAmbienceConfigured && m_bConfigureAmbience == false) {
			m_bConfigureAmbience = true;
			m_fStartTime = MISC::GET_GAME_TIMER();
			m_bSetVehicleDensityNow = true;
			SCRIPT_MGR->SetDisablerActive(true); // as part of ambience.
			WORLD->SetBlackoutState(true);
			WORLD->SetBlackoutStateEffectVehicle(false);
			ClearTraffic();
		}
	}
}

void CTheScript::Cheat_CLEARSCRFX() {
	scriptLogI("[CHEAT] called");
	this->ambienceConfig.ClearAll();
	WORLD->ResetTime();
}

void CTheScript::Cheat_GOTODELUXO() {
	scriptLogI("[CHEAT] called");

	STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, 1);
	Ped player = PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 0, 0, 1);
	ENTITY::SET_ENTITY_COORDS(player, 42.8494, -860.811, 30, 1, 0, 0, 0);
	WAIT(100);
	WORLD->GetLocalPlayer()->SetCoordinates({ 42.8494, -860.811, 30 });
	PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), DELUXO, -1);
	STREAMING::SWITCH_TO_MULTI_SECONDPART(player);
}

void CTheScript::ClearTraffic() {
	VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	VEHICLE::SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(0.0);
	PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
	PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0, 0.0);
}

void CTheScript::BlipSetup() {
	Blip_MainObj = HUD::ADD_BLIP_FOR_COORD(-1725.309, -190.1009, -1.0f);
	HUD::SET_BLIP_COLOUR(Blip_MainObj, 1);
	HUD::SET_BLIP_SCALE(Blip_MainObj, 1.5f);
	HUD::SET_BLIP_SPRITE(Blip_MainObj, 274);
	HUD::SET_BLIP_ROUTE(Blip_MainObj, 1);
	HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Your Grave");
	HUD::END_TEXT_COMMAND_SET_BLIP_NAME(Blip_MainObj);
}

void CTheScript::UFOSetup() {
	STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("p_spinning_anus_s"));
	while (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("p_spinning_anus_s"))) {
		WAIT(0);
	}

	if (!ENTITY::IS_AN_ENTITY(OBJ_UFO)) {
		scriptLogI("The UFO is not active creating!");
		OBJ_UFO = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("p_spinning_anus_s"), -1725.449f, -190.3516f, 93.0902f, 1, 0, 1);
		ENTITY::FREEZE_ENTITY_POSITION(OBJ_UFO, 1);
	}
}

void CTheScript::SetupWarp() {
	CVector3<float> pos = WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition;
	
	Scene.SetupScene("anim@scripted@freemode@ufo_invasion@ufo_float@heeled@", pos, { 0, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) });
	Scene.QueueAnimation(PLAYER::PLAYER_PED_ID(), "float");	
	Scene.RunScene();
	GAMEHUD->GetSpinner()->SetType(CGameSpinner::BUSY_SPINNER_RIGHT);
	GAMEHUD->GetSpinner()->SetText("Loading");
	GAMEHUD->GetSpinner()->StartRender();
}

void CTheScript::StartWarp() {
	WarpPed = PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 1, 0, 0);
	ENTITY::SET_ENTITY_COORDS(WarpPed, -2054.274, 3238.3389, -1, 1, 0, 0, 0);
	STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, 1);
	this->m_bsWarp.set(eWarpSet::WARP_HAS_STARTED, 1);
}
//if (PED::GET_SYNCHRONIZED_SCENE_PHASE(m_iSceneId) >= 0.85f) {
//	scriptLogI("Starting wake up scene...");
//	STREAMING::SWITCH_TO_MULTI_FIRSTPART(PLAYER::PLAYER_PED_ID(), 0, 1);
//	Ped p = PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 1, 0, 1);
//	ENTITY::SET_ENTITY_COORDS(p, -1873.391, 3748.26, -99.8408, 1, 0, 0, 0);
//	STREAMING::SWITCH_TO_MULTI_SECONDPART(p);
//	GAMEHUD->GetSpinner()->ForceStopRender();
//	TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
//	//ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 1);
//	while (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
//		if (STREAMING::GET_PLAYER_SWITCH_STATE() == 7) {
//			scriptLogI("We're launching the script here");
//			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
//			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1873.391, 3748.26, -99.8408, 1, 0, 0, 0);
//			this->CurrentLevel = (int)CHECKPOINT::INSIDE_INTERIOR;
//			break;
//		}
//		WAIT(0);
//	}
//	m_bDisplayHelpText = true;
//	this->m_iSceneId = -1;
//}