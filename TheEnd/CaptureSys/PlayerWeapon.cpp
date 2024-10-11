#include "PlayerWeapon.h"
#include <string.h>
#include <stdlib.h>
#include "../SHVNative/natives.h"
#include "./WeaponCapture.h"
#include "./include.h"
#include <sstream>
CPlayerWeapon::CPlayerWeapon(const char* weaponName) {
	this->m_u64WeapHash = MISC::GET_HASH_KEY(weaponName);
	this->m_u64ModelHash = WEAPON::GET_WEAPONTYPE_MODEL(this->m_u64WeapHash);
}
CPlayerWeapon::CPlayerWeapon(CPlayerWeapon::Hash weaponHash) {
	this->m_u64WeapHash = weaponHash;
	this->m_u64ModelHash = WEAPON::GET_WEAPONTYPE_MODEL(this->m_u64WeapHash);
}

void CPlayerWeapon::AddWeaponComponent(const char* comp) {
	this->m_ComponentsOnGun.push_back(comp);
	scriptLogI("\n\tWeapon Comp: %s\n\tOn Weapon: %s", comp, this->GetName(WEAP_CAP));
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

std::string CPlayerWeapon::GetAllWeaponComponents() {
	std::stringstream buffer;
	for (const char* weapComponent : this->m_ComponentsOnGun) {
		buffer << weapComponent << std::endl;
	}
	return buffer.str();
}

std::vector<CPlayerWeapon::WeaponComponent>* CPlayerWeapon::GetAllWeaponComponentVec() {
	return &this->m_ComponentsOnGun;
}
