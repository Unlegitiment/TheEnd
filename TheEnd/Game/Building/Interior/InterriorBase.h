#pragma once
#include "../../../DataTypes/IndexedUSet.h"
#include "../../../SHVNative/types.h"
#include "../../../SHVNative/natives.h"
class CInteriorMgr;
// This class isn't used a lot. Likely for just the casino however its more for scope of what is contained inside of an interior.
class baseInterior {
	struct sIPLInfo {
		const char* ipl;
		bool isIPLActive; // local
		bool operator==(const sIPLInfo& other) const {
			return strcmp(this->ipl, other.ipl) == 0;
		}
	};
	struct sIPLInfo_Hash {
		size_t operator()(const sIPLInfo& ipl) const {
			return std::hash<const char*>()(ipl.ipl);
		}
	};
protected:
	struct sInteriorInformation {
		sInteriorInformation(const char* interiorName); // unique identifier would be nice.
		// Command based interactions
		bool m_bDoesInteriorComeFromEnableMP = false; // this can come from a list of actual things that get launched when ON_ENTER_MP gets called. 
		bool m_bDoesInteriorRequireOnlineLoad = false; // this is for launching most interiors in the game. 
		bool m_bIsInteriorAnOfflineInterior = false; // this is for launching non-online interiors. however is not nessicary
		bool m_bDoesEnableMPInteriorNeedExtraPlacement = false; // this is for loading additional IPLS including the Interior based ones. just a nullsub until a full additional ipl stuff gets added
		bool m_bDoesInteriorHaveItemSets = false; // this is once again likely for Cayo because of the Gold and stuff.
		bool m_bDoesInteriorHaveCustomPresets = false; // for stuff like the facility item placement stuff for shell etc.
		bool m_bIsBuilding = false; // for stuff like the casino where its actually an IPL or any Additions.
		bool m_bIsMapAddition = false; // For Bunker Locations;
		bool m_bIsNewMap = false; // For Full additions like Cayo Perico
		bool m_bDoesHaveCustomMap = false; // interior does have a custom map object. Call ActivateRadarForInterior(); 
		//State
		bool m_bHasFullInteriorLoaded = false;
		bool m_bIsInteriorAlreadyActive = false; // STREAMING::IS_IPL_ACTIVE; // I do really hate doing this shit.
		const char* m_strInteriorName;
		void ActivateRadarForInterior(const char* InteriorMiniName, CVector3<float> InteriorCentre) { // example function of how to use them.
			scriptLogI("[INTERIOR], Interior: ", m_strInteriorName, " Has Map Attempting Map Load. Passed Object: ", InteriorMiniName);
			HUD::SET_RADAR_AS_INTERIOR_THIS_FRAME(MISC::GET_HASH_KEY(InteriorMiniName), InteriorCentre.x, InteriorCentre.y, InteriorCentre.z, 1);
			this->m_bDoesHaveCustomMap = true;
		}
	};
	sInteriorInformation* GetState() { return &this->m_State; }
public:
	baseInterior(CInteriorMgr* mgr); // nullable
	void UpdateMgr();
	void PushIPL(const char* IPL);
	void Trigger();
	void Despawn();
	void RemoveIPL(int index);
	void RemoveIPL(const char* ipl);
	CInteriorMgr* GetManager();
private:
	CInteriorMgr* m_pManager;
	sInteriorInformation m_State;
	IndexedUSet<sIPLInfo, sIPLInfo_Hash> m_IPLS;
};