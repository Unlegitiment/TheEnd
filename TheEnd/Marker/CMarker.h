#pragma once
#include "../SHVNative/types.h"
#include "../Textures/CTXD.h"
class CMarker { // int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, BOOL bobUpAndDown, BOOL faceCamera, int p19, BOOL rotate, char* textureDict, char* textureName, BOOL drawOnEnts, BOOL p24
public:
	enum class eMarkerType {
		MarkerTypeUpsideDownCone = 0,
		MarkerTypeVerticalCylinder = 1,
		MarkerTypeThickChevronUp = 2,
		MarkerTypeThinChevronUp = 3,
		MarkerTypeCheckeredFlagRect = 4,
		MarkerTypeCheckeredFlagCircle = 5,
		MarkerTypeVerticleCircle = 6,
		MarkerTypePlaneModel = 7,
		MarkerTypeSymbolTXD = 8,
		MarkerTypeSymbolTXD2 = 9,
		MarkerTypeNumber0 = 10,
		MarkerTypeNumber1 = 11,
		MarkerTypeNumber2 = 12,
		MarkerTypeNumber3 = 13,
		MarkerTypeNumber4 = 14,
		MarkerTypeNumber5 = 15,
		MarkerTypeNumber6 = 16,
		MarkerTypeNumber7 = 17,
		MarkerTypeNumber8 = 18,
		MarkerTypeNumber9 = 19,
		MarkerTypeChevronUpx1 = 20,
		MarkerTypeChevronUpx2 = 21,
		MarkerTypeChevronUpx3 = 22,
		MarkerTypeHorizontalCircleFat = 23,
		MarkerTypeReplayIcon = 24,
		MarkerTypeHorizontalCircleSkinny = 25,
		MarkerTypeHorizontalCircleSkinny_Arrow = 26,
		MarkerTypeHorizontalSplitArrowCircle = 27,
		MarkerTypeDebugSphere = 28,
		MarkerTypeDollarSign = 29,
		MarkerTypeHorizontalBars = 30,
		MarkerTypeWolfHead = 31,
		MarkerTypeQuestionMark = 32,
		MarkerTypePlaneSymbol = 33,
		MarkerTypeHelicopterSymbol = 34,
		MarkerTypeBoatSymbol = 35,
		MarkerTypeCarSymbol = 36,
		MarkerTypeMotorcycleSymbol = 37,
		MarkerTypeBikeSymbol = 38,
		MarkerTypeTruckSymbol = 39,
		MarkerTypeParachuteSymbol = 40,
		MarkerTypeThruster = 41,
		MarkerTypeSawbladeSymbol = 42,
		MarkerTypeUnkown = 43
	};
	CMarker(eMarkerType type, CVector3<float> pos, CVector3<float> dir, CVector3<float> rot, CVector3<float> scale, CRGBA<float> rgba, bool bob, bool faceCam, int drawRot, bool rotate, CTxd* txd, bool drawOnEnter, bool p24);
	void Draw();
	//getters cause cringe
	eMarkerType getType();
	CVector3<float> getPos();
	CVector3<float> getDir();
	CVector3<float> getRot();
	CVector3<float> getScale();
	CRGBA<float>    getColor();
	bool	 getIfMarkerBobs();
	bool	 getIfMarkerFacesCam();
	bool	 getIfMarkerRotates();
	bool	 getIfMarkerDrawsOnEnter();
	int		 getDrawRotation();
	CTxd*    getTxd(); // can be null
protected:
	eMarkerType m_Type;
	CVector3<float> pos;
	CVector3<float> dir;
	CVector3<float> rotation;
	CVector3<float> scale;
	CRGBA<float> rgba;
	bool bob, faceCam, rotate, drawonEnt, p24;
	int drawRot;
	CTxd* texture; // nullptr

	//bool bob, bool faceCam, int drawRot, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnter, bool p24
};