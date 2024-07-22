#pragma once
#include "../../ButtonDraw/CButtonUI.h"
class CBaseMenuItem : public CButtonUI{
public:
	CBaseMenuItem();
private:
	

};
class CBaseItemController {
public:
	CBaseItemController(CBaseMenuItem item);
	void HandleController(); 
private:

};
class CBaseItemView {
public:
	void Draw();
};