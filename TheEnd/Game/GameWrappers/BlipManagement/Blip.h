#pragma once
#include <bitset>
class CBlip {
public:
	friend class CBlipMgr;
	void SetNewBlipIcon(int Icon);
	void SetBlipName();
	void DeleteBlip();
	friend void Update();
	enum BlipConfigFlags {
		BCF_,
		BCF_,
		BCF_,
		BCF_,
		BCF_,
		BCF_MAX
	};
private:

	bool m_bisFlashing;
	const char* m_pName;
	int m_iIcon;
	CRGBA<int> m_Color;
	std::bitset<BlipConfigFlags::BCF_MAX> m_BlipConfig;

};
#include "../../../SHVNative/types.h"
class CBlipFactory {
private:
public:
	static CBlip* CreateBlipForCoords(CBlipMgr* blipsMgr, CVector3<float> position);
	static CBlip* CreateBlipForEntity(CBlipMgr* blipMgr, int EntityHandle);
	static CBlip* CreateBlipForRadius(CBlipMgr* blipMgr, CVector3<float> position, float radii);
	static CBlip* CreateBlipForPickup(CBlipMgr* blipMgr, int pickupHandle);
};