#include "TrackMgr.h"
#include "./Track.h"
CGameTrackMgr::CGameTrackMgr() {
}

int CGameTrackMgr::PushTrack(bool reqUpdate, CGameTrack* track) {
    this->m_bDoWeNeedToUpdateNow = reqUpdate;
    this->stack.push(track);
    return 0;
}

void CGameTrackMgr::Update() {
    if (this->m_bDoWeNeedToUpdateNow) {
        CGameTrack* ptr = this->stack.top();
        this->m_pCurrentTrack->CancelTrack("GLOBAL_KILL_MUSIC");
        this->m_pCurrentTrack = ptr;
        this->m_pCurrentTrack->PlayTrack(0);
    }
}
