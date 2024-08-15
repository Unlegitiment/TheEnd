#include "CDeluxo.h"
#include "../Scripts/CDisable.h"
#include "../SHVNative/natives.h"
void CDeluxo::Update() {
    return;
}
void CDeluxo::Respawn() {
    Hash deluxoHash = MISC::GET_HASH_KEY("DELUXO");
    if (DisableShopController()) {
        STREAMING::REQUEST_MODEL(deluxoHash);
        if (!STREAMING::HAS_MODEL_LOADED(deluxoHash)) {
            STREAMING::REQUEST_MODEL(deluxoHash);
        }
        int seed = MISC::GET_GAME_TIMER();
        Quaternion<float> spawnpos = { 0,0,0,0 };
        int rand2 = (rand() % this->m_SpawnablePos.size());
        spawnpos = m_SpawnablePos[rand2];
        this->Handle = VEHICLE::CREATE_VEHICLE(deluxoHash, spawnpos.r,spawnpos.g,spawnpos.b,spawnpos.a, 1,0,0); // yes weird Quaternion define die please :)
        //todo check bits and make sure they have the flight stuff turned off. not sure if you need to call on frame.
    }
}
bool CDeluxo::DisableShopController() {
    return false; // will eventually disable the shop controller;
}
