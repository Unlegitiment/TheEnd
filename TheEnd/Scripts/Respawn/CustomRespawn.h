#pragma once
class CPlayer;
#include "../../SHVNative/types.h"
class CRespawn {
public:
	void RespawnPlayer();
	static void RespawnEntity(int entityHandle);
	static void RespawnAtHospital(CPlayer* player); // get location of death.
	void Update(bool updatenow); // once player has died we force a script update.
private:
	CPlayer* m_pPlayer;
	bool m_bHasPlayerDied;
	bool m_bForceUpdate;
};
typedef Singleton<CRespawn> sRespawn;
#define RES_INST sRespawn::GetInstance()
