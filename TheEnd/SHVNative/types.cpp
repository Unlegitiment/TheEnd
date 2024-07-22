#include "types.h"
#include "../SHVNative/natives.h"
void CVector2::NormalizeScreen(float* locX, float* locY)
{
	int SCRX = 0;
	int SCRY = 0;
	GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&SCRX, &SCRY);
	*locX = this->x / SCRX;
	*locY = this->y / SCRY;
	return;
}
