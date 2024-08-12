#pragma once
class CDoor;
#include <vector>
class DoorController { //Don't make an instance based class so that everyone can have unique doorcontrollers!
private:
	std::vector<CDoor*> m_Doors;
	typedef unsigned long long Hash;
public:
	void AddDoorToSystem(CDoor* door); // we'll set the door name to the thing.
	void SetDoorAutomatic(CDoor* door, bool autoState, float fRate);
	void SetDoorAjarState(CDoor* door, float ajarState);
	int FindDoorAtLocation(float x,float y,float z, CDoor* out_door); // 2 = door does not exist at coords; 1 = door is not in system and 0 means no errors
	void ClearDoors();
	void Update(); // defer background systems to another thread.
};