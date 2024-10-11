#include "EnemyAI.h"
#include "../SHVNative/natives.h"
#include "../Game/CGameWorld.h"
#include "../Game/Objects/CPlayer.h"
void CMilitaryAI::SummonAllVehicles() {
	if (this->m_SummonedVehicles.size() > 0) {
		RemoveAllVehiclesInScene();
	}
	for (const auto& it : this->m_Vehicles) {
		Hash h = GetModelHashFromVehicle(it.first);
		STREAMING::REQUEST_MODEL(h);
		while (!STREAMING::HAS_MODEL_LOADED(h)) WAIT(0);
		auto vehicle = VEHICLE::CREATE_VEHICLE(h, it.second.x, it.second.y, it.second.z, it.second.h, 1, 0, 1);
		this->m_SummonedVehicles.push_back(vehicle);
		scriptLogI("Spawning Vehicle: %s", GetModelString(it.first));
	}
}
Hash CMilitaryAI::GetModelHashFromVehicle(eVehicle veh) {
	return MISC::GET_HASH_KEY(this->GetModelString(veh).c_str());
}
void CMilitaryAI::RemoveAllVehiclesInScene() {
	for (Vehicle& veh : this->m_SummonedVehicles) {
		VEHICLE::DELETE_VEHICLE(&veh);
	}
	this->m_SummonedVehicles.clear();
}
std::string CMilitaryAI::GetModelString(eVehicle veh) {
	switch (veh) {
	case MOC: return "trailerlarge";
	case CRUSADER: return "CRUSADER";
	case FIB: return "fbi";
	case BARRACKS: return "barracks";
	default:
		scriptLogE("Invalid object passed: %i", veh);
		return "";
	}
	return std::string();
}
std::vector<CMilitaryAI::eGovernmentEnemy> CMilitaryAI::GetModelsForEnemyType(eEnemyType e) {
	std::vector<eGovernmentEnemy> retVec;
	for (auto it : EnemyTypeToModel) {
		if (it.first == e) {
			retVec.push_back(it.second);
		}
	}
	return retVec;
}
void CMilitaryAI::GivePedWeaponBasedOnEnemyType(const sEnemyInfo& s) {
	if (!ENTITY::IS_ENTITY_A_PED(s.pedIndex)) {
		scriptLogE("Entity is not a ped!");
		return;
	}
	switch (s.enemyType) {
		case FED:
			WEAPON::GIVE_WEAPON_TO_PED(s.pedIndex, MISC::GET_HASH_KEY(FED_WEAPON), 120, 0, 1);
			break; 
		case MILITARY:
			WEAPON::GIVE_WEAPON_TO_PED(s.pedIndex, MISC::GET_HASH_KEY(MIL_WEAPON), 120, 0, 1);
			WEAPON::GIVE_WEAPON_TO_PED(s.pedIndex, MISC::GET_HASH_KEY("WEAPON_SMOKEGRENADE"), 25, 0, 0);
			break;
		case SUIT:
			WEAPON::GIVE_WEAPON_TO_PED(s.pedIndex, MISC::GET_HASH_KEY(SUIT_WEAPON), 120, 0, 1);
			break;
		default: scriptLogW("Invalid object passed: %i", s.enemyType); break;
	}
}
void CMilitaryAI::ActivateCombatOnPlayer(const sEnemyInfo& p) {
	TASK::TASK_COMBAT_PED(p.pedIndex, PLAYER::PLAYER_PED_ID(), 0, 16);
}
void CMilitaryAI::ClearDeadBodies() {
}
void CMilitaryAI::CleanupBody() {
}
void CMilitaryAI::SummonRandomPed(eEnemyType type, CVector3<float> pos) {
	auto PedModelIndex = this->GetModelsForEnemyType(type);
	int RandomPedIndex = MISC::GET_RANDOM_INT_IN_RANGE(0, PedModelIndex.size());
	eGovernmentEnemy GOV_ENTITY_TYPE = PedModelIndex[RandomPedIndex];
	Hash pedHash = ArmyEnumToModel(GOV_ENTITY_TYPE); // summon a randomized ped based on the enemy thing.
	STREAMING::REQUEST_MODEL(pedHash);
	scriptLogI("Spawning Ped: %i\n\t@%s\n\tEnemy Type: %i", pedHash, pos.toStr().c_str(), type);
	Ped p = PED::CREATE_PED(0, pedHash, pos.x, pos.y, pos.z, 273, 1, 0);
	this->m_SpawnedByPeds.push_back({GOV_ENTITY_TYPE, pedHash, type, p});
}
#include "../SHVNative/enums.h"
void CMilitaryAI::SetCombatAbility(const sEnemyInfo& p) {
	if (!ENTITY::IS_ENTITY_A_PED(p.pedIndex)) {
		scriptLogE("Object passed is not a Ped! \n\t\tCannot set combat ability for a non-ped!");
		return;
	}
	PED::SET_PED_COMBAT_ABILITY(p.pedIndex, 2); // CA_PROFESSIONAL
	PED::SET_PED_CAN_SWITCH_WEAPON(p.pedIndex, true);
	
	PED::SET_PED_FLEE_ATTRIBUTES(p.pedIndex, 0, false);
	PED::SET_PED_COMBAT_ATTRIBUTES(p.pedIndex, 46, true);
	PED::SET_PED_COMBAT_ATTRIBUTES(p.pedIndex, 60, true);
	PED::SET_PED_COMBAT_ATTRIBUTES(p.pedIndex, 13, true);
}
std::vector<CVector3<float>> CMilitaryAI::GetLocationsForSpawnPed(eEnemyType e) {
	std::vector<CVector3<float>> retVec;
	for (const sEnemyPosition& enemyPos : this->MilBasePositions) {
		if (enemyPos.EnemyTypeToSpawn == e) {
			retVec.push_back(enemyPos.Position);
		}
	}
	return retVec;
}
void CMilitaryAI::SummonArmyAI() { // that is much better/
	if (this->m_SpawnedByPeds.size() > 0) {
		RemoveAllPedsSummoned();
	}
	for (int enemyType = 0; enemyType < ENEMY_MAX; enemyType++) {
		for (const CVector3<float>& SpawnPos : GetLocationsForSpawnPed((eEnemyType)enemyType)) {
			SummonRandomPed((eEnemyType)enemyType, SpawnPos);
			
		}
	}
}
void CMilitaryAI::RemoveAllPedsSummoned() {
		for (sEnemyInfo& p : this->m_SpawnedByPeds) {
			PED::DELETE_PED(&p.pedIndex);
		}
		this->m_SpawnedByPeds.clear();
}
void CMilitaryAI::TriggerAI() {
	SummonArmyAI();
	for (int i = 0; i < this->m_SpawnedByPeds.size(); i++) {
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(this->m_SpawnedByPeds[i].pedIndex, this->RelationShipHash);
		GivePedWeaponBasedOnEnemyType(this->m_SpawnedByPeds[i]);
		ActivateCombatOnPlayer(this->m_SpawnedByPeds[i]);
	}
	SummonAllVehicles();


}
bool CMilitaryAI::AISpawnDecideCondition() {
	return WORLD->GetLocalPlayer()->GetAllInformationAboutPlayer()->m_vPlayerPosition.Dist({ -1922.2150f, 3749.8501f, -100.6458f }) < 11.0f;
}
Hash CMilitaryAI::ArmyEnumToModel(eGovernmentEnemy e) {
	switch (e) {
	case FBI_ARMOR:		return MISC::GET_HASH_KEY("s_m_m_fibsec_01");
	case BLACKOPS_01:	return MISC::GET_HASH_KEY("s_m_y_blackops_01");
	case BLACKOPS_02:	return MISC::GET_HASH_KEY("s_m_y_blackops_02");
	case BLACKOPS_03:	return MISC::GET_HASH_KEY("s_m_y_blackops_03");
	case MARINE_01:		return MISC::GET_HASH_KEY("s_m_m_marine_01");
	case MARINE_2:		return MISC::GET_HASH_KEY("s_m_m_marine_02");
	case MARINE_3:		return MISC::GET_HASH_KEY("s_m_y_marine_03");
	case FEMALE_AGENT:	return MISC::GET_HASH_KEY("a_f_y_femaleagent");
	case CIA_MALE_1:	return MISC::GET_HASH_KEY("s_m_m_ciasec_01");
	case HIGH_SEC:		return MISC::GET_HASH_KEY("s_m_m_highsec_01");
	case HIGH_SEC_2:	return MISC::GET_HASH_KEY("s_m_m_highsec_02");
	case HIGH_SEC_3:	return MISC::GET_HASH_KEY("u_m_m_jewelsec_01");
	case FIB_OFFICE:	return MISC::GET_HASH_KEY("s_m_m_fiboffice_01");
	case FIB_SUIT:		return MISC::GET_HASH_KEY("cs_fbisuit_01");
	case FIB_SUIT_2:	return MISC::GET_HASH_KEY("ig_fbisuit_01");
	case SWAT:			return MISC::GET_HASH_KEY("s_m_y_swat_01");
	default:			return -1;
	}
}

void CMilitaryAI::THROW_WEAPON_LOGIC(const sEnemyInfo& s) {
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(s.pedIndex,0);
	Ped p = 0;
	PED::GET_CLOSEST_PED(pos.x, pos.y, pos.z, 30.0f, 0, 0, &p, 0, 0, 1);
	if (p != NULL) {
		Vector3 targetCoord = ENTITY::GET_ENTITY_COORDS(p,0);
		TASK::TASK_THROW_PROJECTILE(s.pedIndex, targetCoord.x, targetCoord.y, targetCoord.z, 0, 1); // whatever scratch this for now. player might just get charged with aggressive ai
	}
}

CMilitaryAI::CMilitaryAI() {
	if (this->isRelationSetup == false) {
		PED::ADD_RELATIONSHIP_GROUP(this->m_RELGROUPMIL, &this->RelationShipHash);
		if (PED::DOES_RELATIONSHIP_GROUP_EXIST(this->RelationShipHash)) {
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(1, this->RelationShipHash, MISC::GET_HASH_KEY("ARMY"));
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(1, MISC::GET_HASH_KEY("ARMY"), this->RelationShipHash);
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(2, this->RelationShipHash, MISC::GET_HASH_KEY("COP"));
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(2, MISC::GET_HASH_KEY("COP"), this->RelationShipHash);
			scriptLogI("[REL_FM_GROUP] Relationship setup.");
		};
		this->isRelationSetup = true;
	}
}
