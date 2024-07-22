#pragma once
#include "../SHVNative/types.h"
class CTxd {
	const char* textureDict;
	const char* textureName;
public:
	CTxd(const char* dictionary, const char* name);
	void* operator new(size_t buffer);
	void Request();
	bool IsReady();
	const char* getDict();
	const char* getName(); 
	void Remove(); // Pops off stack calls SET_TEXTURE_AS_NO_LONGER_USED();
private:
};