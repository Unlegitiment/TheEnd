#pragma once
#include <vector>
class CMission {
	struct MissionEntry {
		enum eType {
			VEHICLE,
			PED,
			INTERIOR,
			PICKUP,
		};
		bool isCleaned;
		eType m_Type;
		union {
			int* handle;
			const char* ipl;
		};
	};
	typedef std::vector<MissionEntry> Entities;
public:
	void RegisterInterior(const char* ipl);
	void RegisterVehicle(int* handle);
	void RegisterPed(int* handle);
	void RegisterPickup(int* handle);
	virtual void Update() = 0; // lol
	void Cleanup();
protected:
	Entities getAllEntities() { return m_AllRegistedEntities; }
private:
	Entities m_AllRegistedEntities;
};