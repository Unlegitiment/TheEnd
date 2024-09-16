#pragma once
#define BIT(x) (1 << x)
#include <bitset>
#include <cmath>
class CConfigureTheEndAmbience {

private:
	enum eStage {
		eS_CONFIGURING_TIME = 0,
		eS_CONFIGURING_TIMECYCLE = 1,
		eS_CONFIGURING_WEATHER_FX = 2,
		eS_CONFIGURED_TIME = 3,
		eS_CONFIGURED_TIMECYCLE = 4,
		eS_CONFIGURED_WEATHER_FX = 5,
		eS_FULLY_CONFIGURED = 6
	};
	std::bitset<8> m_Set;
	int m_LaunchTime;
	static __forceinline float easeInOutQuad(float t) {
		if (t < 0.5f) {
			return 2 * t * t;
		} else {
			return -1 + (4 - 2 * t) * t;
		}
	}
	static __forceinline float easeInOutCubic(float x) {
		if (x < 0.5) {
			return 4 * x * x * x;
		} else {
			return 1 - std::pow(-2 * x + 2, 3) / 2;
		}
	}
	static __forceinline float easeInOutSine(float f) {
		return -(cos(3.14159 * f) - 1) / 2;
	}
public:
	static float Interpolate(float startValue, float endValue, float startTime, float duration, float currentTime);
	static float InterpolateTimeWithDuration(int startHour, int startMinute, int targetHour, int targetMinute, float durationMs, long long startTimeMs);
	static float Lerp(float start, float end, float t);
	static float InterpolateTime(int startHour, int startMinute, int endHour, int endMinute, float t);
	static int TimeToMinutes(int hour, int minute);
private:
	float InterpTimeProgress;
	float InterpTimeCycleProgress;
	float InterpWeatherProgress;
public:
	enum eInterpProgressSelector {
		TIME,
		TIMECYCLE,
		WEATHER
	};
	float GetInterpProgress(eInterpProgressSelector selection);
	template<size_t BITS>
	std::bitset<BITS> GetBitStatus();
	bool isTimeComplete();
	bool isWeatherComplete();
	bool isTimeCycleComplete();
	bool isAllConfigured();
	void DoTimeCycle(float launchTime);
	void DoTime(float launchTime);
	void DoWeather(float launchTime);
	void DoAll(float launchTime);
	void ClearBits();
	static void ClearAll();
	static void HoldTime(CConfigureTheEndAmbience* config);
};

template<size_t BITS>
inline std::bitset<BITS> CConfigureTheEndAmbience::GetBitStatus() {
	return m_Set;
}
