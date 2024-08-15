#pragma once
#include <bitset>
#include "../SHVNative/types.h"
class CConfigureTheEndAmbience;
class CDeluxo { // would extend CVehicle however as we don't have that class we don't care.
private:
	int m_iHandle; // push to super object
	bool m_bIsPlayerInDeluxo; // push to super object under m_bIsPlayerInThisVehicle;
	std::bitset<8> m_ToggleBytes;
	CVector3<float> m_vPosition; // PUSH to super object
	enum eDeluxoBitToggles {
		eDBT_NO_FLIGHT, // force deluxo to never fly.
		eDBT_HOVER_ONLY, // force deluxo to only be able to drive or hover
		eDBT_EFFECT_ACTIVE, // effect is now active.
		eDBT_EFFECT_TRANS, // effect in transition
		eDBT_EFFECT_AWAITING, // awaiting player get in.
		eDBT_EFFECT_EMP,

		eDBT_MAX
	};
public:
	void SetDeluxoNoFlight(bool b);
	void SetDeluxoLockedToGround(bool b);// this is so that the player can still however but cannot fly.
	static bool GetIfDeluxoExists();
	void DisableDeluxo(); // EMP
	void Update(); // Get Position, Screen Effects etc. PUSH to super object as virtual method
	void GetInEffectActive();
	void ActivateEffect(const CConfigureTheEndAmbience* ambienceptr);
	void ForceEffectOff(const CConfigureTheEndAmbience* ambienceptr);

};