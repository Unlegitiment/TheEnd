#include "Music.h"
#include "../SHVNative/natives.h"
CTheEndDoomsdayMusic::CTheEndDoomsdayMusic() : CGameTrack("CMH_MP_START", { "MP_MC_CMH_ACTION", "MP_MC_CMH_AIRBORNE", "MP_MC_CMH_SUSPENSE", "MP_MC_CMH_VEHICLE_CHASE" }) {
	this->Init();
}

CTheEndDoomsdayMusic::eMusicMood CTheEndDoomsdayMusic::GetMood() {
	return this->CurrentTrackMood;
}

void CTheEndDoomsdayMusic::Init() {

}

void CTheEndDoomsdayMusic::PlayTrack() {
	this->CurrentTrackMood = this->SUSPENSE;
	__super::PlayTrack(this->SUSPENSE);
}

void CTheEndDoomsdayMusic::ChangeTrack(eMusicMood mood) {
	this->CurrentTrackMood = mood;
	scriptLogI("Changing Mood to: %s", this->Track_Moods[mood]);
	__super::ChangeTrackMood(this->Track_Moods[mood]);
}

void CTheEndDoomsdayMusic::StopTrack() {
	if (AUDIO::TRIGGER_MUSIC_EVENT("GLOBAL_KILL_MUSIC")) {
		scriptLogI("Triggered Music Event: %s", Track_End);
	}
}

void CTheEndDoomsdayMusic::EndTrack() {
	if (AUDIO::TRIGGER_MUSIC_EVENT("GLOBAL_KILL_MUSIC")) {
		scriptLogI("Triggered Music Event: %s", Track_End);
	}
	AUDIO::CANCEL_MUSIC_EVENT(this->Track_Start); // stop the track lul
}
