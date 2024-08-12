#pragma once
#include "../UIElement.h"
#include <vector>
#include "../Generic/MenuPage.h"

//	If we have usual UIList than all we are going to do is draw the items like a list however its gonna have to depend we might have to 
//	UILists We Have to determine the difference between a UIList and a PauseList. Likely PauseList will extend UIList because they both are of the same type.
//	That or we write a seperate version of UIList



class UIList : public UIElement<UIT_LIST> {
private:
	struct sListItem {
		char* m_Left;
		char* m_Right;
	};
	typedef sListItem ListItem;
	std::vector<ListItem> m_Items;
	CPauseMenuPage* m_pPage;
public:
	struct sPublicListItem {
		ListItem& m_item;
		CVector2 m_ItemLocation;
		CRGBA m_ItemColour;
		CRGBA m_ItemSelection;
	};
	UIList(const CPauseMenuPage* pPage);
	static void DrawItem(sPublicListItem& item);
	
	virtual void Draw();
	void SetSelection(int _selection); // I recommend setting this up when the page is swapped to.
	int GetSelection();
	int GetMaxSelections();
	ListItem* GetItem(int index);

};