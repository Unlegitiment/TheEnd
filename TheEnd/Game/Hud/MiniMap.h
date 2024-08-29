#pragma once
#include "../../SHVNative/types.h"
class CMinimap {
private:
	bool m_bIsMinimapActive;
public:
	CMinimap();
	void Init();
	void Update();
	void SetMinimapActive(bool active);
	bool IsMiniMapActive();
};

typedef Singleton<CMinimap> sMiniMap;
#define MINIMAP sMiniMap::GetInstance()