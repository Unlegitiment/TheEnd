/*
    Purpose: Aiming for perfection is hard. So lets aim a little lower. This is the tip of the mountain. Where everything comes together.
             Recreating the GTA Freemode Experience is hard. Especially for just one thread. We have a few other helper threads to come along. I.E The World Thread.
             However this is where the script is ran.
    Author: Unlegitiment.
*/
#define NOMINMAX
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
#include <bitset>
#include "./Ambience/CConfigureTheEndAmbience.h"
#include "./Scripts/CDisable.h"
#pragma warning(disable : 4244 4305) // double <-> float conversions
#include "./Logger/CLoggerInstances.h"
#include "./GlobalUpdateThread.h"
#include "./Game/Interior/GameInterior.h"
#include "./Important/Pause/CTheEndPauseMenu.h"
#include "./Scripts/SPRestart/Restart.h"
#include "./Launcher/CTheEndLoadMenu.h"
//This does NOT work. Depricated and completely fucking invalid I mean jfc. Logic found in Shop_Controller.sc which CAN be reset through loading a save file.
void GameVersionCheck();
std::string ClockToDay(int day);
void RotatePoint(float& x, float& y, float& z, float rx, float ry, float rz) {
    // Convert degrees to radians
    float rxRad = rx * (3.14f / 180.0f);
    float ryRad = ry * (3.14f / 180.0f);
    float rzRad = rz * (3.14f / 180.0f);

    // Rotation around X-axis
    float yTemp = y * cos(rxRad) - z * sin(rxRad);
    float zTemp = y * sin(rxRad) + z * cos(rxRad);
    y = yTemp;
    z = zTemp;

    // Rotation around Y-axis
    float xTemp = x * cos(ryRad) + z * sin(ryRad);
    z = -x * sin(ryRad) + z * cos(ryRad);
    x = xTemp;

    // Rotation around Z-axis
    xTemp = x * cos(rzRad) - y * sin(rzRad);
    y = x * sin(rzRad) + y * cos(rzRad);
    x = xTemp;
}

// Function to draw a rotated box around a specific point
void DrawRotatedBox(float centerX, float centerY, float centerZ, float width, float height, float depth, float rotX, float rotY, float rotZ) {
    // Calculate half-dimensions
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;

    // Define vertices of the box
    float vertices[8][3] = {
        {centerX - halfWidth, centerY - halfHeight, centerZ - halfDepth},
        {centerX + halfWidth, centerY - halfHeight, centerZ - halfDepth},
        {centerX + halfWidth, centerY + halfHeight, centerZ - halfDepth},
        {centerX - halfWidth, centerY + halfHeight, centerZ - halfDepth},
        {centerX - halfWidth, centerY - halfHeight, centerZ + halfDepth},
        {centerX + halfWidth, centerY - halfHeight, centerZ + halfDepth},
        {centerX + halfWidth, centerY + halfHeight, centerZ + halfDepth},
        {centerX - halfWidth, centerY + halfHeight, centerZ + halfDepth}
    };

    // Rotate vertices
    for (int i = 0; i < 8; ++i) {
        RotatePoint(vertices[i][0], vertices[i][1], vertices[i][2], rotX, rotY, rotZ);
    }

    // Draw the edges of the box
    auto drawLine = [](float* v1, float* v2) {
        GRAPHICS::DRAW_LINE(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], 255, 0, 0, 255);
        };

    // Bottom face
    drawLine(vertices[0], vertices[1]);
    drawLine(vertices[1], vertices[2]);
    drawLine(vertices[2], vertices[3]);
    drawLine(vertices[3], vertices[0]);

    // Top face
    drawLine(vertices[4], vertices[5]);
    drawLine(vertices[5], vertices[6]);
    drawLine(vertices[6], vertices[7]);
    drawLine(vertices[7], vertices[4]);

    // Vertical edges
    drawLine(vertices[0], vertices[4]);
    drawLine(vertices[1], vertices[5]);
    drawLine(vertices[2], vertices[6]);
    drawLine(vertices[3], vertices[7]);
}
#include <cmath>
#include <iostream>
#include "./Facility/CFacility.h"
bool IsPointInBox(Vector3 point, Vector3 boxCenter, float width, float height, float depth, float rotX, float rotY, float rotZ) {
    // Calculate half-dimensions
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;

    // Define the vertices of the box
    Vector3 vertices[8] = {
        {boxCenter.x - halfWidth, boxCenter.y - halfHeight, boxCenter.z - halfDepth},
        {boxCenter.x + halfWidth, boxCenter.y - halfHeight, boxCenter.z - halfDepth},
        {boxCenter.x + halfWidth, boxCenter.y + halfHeight, boxCenter.z - halfDepth},
        {boxCenter.x - halfWidth, boxCenter.y + halfHeight, boxCenter.z - halfDepth},
        {boxCenter.x - halfWidth, boxCenter.y - halfHeight, boxCenter.z + halfDepth},
        {boxCenter.x + halfWidth, boxCenter.y - halfHeight, boxCenter.z + halfDepth},
        {boxCenter.x + halfWidth, boxCenter.y + halfHeight, boxCenter.z + halfDepth},
        {boxCenter.x - halfWidth, boxCenter.y + halfHeight, boxCenter.z + halfDepth}
    };

    // Rotate vertices
    for (int i = 0; i < 8; ++i) {
        RotatePoint(vertices[i].x, vertices[i].y, vertices[i].z, rotX, rotY, rotZ);
    }

    // Translate point to origin
    point.x -= boxCenter.x;
    point.y -= boxCenter.y;
    point.z -= boxCenter.z;

    // Rotate point
    RotatePoint(point.x, point.y, point.z, rotX, rotY, rotZ);

    // Define the min and max values for each axis
    
    float minX = std::min({ vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x, vertices[4].x, vertices[5].x, vertices[6].x, vertices[7].x });
    float maxX = std::max({ vertices[0].x, vertices[1].x, vertices[2].x, vertices[3].x, vertices[4].x, vertices[5].x, vertices[6].x, vertices[7].x });
    float minY = std::min({ vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y, vertices[4].y, vertices[5].y, vertices[6].y, vertices[7].y });
    float maxY = std::max({ vertices[0].y, vertices[1].y, vertices[2].y, vertices[3].y, vertices[4].y, vertices[5].y, vertices[6].y, vertices[7].y });
    float minZ = std::min({ vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z, vertices[4].z, vertices[5].z, vertices[6].z, vertices[7].z });
    float maxZ = std::max({ vertices[0].z, vertices[1].z, vertices[2].z, vertices[3].z, vertices[4].z, vertices[5].z, vertices[6].z, vertices[7].z });

    // Check if point is within bounds
    return (point.x >= minX && point.x <= maxX) &&
        (point.y >= minY && point.y <= maxY) &&
        (point.z >= minZ && point.z <= maxZ);
}
#include "./Game/Objects/CPlayer.h"
#define WORLD sGameWorld::GetInstance()
void main() {
    CTheEndLoadMenu menuLoad = CTheEndLoadMenu();
    menuLoad.Init();
    bool displayLoadMenu = true;
    CDisableScripts disableScripts = CDisableScripts();
    CVector3<float> v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
    CFacility facility = CFacility(WORLD->GetInteriorManager());
    //facility.SummonBase();
    //facility.SummonInteriorComponent("set_int_02_decal_01");
    //facility.SetInteriorPropColor("set_int_02_decal_01", 1);
    //facility.Default();
    //
    //facility.RefreshInterior();
    //WORLD->GetLocalPlayer()->SetCoordinates({ 483.2006225586f, 4810.5405273438f, -58.919288635254f});
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
    CInterior silo = CInterior(WORLD->GetInteriorManager());
    silo.AddEntry("m23_1_dlc_int_03_m23_1"); // the silo is an DLC::ON_ENTER_MP interior. which means it can't be deloaded from a script. weird.
    silo.Request();
    
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
    disableScripts.PushBackScript("mission_repeat_controller"); // also add here to disable respawn script. so that we write our own in here. and so that we can restart it.
    disableScripts.PushBackScript("mission_Race");
    disableScripts.Update();
    CClientNetwork* logger = CLogger::GetInst()->GetNetworkLogger();
    logger->LogInfo(INFO, true, "We have summoned the script");
    logger->LogInfo(INFO, true, disableScripts.GetLogStatement());
    bool curInteriorStatus = false;
    CPauseMenuPaginator paginator = CPauseMenuPaginator();
    //pauseMenu.Init();
    DLC::ON_ENTER_MP(); // alrighty lol
    PED::SET_PED_MODEL_IS_SUPPRESSED(MISC::GET_HASH_KEY("A_C_SHARKTIGER"), 1);
    int staggeredLoopTimer = MISC::GET_GAME_TIMER();
    if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("pedmugshot_01")) {
        scriptLogI(__LINE__, __FILE__, ": Script has loaded pedmugshot_01");
    } else {
        GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("pedmugshot_01", 1);
    }
    CTheEndPauseMenu pauseMenu = CTheEndPauseMenu();
    const char* model = "m24_1_mp2024_01_additions_carrmp_2_tg_hull1"; // we have to be near to the model to summon this prop.
    Hash h = MISC::GET_HASH_KEY(model);
    STREAMING::REQUEST_MODEL(h);
    Object o;
    if (STREAMING::HAS_MODEL_LOADED(h)) {
        scriptLogI("Found Model: ", model, " at: ", h);
        o = OBJECT::CREATE_OBJECT(h, v.x, v.y, v.z, 1, 0, 1);
        scriptLogI("Attempting load of Object Collision: ", model);
        STREAMING::REQUEST_COLLISION_FOR_MODEL(h);
    } else {
        scriptLogW("Thats a shame! Model: ", model, " not found! Womp womp!"); // if we can't load the model this is a big issue. Lets teleport to where it is in the worldspace located: for example if the thing is located in an IPL then summon it. teleport the player to where the loading 
    }
    pauseMenu.Init();
    while (true){ // we've turned off the normal loop here for smaller testing of the program. sGameWorld being still active however.
        disableScripts.StaggeredLoop(&staggeredLoopTimer); //keeping the logic of program reload and cancel.
        if (displayLoadMenu) {
            menuLoad.Update();
        }
        if (IsKeyJustUp(VK_F13)) {
            if (displayLoadMenu) {
                MINIMAP->SetMinimapActive(true);
            }
            displayLoadMenu = !displayLoadMenu;
            scriptLogI("F13 pressed. CurStatus: ", displayLoadMenu);
        }
#ifdef TRADITIONAL_PROGRAM_LOOP
        //// Define vertices for the polygon
        //float x1 = 100.0f, y1 = 100.0f, z1 = 150.0f; // Vertex 1
        //float x2 = 125.0f, y2 = 100.0f, z2 = 150.0f; // Vertex 2
        //float x3 = 125.0f, y3 = 150.0f, z3 = 150.0f; // Vertex 3

        //// Define color and opacity
        //int red = 255;
        //int green = 0;
        //int blue = 0;
        //int alpha = 128; // Semi-transparent

        // Draw the polygon
        v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
        
        DrawRotatedBox(-175.6,502.4,137.7,3,2.0,3,0,0,0);
        if (IsPointInBox(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(),1), CVector3<float>{-175.6f, 502.4f, 137.7f}.GetAsStruct(), 3, 2.0, 3, 0, 0, 0)) {
            CTextUI("You're inside the bounding box", { 0.1f,0.15f }, {255.f,255.f,255.f,255.f}).Draw();
        }
        //GRAPHICS::DRAW_POLY(x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha);
        pauseMenu.Update();
        if (IsKeyJustUp(VK_F4)) {
            disableScripts.RestartAllScripts();
        }
        if (HUD::IS_PAUSEMAP_IN_INTERIOR_MODE()) {
            HUD::SET_RADAR_AS_EXTERIOR_THIS_FRAME();
            HUD::SET_RADAR_AS_INTERIOR_THIS_FRAME(MISC::GET_HASH_KEY("h4_fake_islandx"), 4700.0f, -5150.0f, 0.0f, 0.0f);
        }
        //pauseMenu.Update();
        disableScripts.StaggeredLoop(&staggeredLoopTimer);
        CTextUI(std::to_string(ambienceConfigurer.GetInterpProgress(ambienceConfigurer.TIMECYCLE)), { 0.5f,0.55f }, { 255,255,255,255 }).Draw();
        CTextUI(std::to_string(ambienceConfigurer.GetInterpProgress(ambienceConfigurer.WEATHER)), {0.5f,0.575f}, {255,255,255,255}).Draw();
        bool isPedInsideDeluxo = (PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), Deluxo, 0));
        if (IsKeyJustUp(VK_DIVIDE)) {
            bitStatus_SHOP_CONTRLLER.set(0, 1);
        }
        if (bitStatus_SHOP_CONTRLLER.test(0)) {
            while(!CDisableScripts::RestartScript("GB_HEADHUNTER", CDisableScripts::MULTIPLAYER_MISSION)) {
                bitStatus_SHOP_CONTRLLER.set(2, 1);//isrequesting
                WAIT(0);
            }
            bitStatus_SHOP_CONTRLLER.set(2, 1);//done
            bitStatus_SHOP_CONTRLLER.set(1, 0);//transition bit done
            bitStatus_SHOP_CONTRLLER.set(0, 0); //  clear test bit.
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
            logger->LogInfo(WARN, true, "Deluxo is invalid. Respawning.");
            WAIT(5000);
            Deluxo = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("DELUXO"), 47.2755f, -862.1296f, 30.05f, 340.8, 1, 0, 1);
        }
        WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_SOUTH, curInteriorStatus); //Todo -- Add cleanup for this bit if we set the curInteriorStatus to false we never clear the interior.
        WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_LOAD_AIRCRAFT_CARRIER_NORTH, curInteriorStatus); //Todo -- Add cleanup for this bit if we set the curInteriorStatus to false we never clear the interior.
        WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_DISABLE_LOS_SANTOS, curInteriorStatus);
        WORLD->GetGameInteriorInformation()->set(WORLD->eGWBS_WORLD_LOAD_CAYO, curInteriorStatus);
        if (IsKeyJustUp(VK_F14)) {
            curInteriorStatus = !curInteriorStatus;
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
        //if (isOnlineReq == false) {
        //    DLC::ON_ENTER_MP();
        //    isOnlineReq = true;
        //}
        if (silo.IsInteriorActive()) { // Todo -- Run this threw the game world stuff.
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

        if (v.Dist(CVector3<float>{ -1921.955, 3749.7202, -99 }) < 1.76) {
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
        CMissionMarker marker = CMissionMarker({v.x, v.y, v.z + 2.f}, { 5.f,5.f,1.f }, CRGBA<float>(255, 255, 255, 255), CTxd("mpmissmarkers256", "custom_icon")); // i never draw these. idk why these are loaded into mem. 
        CVisMarker vismarker = CVisMarker(markerInfo, marker);
        CVector3<float> v = CAM::GET_GAMEPLAY_CAM_ROT(2);
        //TODO -- Put all pause menu Logic into a CTheEndPauseMenu! for clean and simplisiticity! Done. 8/18/24 3:50 am

        //vCorona.Draw();eeee
#endif //TRADITIONAL_PROGRAM_LOOP
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