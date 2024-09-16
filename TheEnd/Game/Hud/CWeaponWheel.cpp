#include "CWeaponWheel.h"
#include "../../SHVNative/natives.h"
void CGameWeaponWheel::Show() {
	GRAPHICS::REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(19);
	while (!GRAPHICS::HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(19))WAIT(0);
	HUD::SHOW_HUD_COMPONENT_THIS_FRAME(19);
	
}

enum eSCRIPT_HUD_COMPONENT {
	HUD_DRUGS_PURSE_01 = 0,
	HUD_DRUGS_PURSE_02,
	HUD_DRUGS_PURSE_03,
	HUD_DRUGS_PURSE_04,
	HUD_MP_TAG_CASH_FROM_BANK,
	HUD_MP_TAG_PACKAGES,
	HUD_MP_TAG_CUFF_KEYS,
	HUD_MP_TAG_DOWNLOAD_DATA,
	HUD_MP_TAG_IF_PED_FOLLOWING,
	HUD_MP_TAG_KEY_CARD,
	HUD_MP_TAG_RANDOM_OBJECT,
	HUD_MP_TAG_REMOTE_CONTROL,
	HUD_MP_TAG_CASH_FROM_SAFE,
	HUD_MP_TAG_WEAPONS_PACKAGE,
	HUD_MP_TAG_KEYS,
	HUD_MP_VEHICLE,
	HUD_MP_VEHICLE_HELI,
	HUD_MP_VEHICLE_PLANE,
	HUD_PLAYER_SWITCH_ALERT,
	HUD_MP_RANK_BAR,
	HUD_DIRECTOR_MODE,
	HUD_CHIP,						//Casino chips display
	HUD_CHIP_CHANGE,				//Casino chips value change


	HUD_MP_TAG_LARGE_PACKAGES,//Not listed in the code side enum
	HUD_MP_TAG_GANG_CEO,//Not listed in the code side enum
	HUD_MP_TAG_GANG_BIKER//Not listed in the code side enum

};