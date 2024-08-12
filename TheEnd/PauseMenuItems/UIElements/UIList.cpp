#include "UIList.h"
#include <cassert>
UIList::UIList(const CPauseMenuPage* pPage) {
	assert(pPage != nullptr, "UIList::UIList passed nullptr!");
}

void UIList::Draw() {
}

void UIList::SetSelection(int _selection) {
}

int UIList::GetSelection() {
	return 0;
}

int UIList::GetMaxSelections() {
	return 0;
}

UIList::ListItem* UIList::GetItem(int index) {
	if (index > this->GetMaxSelections()) {
		return nullptr;
	}
	return &m_Items[index]; // yes yes 
}
