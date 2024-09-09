#pragma once
class CPlayerWeapon;
class CPlayerWeaponComponent {
public:
	CPlayerWeaponComponent(CPlayerWeapon* ownerWeapon, const char* componentName);
	
private:
	void SetComponentInformation(const char* componentName);
	unsigned long long componentHash;

};