#pragma once
#include "../../SHVNative/types.h"
class CDoor {
	typedef unsigned long long Hash;
	typedef int DoorId;
	typedef float DoorAjarState;
public:
	void OpenDoor();
private:
	enum eDoorState {
		LOCKED_FRAME,
		UNLOCKED_FRAME,
		UNLOCKED_PERMA,
		LOCKED_PERMA,
	};
	bool isDoorOpen;
	bool isDoorAuto;
	float doorAutoRate; // interpolate between two points when in range
	DoorId ID;
	Hash DoorHash;
	Hash DoorName;
	CVector3 DoorLocation;
	DoorAjarState doorajar;
	eDoorState doorState;
};