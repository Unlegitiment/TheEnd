#pragma once
class CBlackout {
public:
	void Update();
private:
	bool m_bIsBlackoutEnabled = false;
	bool m_bDoesBlackoutEffectVehicles = false;
};