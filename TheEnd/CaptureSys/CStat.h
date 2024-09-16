#pragma once
class CStat {
public:
	enum eCharacter {
		MICHAEL,
		FRANKLIN,
		TREVOR,
		MULTI_ZERO,
		MULTI_ONE,
		UNK
	};
private:
	const char* m_FullStatName;
	eCharacter m_CharacterThatStatBelongsTo = UNK;
	int StatType;
	static constexpr const char* SCRIPT_ = "stats_controller";
	char* EnumToString(eCharacter e);
public:
	CStat(const char* StatName);
	template<typename T = int>
	void ModifyStat(T _newStatVal);
	void Test();
	eCharacter DeduceCharacterFromStat(const char* statName);
};

