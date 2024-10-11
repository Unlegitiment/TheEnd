#pragma once
#include"../../SHVNative/types.h"
class baseHeader {
protected:
	CVector2<float> fOffset;
public:
	baseHeader(const CVector2<float> offset);
	CVector2<float>& GetOffset();
	virtual void Draw() = 0;
};