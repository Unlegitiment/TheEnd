#include "CConfigureTheEndAmbience.h"
#include "../SHVNative/natives.h"
#include "../Logger/CLoggerInstances.h"
float CConfigureTheEndAmbience::Interpolate(float startValue, float endValue, float startTime, float duration, float currentTime) {
    double progress = (currentTime - startTime) / duration;
    if (progress > 1.0) {
        progress = 1.0; // Clamp progress to 1.0 at the end
    }
    return startValue + (endValue - startValue) * easeInOutCubic(progress);
}

float CConfigureTheEndAmbience::InterpolateTimeWithDuration(int startHour, int startMinute, int targetHour, int targetMinute, float durationMs, long long startTimeMs) {
    int startTotalMinutes = TimeToMinutes(startHour, startMinute);
    int targetTotalMinutes = TimeToMinutes(targetHour, targetMinute);

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
    float interpolatedMinutes = Lerp(startTotalMinutes, targetTotalMinutes, easedT);

    // If the interpolated time exceeds 24 hours, wrap around
    if (interpolatedMinutes >= 24 * 60) {
        interpolatedMinutes -= 24 * 60;
    }

    return interpolatedMinutes;
}

float CConfigureTheEndAmbience::Lerp(float start, float end, float t) {
    return start + t * (end - start);
}

float CConfigureTheEndAmbience::InterpolateTime(int startHour, int startMinute, int endHour, int endMinute, float t) {
    int startTotalMinutes = startHour * 60 + startMinute;
    int endTotalMinutes = endHour * 60 + endMinute;

    if (endTotalMinutes < startTotalMinutes) {
        endTotalMinutes += 24 * 60;
    }

    float interpolatedMinutes = Lerp(startTotalMinutes, endTotalMinutes, t * t);
    return interpolatedMinutes;
}

int CConfigureTheEndAmbience::TimeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}


float CConfigureTheEndAmbience::GetInterpProgress(eInterpProgressSelector selection) {
    switch (selection) {
        case eInterpProgressSelector::WEATHER:
            return this->InterpWeatherProgress;
        case eInterpProgressSelector::TIME:
            return this->InterpTimeProgress;
        case eInterpProgressSelector::TIMECYCLE:
            return this->InterpTimeCycleProgress;
        default:
            return this->InterpWeatherProgress;
    }
}

bool CConfigureTheEndAmbience::isTimeComplete() {
    return m_Set.test(eS_CONFIGURED_TIME);
}

bool CConfigureTheEndAmbience::isWeatherComplete() {
    return m_Set.test(eS_CONFIGURED_WEATHER_FX);
}

bool CConfigureTheEndAmbience::isTimeCycleComplete() {
    return m_Set.test(eS_CONFIGURED_TIMECYCLE);
}

bool CConfigureTheEndAmbience::isAllConfigured() {
    return m_Set.test(eStage::eS_FULLY_CONFIGURED);
}

void CConfigureTheEndAmbience::DoTimeCycle(float launchTime) {
    CLogger::GetInst()->GetNetworkLogger()->LogInfo(INFO, true, "DoTimeCycle Called with params: ", launchTime); //what can we do to just send this once lul
    this->m_LaunchTime = launchTime;
    const char* timeCycleModifier = "New_sewers";
    float timeCycleStrength = Interpolate(0.0, 0.8, this->m_LaunchTime, 5000, MISC::GET_GAME_TIMER());
    this->InterpTimeCycleProgress = timeCycleStrength;
    GRAPHICS::SET_TIMECYCLE_MODIFIER(timeCycleModifier);
    GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(timeCycleStrength);
    m_Set.set(eStage::eS_CONFIGURING_TIMECYCLE, 1);
    if (timeCycleStrength >= 0.8f) {
        m_Set.set(eStage::eS_CONFIGURING_TIMECYCLE, 0);
        m_Set.set(eStage::eS_CONFIGURED_TIMECYCLE, 1);
    }
}

void CConfigureTheEndAmbience::DoTime(float launchTime) {
    this->m_LaunchTime = launchTime;
    auto interp_minutes = InterpolateTimeWithDuration(CLOCK::GET_CLOCK_HOURS(), CLOCK::GET_CLOCK_MINUTES(), 0, 0, 10000, this->m_LaunchTime);
    int clock_hours = static_cast<int>(interp_minutes) / 60;
    int clock_minutes = static_cast<int>(interp_minutes) % 60;
    if (clock_minutes >= 61) {
        clock_hours += 1;
        clock_minutes = 0;
    }
    if (clock_hours >= 25) {
        clock_hours = 0;
    }
    this->InterpTimeProgress = interp_minutes;
    CLOCK::SET_CLOCK_TIME(clock_hours, clock_minutes, 0);
    m_Set.set(eStage::eS_CONFIGURING_TIME, 1);
    if (interp_minutes == 0) {
        m_Set.set(eStage::eS_CONFIGURING_TIME, 0);
        m_Set.set(eStage::eS_CONFIGURED_TIME, 1);
    }
}

void CConfigureTheEndAmbience::DoWeather(float launchTime) {
    
    this->m_LaunchTime = launchTime;
    float value = Interpolate(0.0, 1.0, this->m_LaunchTime, 5000, MISC::GET_GAME_TIMER());
    MISC::SET_CURR_WEATHER_STATE(MISC::GET_PREV_WEATHER_TYPE_HASH_NAME(), MISC::GET_HASH_KEY("HALLOWEEN"), value);
    this->InterpWeatherProgress = value;
    m_Set.set(eS_CONFIGURING_WEATHER_FX, 1);
    if (value >= 1.0f) {
        m_Set.set(eS_CONFIGURING_WEATHER_FX, 0);
        m_Set.set(eS_CONFIGURED_WEATHER_FX, 1);
    }
}

void CConfigureTheEndAmbience::DoAll(float launchTime) {
    this->m_LaunchTime = launchTime;
    if (m_Set.test(eS_FULLY_CONFIGURED) == 0) {
        DoWeather(this->m_LaunchTime);
        DoTime(this->m_LaunchTime);
        DoTimeCycle(this->m_LaunchTime);
    }
    if (this->GetInterpProgress(WEATHER) >= 1.0f && this->GetInterpProgress(TIMECYCLE) >= 0.8f && this->GetInterpProgress(TIME) == 0.0f) {
        MISC::SET_WEATHER_TYPE_NOW_PERSIST("HALLOWEEN");
        this->m_Set.set(eS_FULLY_CONFIGURED, 1);
    }
}

void CConfigureTheEndAmbience::ClearBits() {
    this->m_Set.reset();
}

void CConfigureTheEndAmbience::ClearAll() {
    
    GRAPHICS::CLEAR_EXTRA_TCMODIFIER();
    GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
    MISC::SET_WEATHER_TYPE_NOW("CLEAR");
    CLOCK::ADVANCE_CLOCK_TIME_TO(12, 0, 0);
}

void CConfigureTheEndAmbience::HoldTime(CConfigureTheEndAmbience* config) {
    if (config->m_Set.test(config->eS_CONFIGURED_TIME)) { // time configured
        //CLOCK::SET_CLOCK_TIME(0, 0, 0); // force time freeze.
    }
}
