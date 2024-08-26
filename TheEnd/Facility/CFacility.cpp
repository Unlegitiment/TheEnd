#include "CFacility.h"
#include "../SHVNative/natives.h"
CFacility::CFacility(CGameInteriorMgr* mgr) :
	m_pInteriorManager(mgr)
{
}
#define TIMER(INTERIORNAME) int lastUpdateInterior_##INTERIORNAME = 0;  int GetTimer_##INTERIORNAME(){return lastUpdateInterior_##INTERIORNAME; } void SetTimer_##INTERIORNAME(int _newTime){lastUpdateInterior_##INTERIORNAME = _newTime;}


struct sTimer {
	TIMER(FACILITY_REFRESH); // every day I get closer to dying to macros. and every day I want to die because of it.

};
/*
	Alright so For later we gotta do some stuff in relation to creating specialized interior classes. 
	Interior based classes shouldn't be too hard to work on however it could be with everything going through the CInteriorMgr class it might be
	So basically the call would be:
	sGameWorld::GetInstance()->GetInteriorManager()->GetFacility()->ActivateFacilitySkin(eFacilitySkinType);
	however with shortening and some type stuff we can shorten that call down.
	However the facility is one interior. Getting all interiors is harder. 
	We need some way to kinda have each of them self-identify as an Interior.
	Hmm This can be pretty tricky. 
	Because since these are specialized interiors The Interior Inheritance model should be:
	CInterior -> CInteriorEntitySet() -> CFacility.
	Or we can do an interface type and say:
	Not all interiors have components. 
	class IInterior{
		int m_iInteriorHandle; 
	}
	class IInteriorExtended : IInterior{
		struct sInteriorComponent{
			const char* ComponentName;
			int			ComponentColor;
			bool		isComponentActive;
		}
		std::vector<sInteriorComponent> m_AllInteriorComponents;
	}
	class CFacility : IInteriorExtended{
		bool forceUpdate;
		void Init(){
			m_AllInteriorComponents.push_back({"set_int_02_shell", 0, false});
			// Continue Initalization for Interior 
		}
		void SetForceInteriorUpdate(bool isInteriorInNeedOfUpdate); 
		bool GetIfUpdateIsNessicary();
		enum eFacilityComponent{
			FACILITY_SHELL = 0, // this corresponds with index above.
		}
		void ActivateComponentDetail(eFacilityComponent e, int color);
		void DeactivateComponentDetail(eFacilityComponent e);
		void Update(){ // we're just gonna lazy load this shit. its not really important for the Game to Update the interior every frame unless forceUpdate is entirely like required.

		}
		//Also cause its not really worth like check OHHH is this shit valid yes or no! we're just gonna elect to ignore it because if its not valid game already runs a check on that and defaults the value.
	};
	class CGameInteriorMgr{
		void Init(){
		//... other classes
			this->m_pFacility = cus_new(CFacility); // verify check
			this->pInteriorTimers = cus_new(sGameInteriorTimers); // check mate.
		}
		void Update(); // which this is gonna do the main work in this case for the whatever.
		CFacility* m_pFacility; // since this is just gonna either be a cus_new or a in general new. 
		//Since NOT everything needs to be updated every frame. We just effectively void it Until nessicary. Then we can update this crap. 
		struct sGameInteriorTimers{ // basically putting a bunch of stuff in the oven to cook and leaving the timer in a struct. 

			TIMER(FACILITY);
			TIMER(NIGHTCLUB);
			TIMER(PROG);
		}*pInteriorTimers;
	}



*/
void CFacility::SummonBase() {
	/*
	God I hate the Interior System in this game. I also wonder if you could Summon Lights that wouldn't get effected by the BLACKOUT state?
	I doubt it because I think id just set the blackout state anyways to die but idk.
	*/
	STREAMING::REQUEST_IPL("xm_x17dlc_int_placement"); // Facility IPL
}

void CFacility::SummonInteriorComponent(const char* m_component) {
	INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(this->InteriorID, m_component);
}

void CFacility::DesummonInteriorComponent(const char* m_component) {
	INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(this->InteriorID, m_component);
}

void CFacility::SetInteriorPropColor(const char* m_component, int color) {
	INTERIOR::SET_INTERIOR_ENTITY_SET_TINT_INDEX(this->InteriorID, m_component, color);
}

void CFacility::RefreshInterior() {
	INTERIOR::REFRESH_INTERIOR(this->InteriorID);
}

void CFacility::Default() {
	SummonInteriorComponent("set_int_02_decal_01");
	SummonInteriorComponent("set_int_02_lounge1");
	SummonInteriorComponent("set_int_02_cannon");
	SummonInteriorComponent("set_int_02_clutter1");
	SummonInteriorComponent("set_int_02_crewemblem");
	SummonInteriorComponent("set_int_02_shell");
	SummonInteriorComponent("set_int_02_security");
	SummonInteriorComponent("set_int_02_sleep");
	SummonInteriorComponent("set_int_02_trophy1");
	SummonInteriorComponent("set_int_02_paramedic_complete");
	SummonInteriorComponent("set_Int_02_outfit_paramedic");
	SummonInteriorComponent("set_Int_02_outfit_serverfarm");
	SetInteriorPropColor("set_int_02_decal_01", 1);
	SetInteriorPropColor("set_int_02_lounge1", 1);
	SetInteriorPropColor("set_int_02_cannon", 1);
	SetInteriorPropColor("set_int_02_clutter1", 1);
	SetInteriorPropColor("set_int_02_shell", 3);
	SetInteriorPropColor("set_int_02_security", 1);
	SetInteriorPropColor("set_int_02_sleep", 1);
	SetInteriorPropColor("set_int_02_trophy1", 1);
	SetInteriorPropColor("set_int_02_paramedic_complete", 1);
	SetInteriorPropColor("set_Int_02_outfit_paramedic", 1);
	SetInteriorPropColor("set_Int_02_outfit_serverfarm", 1);
	RefreshInterior();
};

