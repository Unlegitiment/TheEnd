#pragma once
#include "./Track.h"
#include <string>
class CMusicTrack : private CGameTrack{
public:
	static const int MOOD_TRACK_NO_MOOD = -1;
	struct sMusicCancel {
		enum eCancelMethod {
			GLOB_KILL_MUSIC,
			CUSTOM_TRACK_KILL
		};
		eCancelMethod trackCancel;
		union {
			const char* CustomTrackKill; // ignore if trackCancel == glob_kill_music
		};
	};
	CMusicTrack(const std::string& TrackName, std::vector<std::string> moods);
	std::string GetTrackName();
	void PlayTrack(int mood);
	void ChangeMood(int moodindex);
	void ChangeMood(const char* mood);
	void CancelTrack(const sMusicCancel cancel); 
	std::pair<int, const std::string&> GetMood();
private:
	void ResetCurrentTrack();
	std::pair<int, std::string> CurrentMood;
};