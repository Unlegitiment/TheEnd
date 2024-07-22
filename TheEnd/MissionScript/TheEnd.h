#pragma once
#include "../MarkerLauncher/VisualMarker.h"
#include <vector>
class CTheEnd final {
public:
    CTheEnd(CVector3 missionPosition) :
        markerPos(missionPosition),
        markerInfo("Mission", "The End", "", "100%", "", false, "1", "", "", ""),
        marker(markerPos, { 5.f,5.f,1.f }, CRGBA(255, 255, 255, 255), CTxd("mpmissmarkers256", "custom_icon")),
        vismarker(markerInfo, marker),
        missionState(0)
    {

    }
    void Run(int byteSelect);
    void OnTransition();
    bool GetMissionActive() {
        return CTheEnd::isMissionActive;
    }
    void SetMissionActive(bool isactive) {
        CTheEnd::isMissionActive = isactive;
        return;
    }
    int getMissionState() {
        return this->missionState;
    }
    enum MissionStates {
        EMS_PRELOAD = 0,
        EMS_MISSION_IN_PAUSE_STATUS = 10, // Pause menu is up with the preloaded stuff buttons etc. (not a real pause menu) 
        EMS_MISSIONSTATE_CHECKPOINT = 20,
        EMS_MISSIONSTATE_CHECKPOINT1 = 30,
        EMS_MISSIONSTATE_CHECKPOINT2 = 40,
        EMS_MISSIONSTATE_CHECKPOINT3 = 50,
        EMS_MISSIONSTATE_CHECKPOINT4 = 60,// ... We should add more here if we run out of states.
        EMS_DISPLAYING_ENDSCREEN = 70,
        EMS_CLEANUP_ENTITY = 80,
    };
    void RequestAllModels();
    void PrepareModels();
    void Destroy();
private:
    static bool isMissionActive;
    CVector3 markerPos;
    CMarkerInfo markerInfo;
    CMissionMarker marker;
    CVisMarker vismarker;
    int missionState; 
    std::vector<Hash> m_models;
    std::vector<Hash> m_peds;
    std::vector<Hash> m_vehicles;
};