#include "CStat.h"
#include "string.h"
#include <string>
#include "../SHVNative/natives.h"
#include "../Scripts/CDisable.h"
CStat::CStat(const char* StatName) : m_FullStatName(StatName){
    this->m_CharacterThatStatBelongsTo = DeduceCharacterFromStat(m_FullStatName);
}
char* CStat::EnumToString(eCharacter e) {
    if (e == MICHAEL) {
        return "MICHAEL";
    } else if (e == FRANKLIN) {
        return "FRANKLIN";
    } else if (e == TREVOR) {
        return "TREVOR";
    } else if (e == MULTI_ZERO) {
        return "MULTI_ZERO";
    } else if (e == MULTI_ONE) {
        return "MULTI_ONE";
    } else {
        return "UNKNOWN";
    }
}
template<typename T>
void CStat::ModifyStat(T _newStatVal) {
    MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(SCRIPT_);
    WAIT(50);
    STATS::STAT_SET_INT(MISC::GET_HASH_KEY(m_FullStatName), _newStatVal, 1);
    scriptLogI("Setting stat: ", m_FullStatName, " to ", _newStatVal, " Character: ", EnumToString(this->m_CharacterThatStatBelongsTo));
    int StatVal = -1;
    STATS::STAT_GET_INT(MISC::GET_HASH_KEY(m_FullStatName), &StatVal, -1);
    scriptLogI("StatsVal: ", StatVal);
    STATS::STAT_GET_INT(MISC::GET_HASH_KEY(m_FullStatName), &StatVal, -1);
    scriptLogI("StatsVal: ", StatVal);
}

CStat::eCharacter CStat::DeduceCharacterFromStat(const char* statName) {
    char firstthree[4] = { 0 };
    strncpy_s(firstthree, statName, 3);
    firstthree[3] = '\0';
    
    if (strcmp(firstthree, "SP0") == 0) {
        return MICHAEL;
    } else if (strcmp(firstthree, "SP1") == 0) {
        return FRANKLIN;
    } else if (strcmp(firstthree, "SP2") == 0) {
        return TREVOR;
    } else if (strcmp(firstthree, "MP0") == 0) {
        return MULTI_ZERO;
    } else if(strcmp(firstthree, "MP1") == 0) {
        return MULTI_ONE;
    } else {
        return UNK;
    }
}

void CStat::Test() {
    this->ModifyStat(0);
}
