#include "MusicInterface.h"
#include "../../SHVNative/natives.h"
CMusicTrack::CMusicTrack(const std::string& TrackName, std::vector<std::string> moods) : CGameTrack(TrackName, moods),
CurrentMood({ -1, std::string("GLOBAL_KILL_MUSIC") })
{
}

std::string CMusicTrack::GetTrackName() {
	return ::CGameTrack::GetTrackName();
}

void CMusicTrack::PlayTrack(int mood) {
	this->CurrentMood = { mood, (this->GetAllTrackMoods()->at(mood))};
	::CGameTrack::PlayTrack(mood);
	
}

void CMusicTrack::ChangeMood(int moodindex) {
	TrackMood targetMood = this->GetAllTrackMoods()->at(moodindex); // mood name // mood index
	this->CurrentMood = { moodindex, targetMood }; // this is nonconst. die please!
	::CGameTrack::ChangeTrackMood(targetMood);
}

void CMusicTrack::ChangeMood(const char* mood) {
	if (auto it = std::find(this->GetAllTrackMoods()->begin(), this->GetAllTrackMoods()->end(), mood); it != this->GetAllTrackMoods()->end()) {
		size_t type = (std::distance(this->GetAllTrackMoods()->begin(), it));
		this->CurrentMood = { (int)type, *it };
		::CGameTrack::ChangeTrackMood(it->c_str());
	} else {
		this->GetAllTrackMoods()->push_back(mood);
		std::string curMood = mood;
		this->CurrentMood = { (int)(this->GetAllTrackMoods()->size() - 1), std::string(mood)};
		::CGameTrack::ChangeTrackMood(it->c_str());
	}
}

void CMusicTrack::CancelTrack(const sMusicCancel cancel) {
	if (cancel.GLOB_KILL_MUSIC == cancel.trackCancel) {
		this->ResetCurrentTrack();
		AUDIO::TRIGGER_MUSIC_EVENT("GLOBAL_KILL_MUSIC");
	}

}

std::pair<int, const std::string&> CMusicTrack::GetMood() {
	return this->CurrentMood;
}

void CMusicTrack::ResetCurrentTrack() {
	
	this->CurrentMood = { -1, std::string("GLOBAL_KILL_MUSIC") };
}
