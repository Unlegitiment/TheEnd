/*
    Purpose: Aiming for perfection is hard. So lets aim a little lower. This is the tip of the mountain. Where everything comes together.
             Recreating the GTA Freemode Experience is hard. Especially for just one thread. We have a few other helper threads to come along. I.E The World Thread.
             However this is where the script is ran.
    Author: Unlegitiment.
*/
#define NOMINMAX
#include "script.h"
#include "keyboard.h"
#pragma warning(disable : 4244 4305) // double <-> float conversions
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
#include "./Logger/CLoggerInstances.h"
#include "./GlobalUpdateThread.h"
#include "./Game/Interior/GameInterior.h"
#include "./Important/Pause/CTheEndPauseMenu.h"
#include "./Scripts/SPRestart/Restart.h"
#include "./Launcher/CTheEndLoadMenu.h"
#include "./Launcher/ScriptDisable.h"
#include "./CTheScript.h"
#include <cmath>
#include <iostream>
#include "./Facility/CFacility.h"
#include "./TheEnd/Hud.h"
#include "./Game/Objects/CPlayer.h"
#include "./Game/Building/CBoundingBox.h"
#include "./Game/Anim/SyncronizedScene.h"
#include "./CaptureSys/WeaponCapture.h"
#include "./CaptureSys/PlayerWeapon.h"
#include "./Game/Hud/CWeaponWheel.h"
#include "./Game/Hud/HudInterface.h"
void main() {
    CWeaponCapture weapCapture = CWeaponCapture();
    THEENDSCRIPT->OneTime();
    EHUD->OneTick();
    bool m_bShowWeapnWheel = false;
    while (true){ // we've turned off the normal loop here for smaller testing of the program. sGameWorld being still active however.
        SCRIPT_MGR->Update();
        EHUD->Update();
        THEENDSCRIPT->Update();
        if (IsKeyJustUp(VK_F14)) {
            m_bShowWeapnWheel = !m_bShowWeapnWheel;
            scriptLogI("ShowWeaponWheel: ", m_bShowWeapnWheel);
        }
        if (m_bShowWeapnWheel) {
            int x = GRAPHICS::REQUEST_SCALEFORM_MOVIE_INSTANCE("NEW_HUD"); // hud.gfx?
            GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(x, "SET_WEAPON_WHEEL_ACTIVE");
            GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
            GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
            GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(x, "SHOW_ALL");
            GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
            GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
            GRAPHICS::DRAW_SCALEFORM_MOVIE(x, 0.5, 0.5, 1, 1, 255, 255, 255, 255, 0);
            HUD::SHOW_HUD_COMPONENT_THIS_FRAME(x - 1);
            
        }
        if (IsKeyJustUp(VK_F16)) {
            OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_1"), 0, 0, 1);
            OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_2"), 0, 0, 1);
            OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(MISC::GET_HASH_KEY("THEEND_DOOR_3"), 0, 0, 1);
        }
        
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

//FACILITY

//CFacility facility = CFacility(WORLD->GetInteriorManager());
//facility.SummonBase();
//facility.SummonInteriorComponent("set_int_02_decal_01");
//facility.SetInteriorPropColor("set_int_02_decal_01", 1);
//facility.Default();
//
//facility.RefreshInterior();
//WORLD->GetLocalPlayer()->SetCoordinates({ 483.2006225586f, 4810.5405273438f, -58.919288635254f});

//SILO REASON FOR SCRATCH: (DLC::ON_ENTER_MP()) 
//CInterior silo = CInterior(WORLD->GetInteriorManager());
//silo.AddEntry("m23_1_dlc_int_03_m23_1"); // the silo is an DLC::ON_ENTER_MP interior. which means it can't be deloaded from a script. weird.
//silo.Request();

/* DESTROY FREEMODE ENVIRONMENT ( CANNOT RELAUNCH SOME OF THESE SCRIPTS ) 
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
*/

//DOOR RELATED SHIT.

//Hash left = MISC::GET_HASH_KEY("DOOR_LEFT_SILO_BASE");
//Hash right = MISC::GET_HASH_KEY("DOOR_RIGHT_SILO_BASE");
//OBJECT::ADD_DOOR_TO_SYSTEM(left, MISC::GET_HASH_KEY("v_ilev_garageliftdoor"), -1920.684, 3749.0371, -100.65, 1, 1, 1);
//OBJECT::ADD_DOOR_TO_SYSTEM(right, MISC::GET_HASH_KEY("v_ilev_garageliftdoor"), -1920.690, 3750.5276, -100.65, 1, 1, 1);
//if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(left)) {
//    OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(left, 4.0f, 0, 1);
//    OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(left, 10.f, 0, 1);
//    OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(left, 3, 0, 1);
//}
//if (OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(right)) {
//    OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(right, 4.0f, 0, 1);
//    OBJECT::DOOR_SYSTEM_SET_AUTOMATIC_RATE(right, 10.f, 0, 1);
//    OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(right, 3, 0, 1);
//}
//PED::SET_PED_MODEL_IS_SUPPRESSED(MISC::GET_HASH_KEY("A_C_SHARKTIGER"), 1);