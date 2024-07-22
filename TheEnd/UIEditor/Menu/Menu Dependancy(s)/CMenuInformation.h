#pragma once
#include "../../ButtonDraw/CButtonUI.h"
#include "./ArrowButton.h"
#include "../../../GenericList/CList.h"
class CMenuInfo {
public:
	CMenuInfo(); 
	void SetArrowBlocked();
private:
	CList<CArrowButton> buttonArrow;
	
};