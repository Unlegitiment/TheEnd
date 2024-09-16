#pragma once
#include <vector>
#include "../SHVNative/types.h"
class CMilitaryAI {
public:
public: // Vehicles for Scene. Eventually push to CScriptScene
	enum eVehicle {
		FIB, 
		BARRACKS,
		CRUSADER,
		MOC
	};
	struct sVector4 { // basic impl for this use-case in future make just struct with two positional vectors.
		float x, y, z, h;
	};
	float ConvertYaw(float fYaw) {
		return (fYaw < 0) ? fYaw + 360 : fYaw;
	}
	std::vector<Vehicle> m_SummonedVehicles;
	std::vector<std::pair<eVehicle, sVector4>> m_Vehicles = {
		{FIB, {-2090.108, 3246.5562, 32.4701,		ConvertYaw(-171.4678)}},
		{FIB, {-2084.306, 3241.0637, 32.4701,		ConvertYaw(32.4701)}},
		{BARRACKS, {-2077.260f, 3261.1331f,	34.4963,ConvertYaw(-2.6595)}},
		{CRUSADER, {-2082.081, 3255.6082, 32.3305,	ConvertYaw(12.4066)}},
		{CRUSADER, {-2080.362, 3248.9880, 32.3305,	ConvertYaw(-60.7376)}},
		{MOC, {-2069.471, 3275.2271, 33.4963,		ConvertYaw(-53.1141)}}
	};
	void SummonAllVehicles();
	Hash GetModelHashFromVehicle(eVehicle veh);
	std::string GetModelString(eVehicle veh);
	void RemoveAllVehiclesInScene();
public: // default AI for Military.
	static constexpr const char* m_RELGROUPMIL = "THEEND_BASE_RESPECT";
	bool isRelationSetup = false;
	Hash RelationShipHash = 0;
	enum eGovernmentEnemy {
		NO_ENEMY,
		//mil
		BLACKOPS_01,	// s_m_y_blackops_01
		BLACKOPS_02,	// s_m_y_blackops_02
		BLACKOPS_03,	// s_m_y_blackops_03
		MARINE_01,		// s_m_m_marine_01
		MARINE_2,		// s_m_m_marine_02
		MARINE_3,		// s_m_y_marine_03
		SWAT,			// s_m_y_swat_01		
		//cia/fbi base
		FBI_ARMOR,		// s_m_m_fibsec_01
		FEMALE_AGENT,	// a_f_y_femaleagent
		CIA_MALE_1,		// s_m_m_ciasec_01
		//SUITs
		HIGH_SEC,		// s_m_m_highsec_01
		HIGH_SEC_2,		// s_m_m_highsec_02
		HIGH_SEC_3,		// u_m_m_jewelsec_01
		FIB_OFFICE,		// s_m_m_fiboffice_01
		//FIB_OFFICE_2,	// s_m_m_fiboffice_02
		FIB_SUIT,		// cs_fbisuit_01
		FIB_SUIT_2,		// ig_fbisuit_01
		GOVERNMENT_AI_MAX
	};
	enum eEnemyType {
		MILITARY,
		FED,
		SUIT,
		ENEMY_MAX
	};
	struct sEnemyPosition {
		CVector3<float> Position;
		eEnemyType EnemyTypeToSpawn;
	};
	static constexpr const char* SUIT_WEAPON = "WEAPON_APPISTOL";
	static constexpr const char* FED_WEAPON = "WEAPON_SMG";
	static constexpr const char* MIL_WEAPON = "WEAPON_CARBINERIFLE";
	struct sEnemyInfo {
		eGovernmentEnemy enemySkin;
		Hash enemyHash;
		eEnemyType enemyType;
		int pedIndex;
	};
	std::vector<sEnemyInfo> m_SpawnedByPeds;
	std::vector<std::pair<eEnemyType, eGovernmentEnemy>> EnemyTypeToModel{
		{ MILITARY, BLACKOPS_01 },
		{ MILITARY, BLACKOPS_02 },
		{ MILITARY, BLACKOPS_03 },
		{ MILITARY, MARINE_01 },
		{ MILITARY, MARINE_2 },
		{ MILITARY, MARINE_3 },
		{ MILITARY, SWAT },
		{ FED, FBI_ARMOR },
		{ FED, FEMALE_AGENT},
		{ FED, CIA_MALE_1},
		{ SUIT, HIGH_SEC},
		{ SUIT, HIGH_SEC_2},
		{ SUIT, HIGH_SEC_3},
		{ SUIT, FIB_OFFICE},
		//{ SUIT, FIB_OFFICE_2},
		{ SUIT, FIB_SUIT},
		{ SUIT, FIB_SUIT_2},
	};
	std::vector<eGovernmentEnemy> GetModelsForEnemyType(eEnemyType e);
	std::vector<sEnemyPosition> MilBasePositions{
		//Military
		{{-2073.658, 3241.1997, 33.1103}, MILITARY},
		{{-2074.128, 3250.3806, 33.1103}, MILITARY},
		{{-2074.897, 3249.5276, 33.1103}, MILITARY},
		{{-2078.222, 3247.1472, 33.1103}, MILITARY},
		{{-2072.575, 3259.8496, 33.1103}, MILITARY},
		{{-2074.526, 3254.6035, 33.1103}, MILITARY},
		{{-2080.185, 3257.2207, 33.1103}, MILITARY},
		{{-2079.411, 3252.4751, 33.1103}, MILITARY},
		{{-2084.430, 3244.6382, 33.1103}, MILITARY},
		//GOV/FIB/IAA
		{{-2079.148, 3254.8464, 33.1103}, SUIT},
		{{-2079.817, 3254.1040, 33.1103}, SUIT},
		{{-2083.343, 3252.0232, 33.1103}, SUIT},
		{{-2083.453, 3250.7783, 33.1103}, SUIT},

		{{-2090.457, 3241.1858, 33.1103}, FED},
		{{-2089.635, 3240.9778, 33.1103}, FED},
		{{-2088.026, 3240.4382, 33.1103}, FED},
		{{-2087.320, 3239.5317, 33.1103}, FED},
	};
	void GivePedWeaponBasedOnEnemyType(const sEnemyInfo& s);
	void ActivateCombatOnPlayer(const sEnemyInfo& p);
	void ClearDeadBodies();
	void CleanupBody();
	void SummonRandomPed(eEnemyType type, CVector3<float> pos);
	void SetCombatAbility(const sEnemyInfo& p);
	std::vector<CVector3<float>> GetLocationsForSpawnPed(eEnemyType e);
	void SummonArmyAI();
	void RemoveAllPedsSummoned();
	void TriggerAI(); // activates enemy player targetting.
	bool AISpawnDecideCondition();
	int m_iLastSpawnTime = 0;
	float m_fSpawnLimiterRadius = 11.f;
	bool m_bCanEnemiesSpawn = true;
	bool m_bShouldEnemiesSpawn = false;
	CVector3<float> m_vSpawnPoint{ 0,0,0 };
	Hash ArmyEnumToModel(eGovernmentEnemy e);
	void THROW_WEAPON_LOGIC(const sEnemyInfo& s);
	CMilitaryAI();
};