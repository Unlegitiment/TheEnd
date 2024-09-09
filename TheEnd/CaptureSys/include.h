#pragma once
#include "./PlayerWeapon.h"
#include "./WeaponCapture.h"
#include "../SHVNative/types.h"
typedef Singleton<CWeaponCapture> __sWeaponCapture;
#define WEAP_CAP __sWeaponCapture::GetInstance()