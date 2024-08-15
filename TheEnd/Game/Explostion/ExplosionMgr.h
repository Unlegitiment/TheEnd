#pragma once
#include <stack>
class CExplosion;
class CExplosionManager {
public:
	void PopExplosion();
	void PushExplosion(CExplosion& exp);
	void Update();
	
private:
	std::stack<CExplosion&> m_Exp;
};