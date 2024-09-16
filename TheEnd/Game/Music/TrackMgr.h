#pragma once
#include <stack>
class CGameTrack;
class CTheEndDoomsdayTrack;
class CGameTrackMgr {
private:
	
	std::stack<CGameTrack*> stack;
	CGameTrack* m_pCurrentTrack = nullptr;
	bool m_bDoWeNeedToUpdateNow;
	void PopTrack();
public:
	CGameTrackMgr();
	int PushTrack(bool reqUpdate, CGameTrack* track); //reqUpdate means that the old track gets immediately deleted
	void Update();
};