#pragma once
#include "../Game/Music/Track.h"
class CTheEndDoomsdayMusic : CGameTrack{
	using TrackName = char*;
	using TrackMood = char*;
public:
	enum eMusicMood {
		ACTION,
		AIRBORNE,
		SUSPENSE,
		VEHICLE_CHASE,
		EMM_MAX
	};
private:
	static constexpr const TrackName Track_Start = "CMH_MP_START";
	static constexpr const TrackName Track_End = "CMH_MP_MUSIC_END";
	static constexpr const TrackName Track_Fail = "CMH_MP_MUSIC_FAIL";
	std::vector<TrackMood> Track_Moods = {
		"MP_MC_CMH_ACTION",
		"MP_MC_CMH_AIRBORNE",
		"MP_MC_CMH_SUSPENSE",
		"MP_MC_CMH_VEHICLE_CHASE"
	};

	eMusicMood CurrentTrackMood; 
public:
	CTheEndDoomsdayMusic();
	eMusicMood GetMood();
	void Init();
	void PlayTrack();
	void ChangeTrack(eMusicMood mood);
	void StopTrack();
	void EndTrack();
};