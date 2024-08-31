#define NOMINMAX
#include "CBoundingBox.h"
#include "../../SHVNative/natives.h"
void CBoundingBox::DisplayBoundBox() {
        
        // Calculate half-dimensions
        float halfWidth = this->m_Size.x / 2.0f;
        float halfHeight = this->m_Size.y / 2.0f;
        float halfDepth = this->m_Size.z / 2.0f;

        // Define vertices of the box
        float vertices[8][3] = {
            {this->m_Position.x - halfWidth, this->m_Position.y - halfHeight, this->m_Position.z - halfDepth},
            {this->m_Position.x + halfWidth, this->m_Position.y - halfHeight, this->m_Position.z - halfDepth},
            {this->m_Position.x + halfWidth, this->m_Position.y + halfHeight, this->m_Position.z - halfDepth},
            {this->m_Position.x - halfWidth, this->m_Position.y + halfHeight, this->m_Position.z - halfDepth},
            {this->m_Position.x - halfWidth, this->m_Position.y - halfHeight, this->m_Position.z + halfDepth},
            {this->m_Position.x + halfWidth, this->m_Position.y - halfHeight, this->m_Position.z + halfDepth},
            {this->m_Position.x + halfWidth, this->m_Position.y + halfHeight, this->m_Position.z + halfDepth},
            {this->m_Position.x - halfWidth, this->m_Position.y + halfHeight, this->m_Position.z + halfDepth}
        };

        // Rotate vertices
        for (int i = 0; i < 8; ++i) {
            RotatePoint(vertices[i][0], vertices[i][1], vertices[i][2], m_qRotation.x, m_qRotation.y, m_qRotation.z);
        }

        // Draw the edges of the box
        auto drawLine = [](float* v1, float* v2) {
            GRAPHICS::DRAW_LINE(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], 255, 0, 0, 255);
            };

        // Bottom face
        drawLine(vertices[0], vertices[1]);
        drawLine(vertices[1], vertices[2]);
        drawLine(vertices[2], vertices[3]);
        drawLine(vertices[3], vertices[0]);

        // Top face
        drawLine(vertices[4], vertices[5]);
        drawLine(vertices[5], vertices[6]);
        drawLine(vertices[6], vertices[7]);
        drawLine(vertices[7], vertices[4]);

        // Vertical edges
        drawLine(vertices[0], vertices[4]);
        drawLine(vertices[1], vertices[5]);
        drawLine(vertices[2], vertices[6]);
        drawLine(vertices[3], vertices[7]);
	const CRGBA boxrgba = CRGBA(0, 255, 0, 255);
	CVector3<float> mCornerPos[2] = { {0,0,0},{0,0,0} };
}

bool CBoundingBox::isEntityInside(int entityHandle) {
    if (!ENTITY::IS_AN_ENTITY(entityHandle)) {
        scriptLogW("Not an entity! Passed: ", entityHandle);
        return false; 
    }
    CVector3<float> entityPosition = ENTITY::GET_ENTITY_COORDS(entityHandle, 0);
    return isCoordinateInside(entityPosition);
}

bool CBoundingBox::isCoordinateInside(CVector3<float> m_Vector) {
    CVector3<float> min = { 0,0,0 }; // just for now
    CVector3<float> max = { 0,0,0 };
    Test(this->m_Position, this->m_Size, this->m_qRotation, min, max);
    // Translate the object coordinates relative to the bounding box center
    float translatedX = m_Vector.x - (min.x + max.x) / 2.0;
    float translatedY = m_Vector.y - (min.y + max.y) / 2.0;
    
    // Rotate the translated coordinates using the negative rotation angle
    float rotatedX = translatedX * cos(-this->m_qRotation.x) - translatedY * sin(this->m_qRotation.x);
    float rotatedY = translatedX * sin(this->m_qRotation.x) + translatedY * cos(this->m_qRotation.x);
    
    // Calculate the half-width and half-height of the rotated bounding box
    float halfWidth = (max.x - min.x) / 2.0;
    float halfHeight = (max.y - min.y) / 2.0;
    
    // Check if the rotated coordinates are within the half-width and half-height
    if (rotatedX >= -halfWidth && rotatedX <= halfWidth &&
        rotatedY >= -halfHeight && rotatedY <= halfHeight) {
        return true; // Object is inside the rotated bounding box
    }
    
    return false; // Object is outside the rotated bounding box
}

void CBoundingBox::Test(const CVector3<float>& boxPosition,
    const CVector3<float>& boxSize,
    const Quaternion<float>& boxRotation,
    CVector3<float>& min,
    CVector3<float>& max) {
    CVector3<float> halfSize = boxSize * 0.5f;

    // Local space corners of the box
    CVector3<float> corners[8] = {
        {-halfSize.x, -halfSize.y, -halfSize.z},
        { halfSize.x, -halfSize.y, -halfSize.z},
        {-halfSize.x,  halfSize.y, -halfSize.z},
        { halfSize.x,  halfSize.y, -halfSize.z},
        {-halfSize.x, -halfSize.y,  halfSize.z},
        { halfSize.x, -halfSize.y,  halfSize.z},
        {-halfSize.x,  halfSize.y,  halfSize.z},
        { halfSize.x,  halfSize.y,  halfSize.z}
    };

    // Transform corners to world space
    CVector3<float> transformedCorners[8]{ {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} };
    for (int i = 0; i < 8; ++i) {
        transformedCorners[i] = boxPosition + boxRotation.Rotate(corners[i]);
    }

    // Initialize min and max with the first corner
    min = max = transformedCorners[0];

    // Find the minimum and maximum values along each axis
    for (int i = 1; i < 8; ++i) {
        min.x = std::min(min.x, transformedCorners[i].x);
        min.y = std::min(min.y, transformedCorners[i].y);
        min.z = std::min(min.z, transformedCorners[i].z);

        max.x = std::max(max.x, transformedCorners[i].x);
        max.y = std::max(max.y, transformedCorners[i].y);
        max.z = std::max(max.z, transformedCorners[i].z);
    }
}
