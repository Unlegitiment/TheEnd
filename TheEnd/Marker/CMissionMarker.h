#pragma once
#include "CMarker.h"
class CMissionMarker : public CMarker {
public:
	CMissionMarker(CVector3<float> position, CVector3<float> scale, CRGBA<float> color, CTxd& texture); // Type is predetermined.
	void Draw();
private:

};