#pragma once
#include "../SHVNative/types.h"
#include <bitset>
#include <vector>
class CDeluxo {
public:
	
	void Update();
	void Respawn();
	static bool DisableShopController();
	int& GetHandle() { return Handle; }
private:
	template<typename T> using Quaternion = CRGBA<T>;
	int& Handle;
	enum eDeluxoConfig {
		eDC_DISABLE_FLIGHT,
		eDC_ONLY_HOVER,
		eDC_SUMMON,
		eDC_MAX
	};
	CVector3<float> m_Pos;
	std::bitset<eDeluxoConfig::eDC_MAX> bits;
	std::vector<Quaternion<float>> m_SpawnablePos; // get all.



};