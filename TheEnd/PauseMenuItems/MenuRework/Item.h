#pragma once
template<typename __Type> class CVector2;
class baseMenuItem {
public:
	virtual void Hover(const CVector2<float>&) = 0;
	virtual void Execute(const CVector2<float>&) = 0;
};