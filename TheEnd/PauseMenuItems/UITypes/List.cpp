#include "List.h"
#include "../../UIEditor/TextDraw/Text.h"
#include "../../UIEditor/BoxDraw/CBoxUI.h"
void CUIType_ItemList::Draw(int *selection) {
    for (int i = 0; i < m_ListItems.size(); i++) {
        ListItem curItem = m_ListItems[i];
        CVector2 baseTextVector = { 0.0,0.0 };
        CBox selectionBox = CBox(baseTextVector, { 5,5,5,255 }, 0.1f, 0.05f); // oke
        // Find the base Vector of which they draw;
        // So as well we need to know some basic stuff;
        CTextUI ltext = { curItem.first, {baseTextVector.x, baseTextVector.y + 0.02f + (0.05f * i)}, {240,240,240,255} };
        CTextUI rtext = { curItem.second, {0.0f,0.0f}, {240,240,240,255} }; // this is gonna store stuff about the right sided text. 
        //These all generally depend on various statements however POOL size might get effected here which is not totally nice. 
        //Also with all these draw calls and the fact that rText is another text object that means 2 text objects per box
        //2 * n ( n being number of ui elements ) is probably not good because we already draw a quite extensive UI with just the regular stuff alone.
        //


    }
}

CPauseMenuPage* CUIType_ItemList::getPage() {
    return this->m_pPage;
}

void CUIType_ItemList::setPage(CPauseMenuPage* page) {
    if (page != nullptr) {
        this->m_pPage = page;
    }
    return;
}

void CUIType_ItemList::AddListItem(ListItem item) {
    this->m_ListItems.push_back(item);
}

void CUIType_ItemList::ClearItems() {
    this->m_ListItems.clear();
}

ListItems CUIType_ItemList::GetAllItems() {
    return this->m_ListItems;
}

ListItem* CUIType_ItemList::GetItemAtIndex(int index) {
    if (index > this->m_ListItems.size()) {
        return nullptr;
    }
    return &this->m_ListItems[index];
}
