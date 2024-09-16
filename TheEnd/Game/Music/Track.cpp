#include "Track.h"
#include "../../SHVNative/natives.h"
CGameTrack::CGameTrack(const TrackName track, std::vector<TrackMood> moods) :
    m_TrackName(track),
    m_TrackMood(moods)
{ 
    scriptLogI("Track: ", track.c_str());
    for (TrackMood trackM : moods) {
        scriptLogI("Track Mood Loaded: ", trackM.c_str());
    }
}


void CGameTrack::PlayTrack(int MoodIndex) {
    PrepTrack();
    if (AUDIO::TRIGGER_MUSIC_EVENT(this->m_TrackName.c_str())) {
        AUDIO::TRIGGER_MUSIC_EVENT(this->m_TrackMood[MoodIndex].c_str());
        scriptLogI("Triggering Music Event");
    }
}

void CGameTrack::ChangeTrackMood(const TrackMood _newtrackMood) {
    if (AUDIO::TRIGGER_MUSIC_EVENT(_newtrackMood.c_str())) {
        scriptLogI("[AUD] Triggered Music Event");
    } else {
        scriptLogI("[AUD] Triggering Music Event");
    }
}

bool CGameTrack::PrepTrack() {
    scriptLogI("Prepping Track: ", this->m_TrackName.c_str());
    return AUDIO::PREPARE_MUSIC_EVENT(this->m_TrackName.c_str());
}

std::vector<CGameTrack::TrackMood>* CGameTrack::GetAllTrackMoods() {
    return &this->m_TrackMood;
}

bool CGameTrack::CancelTrack(const char* trackMoodFade) {
    if (AUDIO::TRIGGER_MUSIC_EVENT(trackMoodFade)) {
        scriptLogI("[AUD] CancelTrack(const char*)");
    }
    return AUDIO::CANCEL_MUSIC_EVENT(this->m_TrackName.c_str());
}
const CGameTrack::TrackName CGameTrack::GetTrackName() {
    return this->m_TrackName;
}
bool CGameTrack::CancelTrack(int trackMoodFade) {
    if (AUDIO::TRIGGER_MUSIC_EVENT(this->m_TrackMood[trackMoodFade].c_str())) {
        scriptLogI("[AUD] CancelTrack(const char*)");
    }
    return AUDIO::CANCEL_MUSIC_EVENT(this->m_TrackName.c_str());
}


