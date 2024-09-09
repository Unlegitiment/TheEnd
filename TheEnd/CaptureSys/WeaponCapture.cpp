#include "WeaponCapture.h"
#include "../SHVNative/natives.h"
#include "../SHVNative/enums.h"
#include <fstream>
#include <vector>
#include "./PlayerWeapon.h"
void CWeaponCapture::Capture() {
	for (auto it = this->GetMap()->begin(); it != GetMap()->end(); it++) {
		if (WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), it->first, 0)) {
			CPlayerWeapon weap = CPlayerWeapon(it->first);
			//The weapon components are just purely horrible for accessing them outside of the game binary. 
			// as such we're just gonna drop all weapon components as soon as we give the weapon back because its REALLY annoying to get components.
			int ammClip = 0;
			WEAPON::GET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), it->first, &ammClip);
			weap.SetAmmoInClip(ammClip);
			weap.SetAmmo(WEAPON::GET_AMMO_IN_PED_WEAPON(PLAYER::PLAYER_PED_ID(), it->first));
			this->m_CapturedWeapons.push_back(weap);
			if (it->first == 2725352035) {
				continue; // so we don't remove the player's fists lul
			}
			WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), it->first);
			scriptLogI("\n\tWeaponName: ", weap.GetName(this));
		}
	}
	this->isCaptured = true;
}

void CWeaponCapture::Reset() {
	
}

void CWeaponCapture::Revert() {
	for (auto it = this->GetCaptured()->begin(); it != GetCaptured()->end(); it++) {
		CPlayerWeapon* weap = const_cast<CPlayerWeapon*>(&(*it));
		WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weap->GetWeapon(), weap->GetAmmo(), 0, 0);
		WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), weap->GetWeapon(), weap->GetAmmoInClip());
	}
}

void CWeaponCapture::Delete() {
}
/*
Reason for Components being annoying.

Basically right you have a component of a weapon. Normally this is just memory associated with an object however in the case of the Scripts you have to have a specific Weapons accessor.

What this means is that the Weapon is unique for every weapon not just the player given weapons. 

So there is no WAY to get all Weapon Components Associated with a Weapon without effectively running through every afformentioned weapon component. 

I mean you can optimize it so that on every tick it sees that oh we're looking for a weapon component with such index like you after "COMPONENT_*"
* is replaced for AP
we look for any beginning with AP and that could match with AP Pistol.

OR you create a data structure for every single component with a weapon. basically an std::vector

however its specific to the weapon.

Which sucks as well.

So either way you lose. 

I'm fine with like "creating" these but there is no way in hell thats like good. 

I'd rather die anyways. So I'd just give the weapon back without components.

Thanks R* I love weapons.

You could have just defined it as 
	COMPONENT_EXTENDED_CLIP
	COMPONENT_EXTENDED_BARREL1
	COMPONENT_EXTENDED_BARREL2
	COMPONENT_EXTENDED_BARREL3
	COMPONENT_EXTENDED_BARREL4 
	but no we've decided to have specific components for each weapon.

	Just take the weapon as context into the equation and see if that component is valid.

	This would also work because then you could just return if a weapon has a component  and the array would be like a quarter of the size.

	Tints/Colors also shouldn't be weapon components by this definition. 

	A Component I see is like a barrel your tint should be like how you do with the interiors and effectively just have a color index. where 0 is that the tint doesn't exist and 1...inf is the definition of the Tint Color and whatever.

	Xoxo idk why y'all didn't do it like this.
*/