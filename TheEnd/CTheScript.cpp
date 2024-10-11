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
#include "./MenuAPI/PlayerMenu.h"
/*
	TODO -- Write up a quick class to do vehicles and their modifications. 
	Also cause shop controller is annoying for this we might just have to void the shop controller when we get close and restart it when we are done. Or Leave the area. 
		Cause I don't know how shop controller works or at least how it tracks conflicts with the models so I can't write my own to get around the controller yet. 
	Write up a Deluxo Class as a part of that vehicle class. As we have the CVehicle class. 
	Maybe write up a CTheEndDeluxo that just deals with the respawning and management of the Launcher?
*/
void CTheScript::OneTime() {
	if (this->m_bDoesPlayerMenuNeedSetup) {
		m_PlayerMenu.SetHeader({ PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), "INTERACTION MENU", true });
		m_PlayerMenu.AddMenuItem({ "Escape To Cayo Perico", "", "", [&](CPlayerMenu* player, CPlayerMenu::sMenuItem* headerInfo) {
			m_BitWarpSet.set(TEST_VAL::DOES_NEED_WARP, 1);
			m_BitWarpSet.set(TEST_VAL::WARP_CAYO, 1);
			CurrentLevel = (int)CHECKPOINT::LEAVING_TO_CAYO;
			m_bIsPlayerMenuShowing = false;
			} });
		m_PlayerMenu.AddMenuItem({ "Get Global Water State (DEBUG)", "", "", [&](CPlayerMenu* player, CPlayerMenu::sMenuItem* headerInfo) {
				STREAMING::LOAD_GLOBAL_WATER_FILE(1);
				scriptLogI("Loading Global Water Configuration: %i", STREAMING::GET_GLOBAL_WATER_FILE());
			} });
		this->m_bDoesPlayerMenuNeedSetup = false;
	}
	STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("DELUXO"));
	DELUXO = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), 47.2755f, -862.1296f, 30.05f, 340.8, 1, 0, 1);
	VEHICLE::SET_VEHICLE_MOD_COLOR_1(DELUXO, 4, 0, 0); 
	VEHICLE::SET_VEHICLE_MOD_COLOR_2(DELUXO, 4, 0);
	VEHICLE::SET_SPECIAL_FLIGHT_MODE_ALLOWED(DELUXO, 0);
	VEHICLE::SET_DISABLE_HOVER_MODE_FLIGHT(DELUXO, 0);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(DELUXO, "OUTATIME");
	AUDIO::SET_VEH_RADIO_STATION(DELUXO, "RADIO_OFF");
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
	CheatHelper();
	WarpStateManagement();
	MenuNav();
	if (IsKeyJustUp(VK_F13)) {
		m_bIsPlayerMenuShowing = !m_bIsPlayerMenuShowing;
		scriptLogI("Player Menu Status: %i", m_bIsPlayerMenuShowing);
	}
	if (m_bIsPlayerMenuShowing) {
		m_PlayerMenu.Display();
	}
	this->isPlayerInDeluxo = PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), DELUXO, 0);
	if (this->isPlayerInDeluxo) {
		m_bSetVehicleDensityNow = this->isPlayerInDeluxo;
		BoxCheck();
	}
	if (m_bSetVehicleDensityNow) {
		ClearTraffic();
	}
	SetupEnvironment();
	CVector3<float> pos = WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition;
	if (IsKeyJustUp(VK_DIVIDE)) {
		//SummonArmyAI();
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
			Scene.Destroy();
			this->StartWarp();
		}
	}
	if (isWithinCircle(pos.x, pos.y, -1725.309, -190.1009, 625) && this->m_CurrentScore.GetMood().first == SUSPENSE) { // suspense
		this->m_CurrentScore.ChangeMood(ACTION); // action;
	}
	if (IsKeyJustUp(VK_ADD)) {
		EHUD->GetFade()->DoFadeWhite(MISC::GET_GAME_TIMER());
	}
	if (this->isPlayerAwake && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
		HUD::DISPLAY_RADAR(false); // global mission fx
	} 
	if (this->isPlayerAwake && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) && HUD::IS_RADAR_HIDDEN()) {
		HUD::DISPLAY_RADAR(true);
	}
	if (this->CurrentLevel == (int)CHECKPOINT::INSIDE_INTERIOR) {
		if (!this->isPlayerAwake) {
			MISC::SET_FAKE_WANTED_LEVEL(5);
			
			this->isPlayerAwake = true;
		}
		if (this->Scene.GetSceneProgression() >= 0.76 && this->Scene.GetAnimDictionary() == "switch@michael@wakes_up_screaming") {
			scriptLogI("This part of the mission is not written yet!");
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			Scene.Destroy();
		}
		if (isWithinCircle(pos.x, pos.y, -1873.440, 3742.1902, 1.5f) && !this->m_bDoesHaveWeapon) { // && !this->m_bisWeaponGrabbed
			GAMEHUD->GetHelpText()->SetHelpText("Press ~INPUT_CONTEXT~ to grab weapon.");
			GAMEHUD->GetHelpText()->SetHelpTextCanRender(true);
			GAMEHUD->GetHelpText()->RenderNow();
			if (PAD::IS_CONTROL_JUST_RELEASED(0, 51) && !m_bDoesHaveWeapon) { // control_action / e
				int TaskId = NULL;
				TASK::OPEN_SEQUENCE_TASK(&TaskId);
					TASK::TASK_GO_STRAIGHT_TO_COORD(NULL, -1873.1250f, 3742.7180f, -99.8454, 1.0f, 10000, 147.2582, 0.0f);
					m_bDoesNeedToGetWeapon = true;
				TASK::CLOSE_SEQUENCE_TASK(TaskId);
				TASK::TASK_PERFORM_SEQUENCE(PLAYER::PLAYER_PED_ID(), TaskId);
				TASK::CLEAR_SEQUENCE_TASK(&TaskId);
			}
			if (m_bDoesNeedToGetWeapon) {
				if (WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({ -1873.1250f, 3742.7180f, -99.8454 }) < .01f) {
					Scene.Destroy();
					Scene.SetupScene("anim@scripted@player@freemode@tun_prep_grab_midd_ig3@male@", { -1873.1250f, 3742.7180f, -99.8454 -1.0f }, { 0,0,147.2582f });
					Scene.QueueAnimation(PLAYER::PLAYER_PED_ID(), "tun_prep_grab_midd_ig3");
					Scene.RunScene();
					this->m_bDoesHaveWeapon = true;
					this->m_bDoesNeedToGetWeapon = false;
				}
			}
		}
		if (this->Scene.GetSceneProgression() >= 0.95f) {
			Object weapon = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(-1873.440, 3742.1902, -99.8485, 0.05f, MISC::GET_HASH_KEY("w_pi_appistol"), 1,0,0);
			if (ENTITY::IS_ENTITY_AN_OBJECT(weapon)) {
				OBJECT::DELETE_OBJECT(&weapon); // deleteing from world.
			}
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WEAPON_APPISTOL"), 216, 0, 1);
			TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
			Scene.Destroy();
		}
		if (isPlayerInElevator()) {
			GAMEHUD->GetHelpText()->SetHelpTextCanRender(true);
			GAMEHUD->GetHelpText()->SetHelpText("Press ~INPUT_CONTEXT~ to leave the Silo.");
			GAMEHUD->GetHelpText()->RenderNow();
			if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) { // input context
				GAMEHUD->GetHelpText()->SetHelpTextCanRender(false);
				m_CurrentScore.ChangeMood(ACTION);
				MISC::SET_FAKE_WANTED_LEVEL(0);
				PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 5, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				EHUD->GetFade()->DoFadeWhite(MISC::GET_GAME_TIMER());
			}
			if (EHUD->GetFade()->GetIsHoldingFade()) {
				AI.TriggerAI();
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -2055.498f, 3239.1194f, 31.4989f, 1,0,0,1);
				ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 63.5304f);
				EHUD->GetFade()->DoFadeOutWhite(MISC::GET_GAME_TIMER());
				AI.TriggerAI();
				iFrameStart = MISC::GET_GAME_TIMER();
				this->CurrentLevel = (int)CHECKPOINT::INSIDE_MIL_BASE;
			}
		}
	}
	if (this->CurrentLevel == (int)CHECKPOINT::INSIDE_MIL_BASE) { // this entire segment is easy.
		if (MISC::GET_HASH_KEY(this->GetZoneWherePlayerIs().c_str()) != MISC::GET_HASH_KEY("ARMYB")) {
			HUD::FLASH_WANTED_DISPLAY(1);
			this->m_CurrentScore.ChangeMood(VEHICLE_CHASE);
			this->Blip_MainObj = HUD::ADD_BLIP_FOR_COORD( -1038.108, -2737.415, 20.1693 );
			if (HUD::DOES_BLIP_EXIST(this->Blip_MainObj)) {
				HUD::SET_BLIP_ROUTE(this->Blip_MainObj, true);
				HUD::SET_BLIP_SPRITE(this->Blip_MainObj, 90); // icon plane/flight_school
				HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Airport");
				HUD::END_TEXT_COMMAND_SET_BLIP_NAME(this->Blip_MainObj);
			}
			this->CurrentLevel = (int)CHECKPOINT::DRIVING_TO_LSIA;
		}
	}	
	if (this->CurrentLevel == (int)CHECKPOINT::DRIVING_TO_LSIA) {
		/*
		AP1_02_DOOR_R 
			coords door_r{
			-1044.840,
			-2746.488,
			22.0308
			}
		AP1_02_DOOR_L
			coords door_l{
				-1041.932,
				-2748.167, 
				22.0308
			}
			ped pathfinder target:
			 -1044.812, 
			 -2749.310,
			 21.3634,
			 150
		*/

		static bool hasPedTaskEnabled = false;
		if(MISC::GET_HASH_KEY(GetZoneWherePlayerIs().c_str()) == MISC::GET_HASH_KEY("AIRP") && !this->m_bHasTextMessageBeenSent) {
			SendTextMessage();
			this->m_bHasTextMessageBeenSent = true;
		}

		if (hasPedTaskEnabled) {
			int TaskId = NULL;
			TASK::OPEN_SEQUENCE_TASK(&TaskId);
			TASK::TASK_GO_STRAIGHT_TO_COORD(NULL, -1044.812,
				-2749.310,
				21.3634,
				1, 15000, 150, 0.0f);
			m_bDoesNeedToGetWeapon = true;
			TASK::CLOSE_SEQUENCE_TASK(TaskId);
			TASK::TASK_PERFORM_SEQUENCE(PLAYER::PLAYER_PED_ID(), TaskId);
			TASK::CLEAR_SEQUENCE_TASK(&TaskId);
			this->m_CurrentScore.CancelTrack({ CMusicTrack::sMusicCancel::GLOB_KILL_MUSIC, {0} }); // cancel music when we are running scene. 
			Hash Left = MISC::GET_HASH_KEY("THEEND_DOOR_HASH_LEFT");
			Hash Right = MISC::GET_HASH_KEY("THEEND_DOOR_HASH_RIGHT");
			if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Right)) {
				scriptLogI("Door Registered With Sys Already! Weird?");
				OBJECT::REMOVE_DOOR_FROM_SYSTEM(Right, 0);
			}
			if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Left)) {
				scriptLogI("Door Registered With Sys Already! Weird?");
				OBJECT::REMOVE_DOOR_FROM_SYSTEM(Left, 0);
			}
			if (!OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Left)) { // @ this point we know we're close to the door.
				OBJECT::ADD_DOOR_TO_SYSTEM(Left, 0xDE3A3326, -1041.932, -2748.167, 22.0308, 0, 0, 1);
				scriptLogI("Door is added: LEFT");
			}
			if (!OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Right)) {
				OBJECT::ADD_DOOR_TO_SYSTEM(Right, 0xdf1f34cc, -1044.840, -2746.488, 22.0308, 0, 0, 1);
				scriptLogI("Door is added: RIGHT");
			}
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(Left, 0, 0, 1);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(Right, 0, 0, 1);
			hasPedTaskEnabled = false;
		}
		if (WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({-1038.108, -2737.415, 20.1693}) <= 5.0f && isPadDisabled == false) {
			// Upon entering doors fade to black. open select menu. handle transfer to cayo or transfer to north yankton. handle cayo because its the easiest. then send. 
			scriptLogI("beginning task scene.");
			isPadDisabled = true;
			hasPedTaskEnabled = true;
		}
		if (WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({ -1044.812, -2749.310, 21.3634 }) <= 0.3f) {
			this->m_bIsPlayerMenuShowing = true;
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
		if (isPadDisabled) {
			PAD::DISABLE_CONTROL_ACTION(0, 1, 0); // CAM Horizontal Movement
			PAD::DISABLE_CONTROL_ACTION(0, 2, 0); // CAM vertical movement
		}
	}
	if (this->CurrentLevel == (int)CHECKPOINT::LEAVING_TO_CAYO) {
		if (WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({ 4700.0, -5145.0, 0.0f }) >= 1200.f) {
			scriptLogI("Player isn't Playable Area!!");
		}
	}
	LockFirstPerson();
}

void CTheScript::MenuNav() {
	m_PlayerMenu.SetSelected(m_iPlayerSelection);
	if (IsKeyJustUp(VK_UP)) {
		m_iPlayerSelection--;
		if (m_iPlayerSelection == -1) {
			m_iPlayerSelection = m_PlayerMenu.GetSize();
		}
	} else if (IsKeyJustUp(VK_DOWN)) {
		m_iPlayerSelection++;
		if (m_iPlayerSelection == m_PlayerMenu.GetSize() + 1) {
			m_iPlayerSelection = 0;
		}
	} else if (IsKeyJustUp(VK_RETURN) && m_bIsPlayerMenuShowing) {
		CPlayerMenu::sMenuItem* curItem = m_PlayerMenu.GetItem(m_iPlayerSelection);
		curItem->CallBack(&m_PlayerMenu, curItem);
	}
	if (m_BitWarpSet.test(TEST_VAL::DOES_NEED_WARP)) {
		if (m_BitWarpSet.test(TEST_VAL::WARP_CAYO)) {
			if (WarpPed == 0) {
				WarpPed = PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), 0, 0, 1);
				ENTITY::SET_ENTITY_COORDS(WarpPed, 4493.6641, -4525.817, 4.4124, 1, 0, 0, 1);
			}
			if (!m_bHasSwitchBeenInit) {
				STREAMING::START_PLAYER_SWITCH(PLAYER::PLAYER_PED_ID(), WarpPed, 0, 1);
				STREAMING::LOAD_GLOBAL_WATER_FILE(1);
				m_bHasSwitchBeenInit = true;
			}
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 7) { // transition
				WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_LOAD_CAYO, 1);
			}
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {

				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 4493.6641, -4525.817, 4.4124, 1, 0, 0, 1);

			}
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 10) {
				DLC::ON_ENTER_MP();
				STREAMING::SET_ISLAND_ENABLED("HeistIsland", 1);
				ENTITY::DELETE_ENTITY(&WarpPed);
				m_bHasSwitchBeenInit = false;
				m_BitWarpSet.reset(WARP_CAYO);
				m_BitWarpSet.reset(DOES_NEED_WARP);
			}
		}
	}
}

void CTheScript::TimeCopy(float fLaunch, int targetHours, int targetMinutes, int targetSeconds) {
	auto interp_minutes = CConfigureTheEndAmbience::InterpolateTimeWithDuration(CLOCK::GET_CLOCK_HOURS(), CLOCK::GET_CLOCK_MINUTES(), targetHours, targetMinutes, 10000, fLaunch);
	int clock_hours = static_cast<int>(interp_minutes) / 60;
	int clock_minutes = static_cast<int>(interp_minutes) % 60;
	if (clock_minutes >= 61) {
		clock_hours += 1;
		clock_minutes = 0;
	}
	if (clock_hours >= 25) {
		clock_hours = 0;
	}
	CLOCK::SET_CLOCK_TIME(clock_hours, clock_minutes, 0);
}

void CTheScript::SendTextMessage() {
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("char_default", 1);
	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("char_default")) {
		WAIT(0);
	}
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("I see you've escaped. We should meet however I see you have your hands tied. Enjoy your flight.");
	HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU("char_default", "char_Default", 0, 1, "UNKNOWN", "", 1.0f);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "Text_Arrive_Tone", "Phone_SoundSet_Default", true);
}

std::string CTheScript::GetZoneWherePlayerIs() {
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
	return std::string(ZONE::GET_NAME_OF_ZONE(pos.x, pos.y, pos.z));
}

void CTheScript::WarpStateManagement() {
	if (m_bsWarp.test(WARP_HAS_STARTED)) {
		if (STREAMING::GET_PLAYER_SWITCH_STATE() == 5) {
			STREAMING::SWITCH_TO_MULTI_SECONDPART(WarpPed);
			m_bsWarp.set(WARP_TRANSITIONING, 1);
			ambienceConfig.ClearAll();
			WORLD->SetTimePersist(0, { 0,0,0 });
			this->TimeCopy(MISC::GET_GAME_TIMER(), 12,0,0);
			this->m_bCanMusicPlay = false;
			this->m_CurrentScore.ChangeMood(AIRBORNE);
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
	if (m_bsWarp.test(WARP_ENDING)) {
		this->m_bDisplayHelpText = true;
		WORLD->SetBlackoutState(false);
		WORLD->SetBlackoutStateEffectVehicle(false);
		this->m_bSetVehicleDensityNow = false;
		m_WeaponCapture.Capture();
		Scene.SetupScene("switch@michael@wakes_up_screaming", { -1873.391, 3748.26, -99.8408 }, { 0.0, 0.0, -8.9672 });
		Scene.QueueAnimation(PLAYER::PLAYER_PED_ID(), "001671_02_mics2_1_wakes_up_screaming_exit");
		PED::DELETE_PED(&this->WarpPed);
		Scene.RunScene();
		this->CurrentLevel = (int)CHECKPOINT::INSIDE_INTERIOR;
		HUD::REMOVE_BLIP(&this->Blip_MainObj);
		OBJECT::DELETE_OBJECT(&this->OBJ_UFO);
		UT_2();
		this->m_bLockFirstPerson = true;
		m_bsWarp.reset(WARP_ENDING);
	}
}

void CTheScript::CheatHelper() {
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("CLEARSCRFX"))) {
		this->Cheat_CLEARSCRFX();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("GOTODELUXO"))) {
		this->Cheat_GOTODELUXO();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DEVSTAR_UT1")) || this->CurrentLevel == (int)CHECKPOINT::DREAM_SEQUENCE) {
		m_bRenderUFOEffect = true;
		float fLaunch = MISC::GET_GAME_TIMER();
		WORLD->SetTimePersist(true, { 0,0,0 });
		WORLD->SetBlackoutState(true); // setting the blackout to take effect
		if (!HUD::DOES_BLIP_EXIST(Blip_MainObj)) {
			scriptLogI("Main Obj blip does not exist!");
			BlipSetup();
		}
		this->CurrentLevel = (int)CHECKPOINT::DREAM_SEQUENCE;
		UFOSetup();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DEVSTAR_UT2"))) {
		UT_2();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("TESTANIM"))) {
		SetupWarp();
	}
	if (IsKeyJustUp(VK_MULTIPLY) || MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("STOPSYNC"))) {
		scriptLogI("Cancelling Script Scene");
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("GOTOSILO"))) {
		WORLD->GetLocalPlayer()->SetCoordinates({  -1873.391, 3748.26, -99.3408  });
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("RESET_GLOBALS"))) {
		Cheat_ResetGlobals();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DEVSTAR_UT3"))) {
		UT_3();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DO_TEST_WARP"))) {
		scriptLogI("[CHEAT] DO_TEST_WARP called!");
		StartWarp();
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("FIXMINI"))) {
		scriptLogI("[CHEAT] FIXMINI called!");
		HUD::SET_BIGMAP_ACTIVE(false, false);
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("SUMMONCAR"))) {
		MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
		scriptLogI("[CHEAT] SUMMONCAR called!");
		OneTime();
		CDisableScripts::RestartScript("shop_controller", CDisableScripts::SHOP_CONTROLLER);
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("TESTER_RETURN_TO_LS"))) {
		SCRIPT_MGR->GetScriptDisabler()->RestartAllScripts();
		Cheat_ResetGlobals();
		STREAMING::SET_ISLAND_ENABLED("HeistIsland", false);
		WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_DISABLE_LOS_SANTOS, 0);
		WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_LOAD_CAYO, 0);
		STREAMING::SET_MAPDATACULLBOX_ENABLED("HeistIsland", 0);
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0, 71.f, 1, 0, 0, 1);
	}
	if (MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(MISC::GET_HASH_KEY("DOORTEST"))) {
		scriptLogI("[CHEAT] DoorTest");
		Hash Left = MISC::GET_HASH_KEY("THEEND_DOOR_HASH_LEFT");
		Hash Right = MISC::GET_HASH_KEY("THEEND_DOOR_HASH_RIGHT");
		if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Right)) {
			scriptLogI("Door Registered With Sys Already! Weird?");
			OBJECT::REMOVE_DOOR_FROM_SYSTEM(Right, 0);
		}
		if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Left)) {
			scriptLogI("Door Registered With Sys Already! Weird?");
			OBJECT::REMOVE_DOOR_FROM_SYSTEM(Left, 0);
		}
		if (!OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Left)) { // @ this point we know we're close to the door.
			OBJECT::ADD_DOOR_TO_SYSTEM(Left, 0xDE3A3326, -1041.932, -2748.167, 22.0308, 0, 0, 1);
			scriptLogI("Door is added: LEFT");
		}
		if (!OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(Right)) {
			OBJECT::ADD_DOOR_TO_SYSTEM(Right, 0xdf1f34cc, -1044.840, -2746.488, 22.0308, 0, 0, 1);
			scriptLogI("Door is added: RIGHT");
		}
		OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(Left,		0, 0, 1);
		OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(Right,	0, 0, 1);

	}
}

void CTheScript::SetupEnvironment() {
	if (this->m_bConfigureAmbience) {
		this->ambienceConfig.DoAll(m_fStartTime);
		if (ambienceConfig.isAllConfigured()) {
			scriptLogI("Ambience is all configured");
			this->CurrentLevel = (int)CHECKPOINT::DREAM_SEQUENCE;
			m_bIsAmbienceConfigured = true;
			m_bRenderUFOEffect = true;
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
			m_bRenderUFOEffect = true;
			SCRIPT_MGR->SetDisablerActive(true); // as part of ambience.
			WORLD->SetBlackoutState(true);
			WORLD->SetBlackoutStateEffectVehicle(false);
			ClearTraffic();
		}
		if (!this->m_bIsMusicActive && this->m_bCanMusicPlay) {
			AUDIO::SET_AUDIO_FLAG("ActivateSwitchWheelAudio", false);
			AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", true);
			this->m_CurrentScore.PlayTrack(SUSPENSE); // SUSPENSE
			scriptLogI("[AUD], Setting Track score to: SUSPENSE");
			this->m_bIsMusicActive = true;
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

void CTheScript::Cheat_ChangeScore() {
}

void CTheScript::Cheat_ResetGlobals() {
	scriptLogI("[CHEAT] Activated");
	this->m_bDoesHaveWeapon = false;
	this->m_bDoesNeedToGetWeapon = false;
	this->m_CurrentScore.CancelTrack(CMusicTrack::sMusicCancel{ CMusicTrack::sMusicCancel::GLOB_KILL_MUSIC, {""} });
	this->m_bDisplayHelpText = true;
	this->m_bCanMusicPlay = true;
	this->isPlayerAwake = false;
	HUD::DISPLAY_RADAR(true);
	if (MISC::GET_FAKE_WANTED_LEVEL() > 0) {
		MISC::SET_FAKE_WANTED_LEVEL(0);
	}
	//this->m_bCanEnemiesSpawn = true;
	this->m_bIsAmbienceConfigured = false;
	this->ambienceConfig.ClearAll();
	this->m_bConfigureAmbience = false;
	this->CurrentLevel = -1;
	//this->m_AllPeds.clear();
	this->m_bRenderUFOEffect = false;
	this->m_bIsMusicActive = false;
	//his->m_CurrentEnemyBatch.clear();
	if (HUD::DOES_BLIP_EXIST(this->Blip_MainObj)) {
		HUD::REMOVE_BLIP(&this->Blip_MainObj);
	}
	this->isPlayerInDeluxo = false;
	this->m_bLockFirstPerson = false;
	this->isPadDisabled = false;
	this->m_WeaponCapture.Revert();
	this->m_fStartTime = 0;
	this->m_bsWarp.reset();
	//this->m_bShouldEnemiesSpawn = false;
	WORLD->ResetTime();

}

void CTheScript::UT_2() {
	scriptLogI("Simulating Wake");
	this->CurrentLevel = (int)CHECKPOINT::INSIDE_INTERIOR; // simulation of after the scene == 0.76
	//this->m_bCanEnemiesSpawn = true;
	//this->m_bShouldEnemiesSpawn = true;
	//this->m_iLastSpawnTime = MISC::GET_GAME_TIMER();
	Hash h = MISC::GET_HASH_KEY("v_ilev_garageliftdoor");
	Hash weap = MISC::GET_HASH_KEY("w_pi_appistol");
	STREAMING::REQUEST_MODEL(weap);
	STREAMING::REQUEST_MODEL(h);
	while (!STREAMING::HAS_MODEL_LOADED(h) && !STREAMING::HAS_MODEL_LOADED(weap)) {
		WAIT(0);
	}
	//LEFT
	Object DoorLeft = -1;
	Object DoorRight = -1;
	Object Weapon = -1; // fuck meeee port this to class. 
	if (!OBJECT::DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(-1920.684, 3749.0371, -100.6573, 0.05f, h, 0)) {
		 DoorLeft = OBJECT::CREATE_OBJECT(h, -1920.684, 3749.0371, -100.6573, 1, 0, 0);
	} else {
		DoorLeft = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(-1920.684, 3749.0371, -100.6573, 0.05f, h, 1, 0, 0);
	}
	if (!OBJECT::DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(-1920.684, 3750.5274, -100.6573, 0.05f, h, 0)) {
		DoorRight = OBJECT::CREATE_OBJECT(h, -1920.684, 3750.5274, -100.6573, 1, 0, 0);
	} else {
		DoorRight = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(-1920.684, 3750.5274, -100.6573, 0.05f, h, 1, 0, 0);
	}
	if (DoorLeft == -1 || DoorRight == -2) {
		//FUCK
		scriptLogE("Door's Could not be found or created! This is an oopsies daisies");
		return;
	}
	if (!OBJECT::DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(-1873.440, 3742.1902, -99.8485, 0.05f, weap, 0)) {
		Weapon = OBJECT::CREATE_OBJECT(weap, -1873.440, 3742.1902, -99.8485, 1, 0, 0);
	} else {
		Weapon = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(-1873.440, 3742.1902, -99.8485, 0.05f, weap, 1, 0, 0);
	}
	ENTITY::SET_ENTITY_LOD_DIST(DoorLeft, 0xfff);
	ENTITY::SET_ENTITY_LOD_DIST(DoorRight, 0xfff);
	ENTITY::SET_ENTITY_LOD_DIST(Weapon, 0xfff);
	ENTITY::SET_ENTITY_ROTATION(Weapon, 90.0f, -29.4642f, 0.0f, 2, 1);
	ENTITY::SET_ENTITY_HEADING(DoorLeft, 90);
	ENTITY::SET_ENTITY_HEADING(DoorRight, -90);
	OBJECT::ADD_DOOR_TO_SYSTEM(MISC::GET_HASH_KEY("THEEND_DOOR_LEFT"), h, -1920.684, 3749.0371, -100.6573, 0, 1, 1);
	OBJECT::ADD_DOOR_TO_SYSTEM(MISC::GET_HASH_KEY("THEEND_DOOR_RIGHT"), h, -1920.684, 3750.5293, -100.6573, 0, 1, 1);
	OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(MISC::GET_HASH_KEY("THEEND_DOOR_LEFT"), 2.5f, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(MISC::GET_HASH_KEY("THEEND_DOOR_RIGHT"), 2.5f, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(MISC::GET_HASH_KEY("THEEND_DOOR_LEFT"), 30.f, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(MISC::GET_HASH_KEY("THEEND_DOOR_RIGHT"), 30.f, 0, 1);
	OBJECT::ADD_DOOR_TO_SYSTEM(MISC::GET_HASH_KEY("THEEND_DOOR_1"), MISC::GET_HASH_KEY("m23_1_prop_iaa_base_door_02"), -1884.492, 3753.2317, -99.4962, 0, 0, 1);
	OBJECT::ADD_DOOR_TO_SYSTEM(MISC::GET_HASH_KEY("THEEND_DOOR_2"), MISC::GET_HASH_KEY("m23_1_prop_iaa_base_door_02"), -1893.762, 3746.8252, -99.4962, 0, 0, 1);
	OBJECT::ADD_DOOR_TO_SYSTEM(MISC::GET_HASH_KEY("THEEND_DOOR_3"), MISC::GET_HASH_KEY("m23_1_prop_iaa_base_door_02"), -1901.874, 3753.2317, -99.4962, 0, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_1"), 1, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_2"), 1, 0, 1);
	OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_3"), 1, 0, 1);
	this->CurrentLevel = (int)CHECKPOINT::INSIDE_INTERIOR;
}

void CTheScript::UT_3() {
	scriptLogI("[CHEAT] Triggered");
	this->CurrentLevel = (int)CHECKPOINT::INSIDE_MIL_BASE;
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
		ENTITY::SET_ENTITY_LOD_DIST(OBJ_UFO, 0xFFFF);
		ENTITY::FREEZE_ENTITY_POSITION(OBJ_UFO, 1);
	}
}

void CTheScript::SetupWarp() {
	CVector3<float> pos = WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition;
	Scene.Destroy();
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
void CTheScript::LockFirstPerson() {
	if (this->m_bLockFirstPerson) {
		CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(4);
		CAM::SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(4);
	}
}
bool CTheScript::isPlayerInElevator() {
	return (WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({-1922.2150f, 3749.8501f, -100.6458f}) < 2.0f);
}
