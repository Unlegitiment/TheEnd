#include "MenuPage.h"
void CPauseMenuPage::Init(CPauseMenuPaginator* pOwner, CPauseMenuHeader* pHeader) {
	this->m_Header = pHeader;
	this->m_pMenuOwner = pOwner;
	m_bHasFocus = false;
}
void CPauseMenuPage::AddEntry(int index, PageEntry entry) {
	this->m_DataEntries.insert({index, entry});
}

void CPauseMenuPage::AddEntry(PageEntry entry) {
	std::vector<int> m_spacesallocated;
	for (std::map<int, PageEntry>::iterator it = m_DataEntries.begin(); it != m_DataEntries.end(); it++) {
		m_spacesallocated.push_back(it->first);
	}
	this->m_DataEntries.insert({m_spacesallocated[m_spacesallocated.size()] + 1, entry});
}

CPauseMenuPage::PageEntry* CPauseMenuPage::GetEntry(int key) {
	if (this->m_DataEntries.find(key) != this->m_DataEntries.end()) {
		return &this->m_DataEntries[key];
	} else {
		return nullptr;
	}
}

void CPauseMenuPage::ClearEntry(int key) {
	this->m_DataEntries.erase(key);
}

std::vector<CPauseMenuPage::PageEntry> CPauseMenuPage::getAllEntries() {
	std::vector<CPauseMenuPage::PageEntry> m_Entries;
	for (std::map<int, CPauseMenuPage::PageEntry>::const_iterator it = m_DataEntries.begin(); it != m_DataEntries.end(); it++) {
		m_Entries.push_back(it->second);
	}
	return m_Entries;
}

void CPauseMenuPage::SetPageHeader(CPauseMenuHeader* header) {
	this->m_Header = header;
	return;
}

CPauseMenuHeader* CPauseMenuPage::GetHeader() {
	return this->m_Header;
}

CRGBA<float> CPauseMenuPage::GetHighlightColor() {
	return this->highlightColor;
}

void CPauseMenuPage::SetHighlightColor(CRGBA<float> rgba) {
	this->highlightColor = rgba;
}

void CPauseMenuPage::LoseFocus() {
	m_bHasFocus = false;

}

bool CPauseMenuPage::HasFocus() {
	return m_bHasFocus;
}

void CPauseMenuPage::SetFocus(bool m_bnewfoc) {
	this->m_bHasFocus = m_bnewfoc;
}
#include "../../keyboard.h"
#include "../../UIEditor/TextDraw/Text.h"
void CPauseMenuPage::Update() {
	if (m_bHasFocus) {
		this->m_pMenuOwner->SetPaginatorFocus(false);
	}
	CTextUI(std::to_string(this->m_bHasFocus), { 0.1,0.1 }, { 240,240,240,255 }).Draw();
}

void CPauseMenuPage::DrawPage(CPauseMenuPage& page) {
	
}

CPauseMenuHeader CPauseMenuPage::GetDefaultHeader() {
	return CPauseMenuHeader("Grand Theft Auto V", "", "{date}", "{character}", "{money/info}");
}

int CPauseMenuPage::GetSelectionIndex() {
	return this->selection_index;
}

void CPauseMenuPage::SetSelectionIndex(int _index) {
	if (getAllEntries().size() < _index) {
		selection_index = 0;
		return;
	}
	selection_index = _index;
}
