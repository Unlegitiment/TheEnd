#pragma once
#include "../../SHVNative/types.h"
class CBoundingBox {
	void DisplayBoundBox();
	bool isEntityInside(int entityHandle);
	bool isCoordinateInside(CVector3<float> m_Vector);
private:
	float m_fLength, m_fWidth, m_fHeight;
	CVector3<float> m_Position;
};