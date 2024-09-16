#pragma once
#include <vector>
#include <string>
class CGameTrack {
public:
	typedef std::string TrackName;
	typedef std::string TrackMood;
private:
	const TrackName m_TrackName;
	std::vector<TrackMood> m_TrackMood;
protected:
	void ChangeTrackMood(const TrackMood _newtrackMood); // this is more for subclasses
	std::vector<TrackMood>* GetAllTrackMoods();
public:
	const TrackName GetTrackName();
	CGameTrack(const TrackName track, std::vector<TrackMood> moods);
	void PlayTrack(int MoodIndex); // dependant on init of moods
	bool PrepTrack();
	bool CancelTrack(const char* trackMoodFade);
	bool CancelTrack(int trackMoodFade);
};