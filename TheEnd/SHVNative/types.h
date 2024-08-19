/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#pragma once

#include <windows.h>
#include "../Logger/CLoggerInstances.h"
#define Logger CLogger::GetInst()
#define netLogger CLogger::GetInst()->GetNetworkLogger()
#define scriptLogI(...) netLogger->LogInfo(INFO, true, __FUNCTION__,": " ,__VA_ARGS__)
#define scriptLogW(...) netLogger->LogInfo(WARN, true, __FUNCTION__,": " ,__VA_ARGS__)
#define scriptLogE(...) netLogger->LogInfo(ERROR2, true, __FUNCTION__,": " ,__VA_ARGS__)
#define scriptLogF(...) netLogger->LogInfo(FATAL, true, __FUNCTION__, ": ", __VA_ARGS__) // this should also trigger a script crash.
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
template<typename T>
class CVector2 {
public:
	CVector2(T x, DWORD _paddingX_, T y, DWORD _paddingY_) :
		x(x),
		y(y),
		_paddingX_(_paddingX_),
		_paddingY_(_paddingY_)
	{
		
	}
	CVector2(T x, T y)
		:
		CVector2(x,0UL,y,0UL)
	{

	}
	T Dist(CVector2& other) {
		T xsub, ysub;
		xsub = other.x - this->x;
		ysub = other.y - this->y;
		T xsq, ysq;
		xsq = xsub * xsub;
		ysq = ysub * ysub;
		T tot = xsq + ysq;
		return static_cast<T>(sqrt(tot));
	}
	virtual std::string toStr() {
		return std::to_string(this->x) + " " + std::to_string(this->y);
	}
	void NormalizeScreen(T* locX, T* locY);
	//Warn this can give funky results.
	void  Normalize(T VAL, T MAX, T MIN) {

	}
	//CVector2 fromVector3(Vector3& const vec);
	CVector2 operator+(CVector2 const& other) {
		return CVector2(x + other.x, _paddingX_ + other._paddingX_, y + other.y, _paddingY_ + other._paddingY_);
	}
	CVector2 operator-(CVector2 const& other) {
		return CVector2(x - other.x, _paddingX_ - other._paddingX_, y - other.y, _paddingY_ - other._paddingY_);
	}


	T x;
	DWORD _paddingX_;
	T y;
	DWORD _paddingY_;
};
template<typename T>
class CVector3 : public CVector2<T>{
public:
	CVector3(T x, DWORD _paddingX_, T y, DWORD _paddingY_, T z, DWORD _paddingZ_)
		:
		CVector2(x, _paddingX_, y, _paddingY_),
		z(z),
		_paddingZ_(_paddingZ_)
	{

	}
	CVector3(T x, T y, T z) :
		CVector3(x, 0UL, y, 0UL, z, 0UL)
	{

	}
	CVector3(Vector3& structV3) :
		CVector3(structV3.x, structV3.y, structV3.z)
	{
	}
public:
	T Dist(CVector3& other) {
		T xsub, ysub, zsub;
		xsub = other.x - this->x;
		ysub = other.y - this->y;
		zsub = other.z - this->z;
		T xsq, ysq, zsq;
		xsq = xsub * xsub;
		ysq = ysub * ysub;
		zsq = zsub * zsub;
		T tot = xsq + ysq + zsq;
		return static_cast<T>(sqrt(tot));
	}
	Vector3 GetAsStruct() {
		return { x,_paddingX_, y, _paddingY_, z, _paddingZ_ };
	}
	std::string toStr() {
		return std::string(std::to_string(this->x) + " " + std::to_string(this->y) + " " + std::to_string(this->z) + " ");
	}
	T z;
	DWORD _paddingZ_;
private:
};
template<typename T>
class CRGBA {
public:
	T r, g, b, a;
	CRGBA(T R, T G, T B, T A) :
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

template<typename T>
inline void CVector2<T>::NormalizeScreen(T* locX, T* locY) {
	int SCRX = 0;
	int SCRY = 0;
	GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&SCRX, &SCRY);
	*locX = this->x / SCRX;
	*locY = this->y / SCRY;
	return;
}
template<typename _Type>
class Singleton : protected _Type {
private:
	static _Type* Instance;
public:
	static _Type* GetInstance();
	static bool IsInitalized();
	static void Initalized();
	~Singleton();
};
template<typename _Type> _Type* Singleton<_Type>::Instance = nullptr;

template<typename _Type>
inline _Type* Singleton<_Type>::GetInstance() {
	if (!Singleton<_Type>::IsInitalized()) {
		Singleton<_Type>::Initalized();
	}
	return Singleton<_Type>::Instance;
}

template<typename _Type>
inline bool Singleton<_Type>::IsInitalized() {
	return Singleton<_Type>::Instance ? true : false;
}

template<typename _Type>
inline void Singleton<_Type>::Initalized() {
	Singleton<_Type>::Instance = new _Type();
	return;
}

template<typename _Type>
inline Singleton<_Type>::~Singleton() {
	delete this->Instance;
}
