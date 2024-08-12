#include "CMission.h"

void CMission::RegisterInterior(const char* ipl) {
	MissionEntry m_Entry = MissionEntry();
	m_Entry.m_Type = m_Entry.INTERIOR;
	m_Entry.ipl = ipl; // idk if this works lmao
	this->m_AllRegistedEntities.push_back(m_Entry);
}

void CMission::RegisterVehicle(int* handle) {
	MissionEntry m_Entry = MissionEntry();
	m_Entry.m_Type = m_Entry.VEHICLE;
	m_Entry.handle = handle;
	this->m_AllRegistedEntities.push_back(m_Entry);
}

void CMission::RegisterPed(int* handle) {
	MissionEntry m_Entry = MissionEntry();
	m_Entry.m_Type = m_Entry.PED;
	m_Entry.handle = handle;
	this->m_AllRegistedEntities.push_back(m_Entry);
}

void CMission::RegisterPickup(int* handle) {
	MissionEntry m_Entry = MissionEntry();
	m_Entry.m_Type = m_Entry.PICKUP; // im not sure how pickups work
	m_Entry.handle = handle;
	this->m_AllRegistedEntities.push_back(m_Entry);
}
#include "../SHVNative/natives.h"
void CMission::Cleanup() {
	for (MissionEntry curEntry : m_AllRegistedEntities) {
		if (curEntry.m_Type == curEntry.INTERIOR) {
			if (!STREAMING::IS_IPL_ACTIVE(curEntry.ipl)) {
				continue;
			}
			STREAMING::REMOVE_IPL(curEntry.ipl);
			curEntry.isCleaned = true;
		} else if (curEntry.m_Type == curEntry.PED) {
			PED::DELETE_PED(curEntry.handle);
			curEntry.isCleaned = true;
		}
		else if (curEntry.m_Type == curEntry.VEHICLE) {
			VEHICLE::DELETE_VEHICLE(curEntry.handle);
			curEntry.isCleaned = true;
		}
		else if (curEntry.m_Type == curEntry.PICKUP) {
			OBJECT::REMOVE_PICKUP(*curEntry.handle);
			OBJECT::DELETE_OBJECT(curEntry.handle);

		}
	}
}
