#include "CScaleform.h"
#include "../SHVNative/natives.h"
CScaleform::CScaleform(const char* scaleform, const char* scaleformbg, const char* scaleformfg)
{
	//Request operations cause fuck you!
	this->Scaleform = this->Request(scaleform);
	//if (scaleformbg != nullptr || strcmp(scaleformbg, "") == 0 || scaleformbg != 0) { // Todo: Fix because this fucking code doesn't work!
	//	this->Scaleform_BG = this->Request(scaleformbg);
	//	this->Scaleform_FG = this->Request(scaleformfg);
	//}
}
CScaleform::CScaleform(const char* scaleform) : // i wanna die./
CScaleform(scaleform, nullptr, nullptr)
{
}
int CScaleform::Request(const char* scaleform) {
	int temp_scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE(scaleform);
	while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(temp_scaleform)) {
		WAIT(0);
	}
	return temp_scaleform;
}
void CScaleform::LiteralStringPush(const char* string) {
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(string);
}

void CScaleform::PlayerNamePush(const char* string) {
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(string);
}

void CScaleform::IntegerPush(int x) {
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(x);
}

void CScaleform::FloatPush(float f) {
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(f);
}

void CScaleform::BoolPush(bool b) {
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(b);
}

void CScaleform::BeginMethod(const char* funcName) {
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->Scaleform, funcName);
}

void CScaleform::EndFunction() {
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}

int CScaleform::EndFunctionWithReturn() {
	return GRAPHICS::END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE();
}

bool CScaleform::IsScaleformReadyToReturn(int endfunctionhandle) {
	return GRAPHICS::IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(endfunctionhandle);
}

int CScaleform::GetReturnValInt(int endFunctionHandle) {
	return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(endFunctionHandle);
}

bool CScaleform::GetReturnValBool(int endfunctionHandle) {
	return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(endfunctionHandle);
}

const char* CScaleform::GetReturnValString(int endfunctionHandle) {
	return GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(endfunctionHandle);
}

void CScaleform::Draw(CVector2 drawPosition, CVector2 drawScale) {
	GRAPHICS::DRAW_SCALEFORM_MOVIE(this->Scaleform, drawPosition.x, drawPosition.y, drawScale.x, drawScale.y, 255, 255, 255, 255, 1);
}

void CScaleform::DrawBGFG() {
	GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(this->Scaleform_BG, this->Scaleform_FG, 255, 255, 255, 255);
}

void CScaleform::Draw3D(CVector3 drawPosition, CVector3 drawRotation, CVector3 drawScale, float p7, float sharpness, float p9, Any p13) {
	GRAPHICS::DRAW_SCALEFORM_MOVIE_3D(this->Scaleform, drawPosition.x, drawPosition.y, drawPosition.z, drawRotation.x, drawRotation.y, drawRotation.z, 0, 0, 0, drawScale.x, drawScale.y, drawScale.z, p13);
}

void CScaleform::Draw3DSolid(CVector3 drawPos, CVector3 drawRot, float p7, float p8, float p9, CVector3 drawScale, Any p13) {
	GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(this->Scaleform, drawPos.x, drawPos.y, drawPos.z, drawRot.x, drawRot.y, drawRot.z, p7, p8, p9, drawScale.x, drawScale.y, drawScale.z, p13);
}
