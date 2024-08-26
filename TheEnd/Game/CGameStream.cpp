#include "CGameStream.h"
#include "../SHVNative/natives.h"
CGameStreamingMgr::CGameStreamingMgr(void) :
    isMP_MAP_ACTIVE(false)
{
    this->Initialize();
}

void CGameStreamingMgr::Initialize() { // we always want to enable the MP MAP regardless. 
    DLC::ON_ENTER_MP();
    this->isMP_MAP_ACTIVE = true;
}

bool CGameStreamingMgr::CheckForDLC(unsigned long long DLCHASH) {
    return DLC::IS_DLC_PRESENT(DLCHASH);
}

bool CGameStreamingMgr::isMPMapActive() {
    return this->isMP_MAP_ACTIVE;
}
