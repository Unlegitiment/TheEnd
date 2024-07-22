#pragma once
#include "../SHVNative/types.h"
class CScaleform {
public:
	CScaleform(const char* scaleform, const char* scaleformbg, const char* scaleformfg);
	CScaleform(const char* scaleform);
	int Request(const char* scaleform);
	//Param Implementations
	void LiteralStringPush(const char* string);
	void PlayerNamePush(const char* string);
	void IntegerPush(int x);
	void FloatPush(float f);
	void BoolPush(bool b);
	//BeginFunction & EndFunctionss
	void BeginMethod(const char* funcName);
	void EndFunction();
	//End With Return
	int EndFunctionWithReturn();
	bool IsScaleformReadyToReturn(int endfunctionhandle);
	//Return
	int GetReturnValInt(int endFunctionHandle);
	bool GetReturnValBool(int endfunctionHandle);
	const char* GetReturnValString(int endfunctionHandle);
	//Draw Commands
	void Draw(CVector2 drawPosition, CVector2 drawScale); // 
	void DrawBGFG(); // fullscreen_mask
	void Draw3D(CVector3 drawPosition, CVector3 drawRotation, CVector3 drawScale, float p7, float sharpness, float p9, Any p13);
	void Draw3DSolid(CVector3 drawPos, CVector3 drawRot, float p7, float p8, float p9, CVector3 drawScale, Any p13);
private:
	int Scaleform, Scaleform_BG, Scaleform_FG; 
	
};