#include "CStatsCapture.h"
#include "CStat.h"
#include "../SHVNative/types.h"
void CStatCapture::InitAllStats() {
	this->m_AllStats.push_back(CStat("SP1_STAMINA"));
	scriptLogI("Initalizing Stats");
}
