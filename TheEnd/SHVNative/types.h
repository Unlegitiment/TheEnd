/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#pragma once

#include <windows.h>


typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
} Vector3;
#pragma pack(pop)
#include <math.h>
#include <string>
class CVector2 {
public:
	CVector2(float x, DWORD _paddingX_, float y, DWORD _paddingY_) :
		x(x),
		y(y),
		_paddingX_(_paddingX_),
		_paddingY_(_paddingY_)
	{
		
	}
	CVector2(float x, float y)
		:
		CVector2(x,0UL,y,0UL)
	{

	}
	float Dist(CVector2& other) {
		float xsub, ysub;
		xsub = other.x - this->x;
		ysub = other.y - this->y;
		float xsq, ysq;
		xsq = xsub * xsub;
		ysq = ysub * ysub;
		float tot = xsq + ysq;
		return static_cast<float>(sqrt(tot));
	}
	virtual std::string toStr() {
		return std::to_string(this->x) + " " + std::to_string(this->y);
	}
	void NormalizeScreen(float* locX, float* locY);
	//Warn this can give funky results.
	void  Normalize(float VAL, float MAX, float MIN) {

	}
	//CVector2 fromVector3(Vector3& const vec);
	CVector2 operator+(CVector2 const& other) {
		return CVector2(x + other.x, _paddingX_ + other._paddingX_, y + other.y, _paddingY_ + other._paddingY_);
	}
	CVector2 operator-(CVector2 const& other) {
		return CVector2(x - other.x, _paddingX_ - other._paddingX_, y - other.y, _paddingY_ - other._paddingY_);
	}


	float x;
	DWORD _paddingX_;
	float y;
	DWORD _paddingY_;
};

class CVector3 : public CVector2{
public:
	CVector3(float x, DWORD _paddingX_, float y, DWORD _paddingY_, float z, DWORD _paddingZ_)
		:
		CVector2(x, _paddingX_, y, _paddingY_),
		z(z),
		_paddingZ_(_paddingZ_)
	{

	}
	CVector3(float x, float y, float z) :
		CVector3(x, 0UL, y, 0UL, z, 0UL)
	{

	}
	CVector3(Vector3& structV3) :
		CVector3(structV3.x, structV3.y, structV3.z)
	{
	}
public:
	float Dist(CVector3& other) {
		float xsub, ysub, zsub;
		xsub = other.x - this->x;
		ysub = other.y - this->y;
		zsub = other.z - this->z;
		float xsq, ysq, zsq;
		xsq = xsub * xsub;
		ysq = ysub * ysub;
		zsq = zsub * zsub;
		float tot = xsq + ysq + zsq;
		return static_cast<float>(sqrt(tot));
	}
	Vector3 GetAsStruct() {
		return { x,_paddingX_, y, _paddingY_, z, _paddingZ_ };
	}
	std::string toStr() {
		return std::string(std::to_string(this->x) + " " + std::to_string(this->y) + " " + std::to_string(this->z) + " ");
	}
	float z;
	DWORD _paddingZ_;
private:
};
class CRGBA {
public:
	float r, g, b, a;
	CRGBA(float R, float G, float B, float A) :
		r(R),
		g(G),
		b(B),
		a(A)
	{

	}
	std::string toStr() {
		std::string red = std::to_string(r);
		std::string gre = std::to_string(g);
		std::string blu = std::to_string(b);
		std::string alp = std::to_string(a);
		return red + " " + gre + " " + blu + " " + alp;
	}
};
