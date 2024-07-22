#pragma once
#include "../../GenericList/CList.h"
#include "./Menu Dependancy(s)/MenuHeader.h"
#include "MenuItems/CMenuItem.h"
#include "../ButtonDraw/CButtonUI.h"
#define _BLIST_ CList<CBaseMenuItem> 
class CMenuUI {
public:
	CMenuUI();
	_BLIST_ GetList();
	CMenuHeader& GetHeader(); 

private:
	CMenuHeader& header;
	_BLIST_ _bList_;
};
class CMenuCntrllr {
public:
	void AddButton(CButtonUI _button);
	CButtonUI GetButtonAtIndex(int index);
	bool IsIndexValid(int index);
private:

};
#undef _BLIST_