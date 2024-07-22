#pragma once
#include "../UIBase.h"
#include "../Generic/MenuPage.h"
namespace UIType_List {
	typedef std::pair<const char*, const char*> ListItem;
	typedef std::vector<ListItem> ListItems;
}
using namespace UIType_List;
class CUIType_ItemList : CUIBase{
private:
	CPauseMenuPage* m_pPage;
	ListItems m_ListItems;
public:
	void Draw(int* selection);
	CPauseMenuPage* getPage();
	void setPage(CPauseMenuPage* page);
	void AddListItem(ListItem item);
	void ClearItems();
	ListItems GetAllItems();
	ListItem* GetItemAtIndex(int index);
};