#include "CMissionMarker.h"
#include "../SHVNative/natives.h"
CMissionMarker::CMissionMarker(CVector3<float> position, CVector3<float> scale, CRGBA<float> color, CTxd& texture) : CMarker(CMarker::eMarkerType::MarkerTypeSymbolTXD, position, CVector3<float>{0,0,0}, CVector3<float>{0,0,0}, scale, color, false, true, 2, false, &texture, false,false)
{
}

void CMissionMarker::Draw() {
	CMarker::Draw();
}
