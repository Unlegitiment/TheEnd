#pragma once
#include <vector>
class CStat;
class CStatCapture {
public:
	void InitAllStats();

private:
	std::vector<CStat> m_AllStats;
};
/*
	GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(GAMEPLAY::GET_HASH_KEY("stats_controller"));
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_SPECIAL_ABILITY_UNLOCKED"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_STAMINA"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_STEALTH_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_LUNG_CAPACITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_FLYING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_SHOOTING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_STRENGTH"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP0_WHEELIE_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_SPECIAL_ABILITY_UNLOCKED"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_STAMINA"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_STEALTH_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_LUNG_CAPACITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_FLYING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_SHOOTING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_STRENGTH"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP1_WHEELIE_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_SPECIAL_ABILITY_UNLOCKED"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_STAMINA"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_STEALTH_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_LUNG_CAPACITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_FLYING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_SHOOTING_ABILITY"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_STRENGTH"), 100, true);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("SP2_WHEELIE_ABILITY"), 100, true);

*/