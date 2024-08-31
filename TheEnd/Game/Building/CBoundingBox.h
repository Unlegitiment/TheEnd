#pragma once
#include "../../SHVNative/types.h"
class CBoundingBox {
public:
    CBoundingBox(CVector3<float> position, CVector3<float> size, Quaternion<float> rotation) {
        this->m_Position = position;
        this->m_Size = size;
        this->m_qRotation = rotation;
    }
	void DisplayBoundBox();
	bool isEntityInside(int entityHandle);
	bool isCoordinateInside(CVector3<float> m_Vector);
private:
    void Test(const CVector3<float>& boxPosition,
        const CVector3<float>& boxSize,
        const Quaternion<float>& boxRotation,
        CVector3<float>& min,
        CVector3<float>& max);
    __forceinline void RotatePoint(float& x, float& y, float& z, float rx, float ry, float rz) {
        // Convert degrees to radians
        float rxRad = rx * (3.14f / 180.0f);
        float ryRad = ry * (3.14f / 180.0f);
        float rzRad = rz * (3.14f / 180.0f);

        // Rotation around X-axis
        float yTemp = y * cos(rxRad) - z * sin(rxRad);
        float zTemp = y * sin(rxRad) + z * cos(rxRad);
        y = yTemp;
        z = zTemp;

        // Rotation around Y-axis
        float xTemp = x * cos(ryRad) + z * sin(ryRad);
        z = -x * sin(ryRad) + z * cos(ryRad);
        x = xTemp;

        // Rotation around Z-axis
        xTemp = x * cos(rzRad) - y * sin(rzRad);
        y = x * sin(rzRad) + y * cos(rzRad);
        x = xTemp;
    }
    CVector3<float> m_Size = { 0,0,0 };
    CVector3<float> m_Position = {0,0,0};
    Quaternion<float> m_qRotation = {0,0,0,0};
};