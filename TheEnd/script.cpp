#include "script.h"
#include "keyboard.h"

#include <string>
#include <ctime>
#include "MarkerLauncher/VisualMarker.h"
#include "ScaleformHelper/CScaleform.h"
#include "UIEditor/TextDraw/Text.h"
#include "PauseMenuItems/Generic/MenuPaginator.h"
#include "PauseMenuItems/Generic/PauseMenuHeader.h"
#include "PauseMenuItems/Generic/MenuPage.h"
#include "./EnableMP/Cars.h"
#include <bitset>
#include "./Ambience/CConfigureTheEndAmbience.h"
#include "./Scripts/CDisable.h"
#pragma warning(disable : 4244 4305) // double <-> float conversions
#include "./Logger/CLoggerInstances.h"


//This does NOT work. Depricated and completely fucking invalid I mean jfc. Logic found in Shop_Controller.sc which CAN be reset through loading a save file.
void GameVersionCheck();
std::string ClockToDay(int day);
void main() {
    CDisableScripts disableScripts = CDisableScripts();
    CVector3 v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
    bool isOnlineReq = false;
    bool isHalloweenInteriorActive = false;
    bool forceFirstPerson = true;
    int pageinator_selection = 0;
    int page_selection = 0;
    int page_focused = 0;
    bool pageinator_focused = true;
    bool m_bCanShowPause = false;
    bool isMissionStarted = false;
    CPauseMenuPage* lastPageSelected = nullptr;
    bool isPedSpawned = false;
    Ped p = -1;
    Vehicle Deluxo = -1;
    bool m_bConfigureAmbience = false;
    float m_fStartTime = 0.0f; 
    int clock_minutes = 0;
    int clock_hours = 0;
    STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("DELUXO"));
    Deluxo = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), 47.2755f, -862.1296f, 30.05f, 340.8, 1,0,1);
    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Deluxo, 1, 1);
    double value3 = 0.0;
    bool isAmbienceConfiged = false;
#ifdef DESTROY_FM // The Purpose of this is to stop the Dev from accidentally destroying freemode lol All of these scripts effectively manage most of freemode Terminating them results in almost dead freemode environment
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_A");  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_B");  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_C");  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_D");  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_repeat_controller"); // Entire Repeat Menu results in undefined behavior 

    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("blip_controller");          // All Mission Blips go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");          // All shops and shit go through this one ( this also disable's the vehicle lockout stuff ) 
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("vehicle_gen_controller");   // All pv's go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("wardrobe_sp");              // All wardrobe utilities go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cheat_controller");          // All cheats go through this script
    MISC::SET_MISSION_FLAG(1);
#endif // DESTROY_FM
    std::bitset<8> bitStatus_SHOP_CONTRLLER;
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller"            );
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("blip_controller"            );          // All Mission Blips go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("vehicle_gen_controller"     );   // All pv's go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("launcher_Racing"            );   // All races go through this script
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_A"        );  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_B"        );  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_C"        );  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_triggerer_D"        );  // Notsure
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mission_repeat_controller"  ); // Entire Repeat Menu results in undefined behavior 
    Hash left = MISC::GET_HASH_KEY("DOOR_LEFT_SILO_BASE");
    Hash right = MISC::GET_HASH_KEY("DOOR_RIGHT_SILO_BASE");
    OBJECT::ADD_DOOR_TO_SYSTEM(left, MISC::GET_HASH_KEY("v_ilev_garageliftdoor"), -1920.684, 3749.0371, -100.65, 1, 1, 1);
    OBJECT::ADD_DOOR_TO_SYSTEM(right, MISC::GET_HASH_KEY("v_ilev_garageliftdoor"), -1920.690, 3750.5276, -100.65, 1, 1, 1);
    if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(left)) {
        OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(left, 4.0f, 0, 1);
        OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(left, 10.f, 0, 1);
        OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(left, 3, 0, 1);
    }
    if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(right)) {
        OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(right, 4.0f, 0, 1);
        OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(right, 10.f, 0, 1);
        OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(right, 3, 0, 1);
    }
    CConfigureTheEndAmbience ambienceConfigurer = CConfigureTheEndAmbience();
    disableScripts.PushBackScript("shop_controller");
    disableScripts.PushBackScript("blip_controller");
    disableScripts.PushBackScript("vehicle_gen_controller");
    disableScripts.PushBackScript("launcher_Racing");
    disableScripts.PushBackScript("mission_triggerer_A");
    disableScripts.PushBackScript("mission_triggerer_B");
    disableScripts.PushBackScript("mission_triggerer_C");
    disableScripts.PushBackScript("mission_triggerer_D");
    disableScripts.PushBackScript("mission_repeat_controller");
    disableScripts.Update();
    CClientNetwork* logger = CLogger::GetInst()->GetNetworkLogger();
    logger->LogInfo(INFO, true, "We have summoned the script");
    logger->LogInfo(INFO, true, disableScripts.GetLogStatement());
    while (true){
        CTextUI(std::to_string(ambienceConfigurer.GetInterpProgress(ambienceConfigurer.TIMECYCLE)), { 0.5f,0.55f }, { 255,255,255,255 }).Draw();
        CTextUI(std::to_string(ambienceConfigurer.GetInterpProgress(ambienceConfigurer.WEATHER)), {0.5f,0.575f}, {255,255,255,255}).Draw();
        bool isPedInsideDeluxo = (PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), Deluxo, 0));
        if (IsKeyJustUp(VK_DIVIDE)) {
            bitStatus_SHOP_CONTRLLER.set(0, 1);
        }
        if (bitStatus_SHOP_CONTRLLER.test(0)) {
            const char* SCRIPT_NAME = "blip_controller";
            const int   SCRIPT_STACK_SIZE = 1024;
            static int iAttempts = 0;
            CLogger::GetInst()->GetNetworkLogger()->LogInfo(INFO, true, "Attempting Launch of Script: ", SCRIPT_NAME, " With stack size of: ", SCRIPT_STACK_SIZE);
            SCRIPT::REQUEST_SCRIPT(SCRIPT_NAME);
            bitStatus_SHOP_CONTRLLER.set(1, 1);
            while (!SCRIPT::HAS_SCRIPT_LOADED(SCRIPT_NAME)) {
                CLogger::GetInst()->GetNetworkLogger()->LogInfo(INFO, true, "Script Attempting Load Attempt: ", iAttempts);
                SCRIPT::REQUEST_SCRIPT(SCRIPT_NAME);
                if (iAttempts >= 10) {
                    CLogger::GetInst()->GetNetworkLogger()->LogInfo(ERROR2, true, SCRIPT_NAME,": Failed Launch! Attempt Count: ", iAttempts);
                    break;
                }
                iAttempts++;
                WAIT(0);
            }
            bitStatus_SHOP_CONTRLLER.set(1, 0); // clear bit is loading
            CLogger::GetInst()->GetNetworkLogger()->LogInfo(INFO, true, SCRIPT_NAME, ": Has successfully loaded!");
            SYSTEM::START_NEW_SCRIPT(SCRIPT_NAME, 62500);
            SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(SCRIPT_NAME);
            
            bitStatus_SHOP_CONTRLLER.set(2,1); // success bit
            bitStatus_SHOP_CONTRLLER.reset(0); // bit clear the activation bit.
        }
        if (IsKeyJustUp(VK_MULTIPLY)) {
            bitStatus_SHOP_CONTRLLER.set(3);
        }
        if (bitStatus_SHOP_CONTRLLER.test(3)) {
            MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("MrsPhilips2");
            bitStatus_SHOP_CONTRLLER.reset(3);
        }
        if ((isPedInsideDeluxo == true)) {
            if (!isAmbienceConfiged && m_bConfigureAmbience == false) { // reconfigure these bools to go into one std::bitset<sizeof(char) * 8>
                m_bConfigureAmbience = true;
                m_fStartTime = MISC::GET_GAME_TIMER();
                isPedSpawned = true;
            } 
        }
        if (m_bConfigureAmbience) {
            ambienceConfigurer.DoAll(m_fStartTime);
            if (ambienceConfigurer.isAllConfigured()) {
                isAmbienceConfiged = true;
                m_bConfigureAmbience = false;
            }
        }
        if (ENTITY::GET_ENTITY_HEALTH(Deluxo) <= 0) {
            WAIT(5000);
            Deluxo = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), 47.2755f, -862.1296f, 30.05f, 340.8, 1, 0, 1);
        }

        GameVersionCheck();
        VEHICLE::SET_DISABLE_HOVER_MODE_FLIGHT(Deluxo, 1);
        VEHICLE::SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(Deluxo, 1);
        VEHICLE::SET_SPECIAL_FLIGHT_MODE_ALLOWED(Deluxo, 0);
        if (IsKeyJustUp(VK_F3)) {
            if (isPedSpawned) {
                m_bConfigureAmbience = false;
                isAmbienceConfiged = false;
                ambienceConfigurer.ClearAll();
                ambienceConfigurer.ClearBits();
                isPedSpawned = false;
            } else {
                m_fStartTime = MISC::GET_GAME_TIMER();
                isPedSpawned = true;
                m_bConfigureAmbience = true;
            }
        }
        CTextUI("CLOCK: " + std::to_string(clock_hours) + ":" + std::to_string(clock_minutes) + " VAL" + std::to_string(value3/60), {0.5,0.5}, {255,255,255,255}).Draw();

        
        if (isPedSpawned) {
            VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
            VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
            VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
            VEHICLE::SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(0.0);
            PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0);
            PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0, 0.0);
        }

        //if (IsKeyJustUp(VK_F3)) {
        //    isPedSpawned = true;
        //    p = PED::CREATE_PED(0, MISC::GET_HASH_KEY("player_zero"), (GRAPHICS::GET_SAFE_ZONE_SIZE() * 117.2), (GRAPHICS::GET_SAFE_ZONE_SIZE() * -53.3), -113.f, 0,1,1);
        //}
        //if (IsKeyJustUp(VK_F3) && isPedSpawned == true) {
        //    PED::DELETE_PED(&p);
        //    isPedSpawned = false;
        //}
        if (forceFirstPerson) {
            CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(4);
            PAD::DISABLE_CONTROL_ACTION(0, 0,false);
        }
        if (IsKeyJustUp(VK_F13)) {
            forceFirstPerson = !forceFirstPerson;
        }
        if (isOnlineReq == false) {
            DLC::ON_ENTER_MP();
            isOnlineReq = true;
        }
        if (!STREAMING::IS_IPL_ACTIVE("m23_1_dlc_int_03_m23_1")) {
            STREAMING::REQUEST_IPL("m23_1_dlc_int_03_m23_1");
            isHalloweenInteriorActive = true;
        }
        if (IsKeyJustUp(VK_DIVIDE)) {
            ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1876.62134, 3750, -100, 1,0,0,0); // interior stuff
        }
        
        GRAPHICS::DRAW_MARKER(eMarkerType::MarkerTypeVerticalCylinder, -1922.155, 3749.79902, -100.75f, 0, 0, 0, 0, 0, 0, 2.25f, 2.25f, 0.6f, 240, 200, 80, 255, 0,0,0,0,nullptr, "", 0); // v_ilev_garageliftdoor -1920.684

        /*
        Door Positions LEFT:
        {
            X: -1920.684,
            Y: 3749.0371,
            Z:-100.6573,
            PITCH: 0.0,
            ROLL: 0.0,
            YAW: 90.0f
        }
        RIGHT 
        {
            X: -1920.684,
            Y: 3749.7847,
            Z:-100.6573,
            PITCH: 0.0,
            ROLL: 0.0,
            YAW: -90.0f
        }
        animdata:
        {
            animDict: "switch@michael@wakes_up_screaming
            animName: "001671_02_mics_1_wakes_up_screaming_exit"
            animFacialData: "001671_02_mics2_1_wakes_up_screaming_exit_facial
            position {
                x: -1873.391,
                y: 3748.2637,
                z: -99.8408
            }
            rotation {
                pitch: 0.0,
                Roll -0.0,
                Yaw: -8.9672
            }
            flags{
                AF_DO_ONCE,
                AF_SMOOTH_EXIT
            }
            developerNotes{
                Flags are falsified for obvious purposes. In total we're exiting to kinda black.
                As soon as wake animation is done we should immediately start playing the warning alarm sound
                Place Camera Above Door in main wakeup room
            }
        }
        objectdata{
            pickups{
                model:w_pi_appistol
                weapon:AP_PISTOL
                position{
                    x:-1873.440,
                    y:3742.1902,
                    z:-99.9485
                }
                rotation{
                    pitch: 90.0f,
                    roll: -29.4642,
                    yaw: 0.0f,
                }
            }
        }
        Post Wakeup Plans: (Inside Silo) 
            add collectibles inside other rooms with key card that will drop from the bodies of one of the npcs that spawn inside facility. to encourage exploration of the interior.
            summon guards every 30s-2m that the player is inside of the interior ( it has to be like normalized but has to be pressureful as if you are under the military base.
            however to counteract this if the player locks the elevator ( from within the main room ) then the guards will stop coming and will wait outside the facility.
            as well the keycard for the rooms will be on one of the first guards that are actively inside the interior. this prevents the player from waiting inside the thing for the guard with the proper keycard to spawn.
            Player must collect weapon.
            Player skills:
                Stamina: 0 pts
                Weapon Stat: 10 pts
                Vehicle Stat: 30 pts
                Flight Stat: 0 pts
                Lung Compacity: 20 pts
                Stealth: 5 pts
                Special: 0 pts. (Won't matter anyways because the special abilities will be disabled)
            Map will be disabled while inside the interior.
        Outside Silo:
            Guards will have accrewed outside the door. Waiting with weapons drawn.
            Tanks will not spawn ( if I instead decide I want to launch from freemode like how a normal job is i might make normal, hard mode settings and hard will summon tanks that are out with the player while they are leaving mil base. ) 
            Certain Hud Elements WILL be broken Bare minimum include :
                Ammo Counter,
                Map,
                Health,
                Armor,
                Pause Elements (however these won't appear unless player presses to pause the game.) 
                The Feed,
                Wanted Level
        Player Outside Military Base: (Not in LS Yet.) 
            Phone will make an appearence ( we can make some bs excuse for it existing like its a guards phone or something if we want or we swiped it off the table while we were in the interior
            Phone will have no signal.
        Player In LS: 
            Phone will regain connection to network (Mobile Bars)
            As Soon as Player regained mobile bars the text message about this will come:
            NOTIFICATION{
                CONTACT_TEXTURE: IFRUIT
                CONTACT_NAME: IFruit Welcome Services
                MESSAGE: Welcome to your new IFruit phone! We're excited to see you have entered the future! Stop running that Facade garbage!
                NOTIFICATION_TYPE: MESSAGE
            } This will end on the notification at "Stop Running".
            Spam Player with Text Messages from old contacts (Mom, Dad, Sister, Brother)
            After Spam is Done Emails with fake promotional shit ( spam mail for 10 years type thing)
            After that is done as the player is nearing LSIA Phone will recieve a notification{
                CONTACT_TEXTURE: Unknown
                CONTACT_NAME: Unknown
                MESSAGE_CONTENT: I see you've escaped that place. There are many others like you, but you it looks like you have your hands full. We shall meet at another time perhaps.
                NOTIFICATION_TYPE: MESSAGE
            }
            
            Player Escape: ** Work on this section a bit we have to spice it up ** ** It doesn't make sense for an armed felon who just escaped a government test project to just leave on the first flight out of Los Santos. **
                Two Options will be given: 
                    Escape To North Yankton,
                    Escape to Cayo Perico

                Escaping to Cayo Perico will be easily facilitated.
                Escaping to North Yankton will be also easily facilitated.
            Player Stays 
                Player should be given the option to stay however under extremely limited conditions.
                Player if decided to stay will message back the Unknown contact.
                Player once done that their mission objects will change.
                Player will be taken to an warehouse that will lead underground to a likely defunct silo or some sort of dead interior.
                Player can run resupply based missions from this to help the resistance.
                Player can also acquire illegitimate licences, weapon permits etc that allow the player to buy weapons and slowly but surely regain themselves within society.
                **Also After both endings the Player can cancel the mission this will save their data and revert them back to the Grand Theft Auto SinglePlayer**
                Player however will never be able to use the resistance to break other members out of the base. This is because logically the player will have never reached the required popularity among the base to stage a full scale invasion of Fort Zancudo.
                If player is arrested in this state there will be two subjects of contact{
                    Has Licence:
                        Player is given a minor fine and is let go.
                    Does not have Licence:
                        Player will be dragged to the police station.
                        Player will be prosecuted and likely found out as the person with this experimental government program.
                        Player will be subjected to questioning and will be exciled from the resistance under pretenses of being a "snitch"
                        Player then must escape from police station and leave city as they are against resistance and government watch.
                If Player Dies. They have lost their progress and must restart from scratch inside the military base. Or they can leave the mission.
                This gives the pressure of the situation of being both an outsider from civilization and under constant threat of dying and losing all generated progress from licence.
                We can add Gang Wars too however in general this is getting a bit to LONG winded for the project.
                Player can never go back to the military base again and instance of them being inside of the military base will not go unnoticed infact player with either die, get tranc'd, or simply if near gates will display a message and gates will be forced closed and fences will be erected.
                    Help text might state: The military base is under ongoing investigation for an escaped member of a test project. As such this base is on mandatory operation mode until later notice.

                }



        */

        if (v.Dist(CVector3{ -1921.955, 3749.7202, -99 }) < 1.76) {
            CTextUI("You are inside area", {0.5, 0.2}, { 255,255,255,255 }).Draw();
            if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
                CAM::DO_SCREEN_FADE_OUT(100);
                WAIT(150);
                ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -2056.26, 3239.9, 30.8,1,0,0,0);
                ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 60);
                WAIT(400);
                CAM::DO_SCREEN_FADE_IN(150);
            }
        }
        v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
        CMarkerInfo markerInfo = CMarkerInfo("Mission", "The End", "", "100%", "", false, "1", "", "", "");
        CMissionMarker marker = CMissionMarker({v.x, v.y, v.z + 2.f}, { 5.f,5.f,1.f }, CRGBA(255, 255, 255, 255), CTxd("mpmissmarkers256", "custom_icon")); // please kys!
        CVisMarker vismarker = CVisMarker(markerInfo, marker);
        CVector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);


#pragma region PauseMenuInit
        CPauseMenuPaginator pageinator = CPauseMenuPaginator();
        pageinator.SetSelection(pageinator_selection);
        pageinator.SetPaginatorFocus(pageinator_focused); // forces the focus on the user's side now.
        //vismarker.DrawAll({0,0,-v.z}, {4,4,1});
        CPauseMenuPage OnlinePage = CPauseMenuPage();
        CPauseMenuHeader::PauseInfo onlineInfo = CPauseMenuHeader::PauseInfo("Header", "False", "true", "false", "true");
        CPauseMenuHeader onlineHeader = CPauseMenuHeader(&onlineInfo);
        CTextUI(std::to_string((unsigned long long) & onlineHeader), { 0.1,0.125 }, { 255,255,255,255 }).Draw();
        OnlinePage.Init(&pageinator, &onlineHeader);
        OnlinePage.AddEntry(0, { "Join Friends","" });
        OnlinePage.AddEntry(1, { "Join Crew Members","" });
        OnlinePage.AddEntry(2, { "Crews","" });
        OnlinePage.AddEntry(3, { "Creator","" });
        OnlinePage.AddEntry(4, { "Choose Character","" });
        OnlinePage.AddEntry(5, { "Play GTA Online","\n\nCut to the chase and head straight into the world of GTA Online" });
        OnlinePage.SetHighlightColor({ 171, 237, 171, 255 });
        OnlinePage.SetPageHeader(&onlineHeader);
        CPauseMenuPage page = CPauseMenuPage();
        CPauseMenuHeader::PauseInfo headerInfo = CPauseMenuHeader::PauseInfo("Grand Theft Auto Online", "", "{date}", "{character}", "{money}");
        CPauseMenuHeader hlol = CPauseMenuHeader(&headerInfo);

        page.Init(&pageinator, &hlol);
        page.AddEntry(0, { "Quick Join",""});
        page.AddEntry(1, { "Join Friends","" });
        page.AddEntry(2, { "Join Crew Member","" });
        page.AddEntry(3, { "Playlists", "" });
        page.AddEntry(4,{ "Players", "" });
        page.AddEntry(5,{ "Crews", "" });
        page.AddEntry(6,{ "Rockstar Creator", "" });
        page.AddEntry(7,{ "Manage Characters", "" });
        page.AddEntry(8,{ "Migrate Profile", "" });
        page.AddEntry(9,{ "GTA+ Membership", "" });
        page.AddEntry(10,{ "Purchase Shark Cards", "" });
        page.AddEntry(11,{ "Options", "" });
        page.AddEntry(12,{ "Find New Session", "" });
        page.AddEntry(13,{ "Credits & Legal", "" });
        page.AddEntry(14,{ "Quit To Story Mode", "" });
        page.AddEntry(15,{ "Quit To Main Menu", "" });
        //page.AddEntry(0, { "{menu_option_online0: \"QUICK_JOIN\"}","" });
        //page.AddEntry(1, { "{menu_option_online1: \"JOIN_FRIEND\"}","" });
        //page.AddEntry(2, { "{menu_option_online2: \"JOIN_CREWMBR\"}","" });
        //page.AddEntry(3, { "{menu_option_online3: \"PLAYLIST\"}", "" });
        //page.AddEntry(4, { "{menu_option_online4: \"PLAYERS\"}", "" });
        //page.AddEntry(5, { "{menu_option_online5: \"CREWS\"}", "" });
        //page.AddEntry(6, { "{menu_option_online6: \"CREATOR\"}", "" });
        //page.AddEntry(7, { "{menu_option_online7: \"MNG_CHAR\"}", "" });
        //page.AddEntry(8, { "{menu_option_online8: \"MIG_PROF\"}", "" });
        //page.AddEntry(9, { "{menu_option_online9: \"GTA+_PROMO\"}", "" });
        //page.AddEntry(10, { "{menu_option_online10: \"BUY_SHK_CRD\"}", "" });
        //page.AddEntry(11, { "{menu_option_online11: \"SETTINGS\"}", "" });
        //page.AddEntry(12, { "{menu_option_online12: \"NEW_SESSION\"}", "" });
        //page.AddEntry(13, { "{menu_option_online13: \"CRED+LEGAL\"}", "" });
        //page.AddEntry(14, { "{menu_option_online14: \"QUIT_STORY\"}", "" });
        //page.AddEntry(15, { "{menu_option_online15: \"QUIT_MAIN\"}", "" });
        pageinator.RegisterPage("MAP", page);
        pageinator.RegisterPage("BRIEF", OnlinePage);
        pageinator.RegisterPage("STATS", OnlinePage);
        pageinator.RegisterPage("SETTINGS", OnlinePage);
        pageinator.RegisterPage("GAME", OnlinePage);
        pageinator.RegisterPage("ONLINE", OnlinePage);
        //CPauseMenuHeader header = CPauseMenuHeader(CPauseMenuHeader::PauseInfo("GrAnd Th3Ft Au0x2 0nIine ?RageParserSchema::NextXMLElement()?0x0fff02bba", "", "T??? ??:??", "UNK_001", "$-ab0x0244f"));
        CPauseMenuPage* currentPage = pageinator.GetPageFromIndex(pageinator_selection);
        currentPage->SetSelectionIndex(page_selection);
        if (IsKeyJustUp(VK_F15) ){
            m_bCanShowPause = true;
        }
        if (m_bCanShowPause) {
            if (pageinator_focused == false) {
                if (currentPage == nullptr) {
                    int gameTime = MISC::GET_GAME_TIMER();
                    while (gameTime + 5000 > MISC::GET_GAME_TIMER()) {
                        CTextUI("currentPage passed is nullptr", { 0.5,0.5 }, { 255,0,0,255 }).Draw();
                        WAIT(0);
                    }
                    return;
                }
                currentPage->SetFocus();
                page_focused = true;
            }
            if (pageinator.GetIfPaginatorHasFocus()) {
                if (IsKeyJustUp(VK_RIGHT)) {
                    pageinator_selection = (pageinator.GetSelection() + 1 < pageinator.GetMaxSelections() ? pageinator.GetSelection() + 1 : 0);
                }
                if (IsKeyJustUp(VK_LEFT)) {
                    pageinator_selection = (pageinator.GetSelection() - 1 >= 0 ? pageinator.GetSelection() - 1 : pageinator.GetMaxSelections() - 1);
                }
                if (IsKeyJustUp(VK_RETURN)) {
                    page_selection = 0;
                    page_focused = 0;
                    pageinator_focused = false;
                }
                if (IsKeyJustUp(VK_BACK)) {
                    pageinator_focused = false;
                    page_selection = 0;
                    page_focused = 0;
                    m_bCanShowPause = false;
                }
            }
            if (!pageinator.GetIfPaginatorHasFocus()) {
                if (IsKeyJustUp(VK_BACK)) {
                    page_focused = false;
                    page_selection = -1;
                    currentPage->LoseFocus();
                    pageinator_focused = true;
                }
                if (IsKeyJustUp(VK_DOWN)) {
                    if (page_selection == currentPage->getAllEntries().size() - 1) {
                        page_selection = -1;
                    }
                    page_selection++;
                }
                if (IsKeyJustUp(VK_UP)) {
                    if (page_selection == -2) {
                        page_selection = currentPage->getAllEntries().size() - 1;
                    }
                    page_selection--;
                }
                if (IsKeyJustUp(VK_RETURN)) {
                    //Call the function with the arguments of currentPage;
                    int gameTimer = MISC::GET_GAME_TIMER();
                    while (gameTimer + 2500 > MISC::GET_GAME_TIMER()) {
                        CTextUI text = CTextUI("VK_RETURN Pressed", { 0.5,0.5 }, { 255,255,255,255 });
                        text.size = 1;
                        text.dropShadow = CTextDropshadow(0, { 0,0,0,0 });
                        text.SetTextJustification(0);
                        text.Draw();
                        if (IsKeyJustUp(VK_BACK)) {
                            break;
                        }
                        WAIT(0);
                    }
                }
            }
            
            pageinator.Update(lastPageSelected);
            
        }
#pragma endregion
        //CPauseMenuPaginator::DrawPage(page);
        if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("pedmugshot_01")) {
            //CPauseMenuHeader h = CPauseMenuHeader(CPauseMenuHeader::PauseInfo("The End", "[Error]: Disconnection detected; Breach breach breach!", std::string(ClockToDay(CLOCK::GET_CLOCK_DAY_OF_WEEK()) + " " + std::to_string(CLOCK::GET_CLOCK_HOURS()) + (CLOCK::GET_CLOCK_MINUTES() <= 9 ? ":0" : ":") + std::to_string(CLOCK::GET_CLOCK_MINUTES())).c_str(), "FRANKLIN", "$2,147,365,094"));
            //CPauseMenuHeader::DrawHeader(h);
        } else {
            GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("pedmugshot_01", 1);
        }
        //vCorona.Draw();eeee
        WAIT(0);
    }
    
    return;
}
void LoggerFunc() {
    CClientNetwork* logger = CLogger::GetInst()->GetNetworkLogger();
    logger->StartWSA();
    logger->StartConnectionProcess();
    logger->ConnectionProcess();
    while (true) {
        

        WAIT(0);
    }
    
}
void ScriptMain()
{
    srand(GetTickCount());
    main();
}
void LoggerThread() {
    srand(GetTickCount());
    LoggerFunc();
}
std::string ClockToDay(int day) {
    switch (day) {
    case 0:
        return "SUNDAY";
    case 1:
        return "MONDAY";
    case 2:
        return "TUESDAY";
    case 3:
        return "WEDNESDAY";
    case 4:
        return "THURSDAY";
    case 5:
        return "FRIDAY";
    case 6:
        return "SATURDAY";

    }
}
void GameVersionCheck() { // call on tick
    eGameVersion version = getGameVersion();
    if (version < 20) {
        *getGlobalPtr(2558120) = 1;
    }

    if ((version < 22 && version > 19)) {
        *getGlobalPtr(2562051) = 1;
    }


    if (version < 26 && version > 21) {
        *getGlobalPtr(2566708) = 1;
    }

    if ((version > 25) && (version < 28)) {
        *getGlobalPtr(2576573) = 1;
    }

    if ((version > 27) && (version < 30)) {
        *getGlobalPtr(2593910) = 1;
    }


    if ((version > 29) && (version < 34)) {
        *getGlobalPtr(2593970) = 1;
    }


    if ((version > 33) && (version < 36)) {
        *getGlobalPtr(2599337) = 1;
    }

    if ((version > 35) && (version < 38)) {
        *getGlobalPtr(2606794) = 1;

    }

    if ((version > 37) && (version < 42)) {
        *getGlobalPtr(4265719) = 1;
    }

    if ((version > 41) && (version < 46)) {
        *getGlobalPtr(4266042) = 1;
    }

    if ((version > 45) && (version < 48)) {
        *getGlobalPtr(4266905) = 1;
    }
}
/* Legacy code for TimeCycle taken out and put in CConfigureTheEndAmbience.h
float easeInOutQuad(float t) {
    if (t < 0.5f) {
        return 2 * t * t;
    } else {
        return -1 + (4 - 2 * t) * t;
    }
}
double easeInOutCubic(double x) {
    if (x < 0.5) {
        return 4 * x * x * x;
    } else {
        return 1 - std::pow(-2 * x + 2, 3) / 2;
    }
}
float easeInOutSine(float f) {
    return -(cos(3.14159 * f) - 1) / 2;
}
double interpolate(double startValue, double endValue, double startTime, double duration, double currentTime) {
    double progress = (currentTime - startTime) / duration;
    if (progress > 1.0) {
        progress = 1.0; // Clamp progress to 1.0 at the end
    }
    return startValue + (endValue - startValue) * easeInOutCubic(progress);
}
int minutesToTarget(int currentHour, int currentMinute, int targetHour, int targetMinute) {
    // Convert current and target times to total minutes
    int currentTotalMinutes = currentHour * 60 + currentMinute;
    int targetTotalMinutes = targetHour * 60 + targetMinute;

    // Calculate the difference in minutes
    int minutes = targetTotalMinutes - currentTotalMinutes;

    // Handle negative result (if target time is in the past for today)
    if (minutes < 0) {
        minutes += 24 * 60; // Add 24 hours in minutes
    }

    return minutes;
}
float lerp(float start, float end, float t) {
    return start + t * (end - start);
}
float interpolateTime(int startHour, int startMinute, int endHour, int endMinute, float t) {
    int startTotalMinutes = startHour * 60 + startMinute;
    int endTotalMinutes = endHour * 60 + endMinute;

    if (endTotalMinutes < startTotalMinutes) {
        endTotalMinutes += 24 * 60;
    }

    float interpolatedMinutes = lerp(startTotalMinutes, endTotalMinutes, t*t);
    return interpolatedMinutes;
}
float easeInQuad(float t) {
    return t * t;
}
int timeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}
float interpolateTimeWithDuration(int startHour, int startMinute, int targetHour, int targetMinute, float durationMs, long long startTimeMs) {
    int startTotalMinutes = timeToMinutes(startHour, startMinute);
    int targetTotalMinutes = timeToMinutes(targetHour, targetMinute);

    // If the target time is earlier in the day than the start time, adjust for wrap-around
    if (targetTotalMinutes < startTotalMinutes) {
        targetTotalMinutes += 24 * 60; // Add 24 hours worth of minutes
    }

    // Get the current time in milliseconds
    long long currentTimeMs = MISC::GET_GAME_TIMER();

    // Calculate elapsed time in milliseconds
    float elapsedTimeMs = currentTimeMs - startTimeMs;

    // Clamp elapsed time to be within the duration
    elapsedTimeMs = std::fmax(0.0f, std::fmin(durationMs, elapsedTimeMs));

    // Normalize elapsed time to a value between 0 and 1
    float t = elapsedTimeMs / durationMs;

    // Apply easing function to normalized t
    float easedT = t;

    // Interpolate between start and target times
    float interpolatedMinutes = lerp(startTotalMinutes, targetTotalMinutes, easedT);

    // If the interpolated time exceeds 24 hours, wrap around
    if (interpolatedMinutes >= 24 * 60) {
        interpolatedMinutes -= 24 * 60;
    }

    return interpolatedMinutes;
}
std::string booltoStr(bool b) {
    if (b == true) {
        return "TRUE";
    } else {
        return "FALSE";
    }
}

void print_bits(unsigned int x) {
    int mask = 0x80000000;
    int i;
    CTextUI text = {std::to_string(x), CVector2(0.5,0.525), CRGBA(255,255,255,255)};
    for (i = 0; i < (sizeof(x) * 8); i++) {
        text.text = std::to_string((x & mask ? 1 : 0));
        mask >>= 1;
    }
    text.Draw();
}

            double value = interpolate(0.0, 1.0, m_fStartTime, 5000, MISC::GET_GAME_TIMER());
            double value2 = interpolate(0.0,0.8, m_fStartTime, 5000, MISC::GET_GAME_TIMER());

            MISC::SET_CURR_WEATHER_STATE(MISC::GET_HASH_KEY("CLEAR"), MISC::GET_HASH_KEY("HALLOWEEN"), value);
            GRAPHICS::SET_TIMECYCLE_MODIFIER("New_sewers");
            GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(value2);
            //1440 minutes in a day
            // 1440 - (CLOCK::GET_CLOCK_MINUTES + (CLOCK::GET_CLOCK_HOURS() * 60))
            auto interp_minutes = interpolateTimeWithDuration(CLOCK::GET_CLOCK_HOURS(), CLOCK::GET_CLOCK_MINUTES(), 0,1, 5000, m_fStartTime);
            value3 = m_fStartTime;
            clock_hours = static_cast<int>(interp_minutes) / 60;
            clock_minutes = static_cast<int>(interp_minutes) % 60;
            if (clock_minutes >= 61) {
                clock_hours += 1;
                clock_minutes = 0;
            }
            if (clock_hours >= 25) {
                clock_hours = 0;
            }
            CLOCK::SET_CLOCK_TIME(clock_hours, clock_minutes, 0);
            if (value >= 1.0) {
                GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(1);
                GRAPHICS::SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(0);
                isAmbienceConfiged = true;
                m_bConfigureAmbience = false;
            }

    heading = GetEntityHeading(PlayerPedId())
    SetFrontendActive(true)
    ActivateFrontendMenu(GetHashKey("FE_MENU_VERSION_EMPTY_NO_BACKGROUND"), true, -1)
    Citizen.Wait(100)
    N_0x98215325a695e78a(false)
    PlayerPedPreview = ClonePed(PlayerPedId(), heading, true, false)
    local x,y,z = table.unpack(GetEntityCoords(PlayerPedPreview))
    SetEntityCoords(PlayerPedPreview, x,y,z-10)
    FreezeEntityPosition(PlayerPedPreview, true)
    SetEntityVisible(PlayerPedPreview, false, false)
    NetworkSetEntityInvisibleToNetwork(PlayerPedPreview, false)
    Wait(200)
    SetPedAsNoLongerNeeded(PlayerPedPreview)
    GivePedToPauseMenu(PlayerPedPreview, 2)
    SetPauseMenuPedLighting(true)
    SetPauseMenuPedSleepState(true)
*/