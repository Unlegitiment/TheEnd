#include "CBoundingBox.h"
#include "../../SHVNative/natives.h"
void CBoundingBox::DisplayBoundBox() {
	const CRGBA boxrgba = CRGBA(0, 255, 0, 255);
	CVector3<float> mCornerPos[2] = { {0,0,0},{0,0,0} };
	
	GRAPHICS::DRAW_LINE(0,0,0,0,0,0,boxrgba.r,boxrgba.g,boxrgba.b,boxrgba.a);
	GRAPHICS::DRAW_POLY(100,100,100,200,200,100,300,300,100,255,0,0,255);
}
