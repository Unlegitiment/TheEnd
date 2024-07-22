#pragma once
#include "CMarker.h"
class CMissionMarker : public CMarker {
public:
	CMissionMarker(CVector3 position, CVector3 scale, CRGBA color, CTxd& texture); // Type is predetermined.
	void Draw();
private:

};