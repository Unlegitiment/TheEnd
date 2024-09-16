#pragma once
#include "./Interior/InterriorBase.h"
class CCasino : private baseInterior{
public:
	struct sCasinoState : baseInterior::sInteriorInformation{
		sCasinoState();
		bool m_bHasCasinoDoorsLoaded = false;
	};
	CCasino();
	void Init();
	void Trigger();
	void Despawn();
	sCasinoState* GetState() { return &this->m_State; }
private:
	sCasinoState m_State;
};