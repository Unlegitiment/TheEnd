#pragma once
#include "./WeapComponent.h"
#include <vector>
#include <string>
class CWeaponCapture;
class CPlayerWeapon {
	static constexpr const char MAX_WEAPON_COMPONENTS = 32;
	typedef unsigned long long Hash;
	typedef const char* WeaponComponent;
public:
	CPlayerWeapon(const char* weaponName); //honestly we could 100% just put this in a buffer and just jooat the response in weapon. or just hold it regardless.
	CPlayerWeapon(Hash WeaponHash);
	void AddWeaponComponent(const char* comp);
	Hash GetModel();
	Hash GetWeapon();
	const char* GetName(const CWeaponCapture* weaponCapture);
	int GetAmmoInClip();
	int GetAmmo();
	void SetAmmo(int amm);
	void SetAmmoInClip(int amm);
	std::string GetAllWeaponComponents();
	std::vector<WeaponComponent>* GetAllWeaponComponentVec();
private:
	int m_iAmmoInClip = 0;
	int m_iAmmo = 0;
	Hash m_u64ModelHash = 0;
	Hash m_u64WeapHash = 0;
	std::vector<WeaponComponent> m_ComponentsOnGun;
};