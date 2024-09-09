#include "PlayerWeapon.h"
#include <string.h>
#include <stdlib.h>
#include "../SHVNative/natives.h"
#include "./WeaponCapture.h"
CPlayerWeapon::CPlayerWeapon(const char* weaponName) {
	this->m_u64WeapHash = MISC::GET_HASH_KEY(weaponName);
	this->m_u64ModelHash = WEAPON::GET_WEAPONTYPE_MODEL(this->m_u64WeapHash);
}
CPlayerWeapon::CPlayerWeapon(CPlayerWeapon::Hash weaponHash) {
	this->m_u64WeapHash = weaponHash;
	this->m_u64ModelHash = WEAPON::GET_WEAPONTYPE_MODEL(this->m_u64WeapHash);
}

CPlayerWeapon::Hash CPlayerWeapon::GetModel() {
	return this->m_u64ModelHash;
}

CPlayerWeapon::Hash CPlayerWeapon::GetWeapon() {
	return this->m_u64WeapHash;
}

const char* CPlayerWeapon::GetName(const CWeaponCapture* weaponCapture) {
	
	const char* test = (weaponCapture->GetMap()->at(this->GetWeapon()));
	return test;
}

int CPlayerWeapon::GetAmmoInClip() {
	return this->m_iAmmoInClip;
}

int CPlayerWeapon::GetAmmo() {
	return this->m_iAmmo;
}

void CPlayerWeapon::SetAmmo(int amm) {
	this->m_iAmmo = amm;
}

void CPlayerWeapon::SetAmmoInClip(int amm) {
	this->m_iAmmoInClip = amm;
}
