#pragma once
#include "./WeapComponent.h"
class CWeaponCapture;
class CPlayerWeapon {
	static constexpr const char MAX_WEAPON_COMPONENTS = 32;
	typedef unsigned long long Hash;
public:
	CPlayerWeapon(const char* weaponName); //honestly we could 100% just put this in a buffer and just jooat the response in weapon. or just hold it regardless.
	CPlayerWeapon(Hash WeaponHash);
	Hash GetModel();
	Hash GetWeapon();
	const char* GetName(const CWeaponCapture* weaponCapture);
	int GetAmmoInClip();
	int GetAmmo();
	void SetAmmo(int amm);
	void SetAmmoInClip(int amm);
private:
	int m_iAmmoInClip;
	int m_iAmmo;
	Hash m_u64ModelHash;
	Hash m_u64WeapHash;
	CPlayerWeaponComponent* m_aWeaponComponent[MAX_WEAPON_COMPONENTS] = { 0 };
};