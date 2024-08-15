#pragma once
#include "./MenuPaginator.h"
#include <vector>
#include <map>
#include "./PauseMenuHeader.h"
class CPauseMenuPage {
public:
	struct PageEntry {
		char leftDataEntry[64]; // woo
		char rightDataEntry[1000]; // woo
		PageEntry() {
			std::memset(leftDataEntry, 0, sizeof(leftDataEntry));
			std::memset(rightDataEntry, 0, sizeof(rightDataEntry));
		}
		PageEntry(const char* left, const char* right)
		{
			std::strncpy(leftDataEntry, left, sizeof(leftDataEntry) - 1);
			leftDataEntry[sizeof(leftDataEntry) - 1] = '\0';
			std::strncpy(rightDataEntry, right, sizeof(rightDataEntry) - 1);
			rightDataEntry[sizeof(rightDataEntry) - 1] = '\0';
		}
	};

public:
	void Init(CPauseMenuPaginator* pOwner, CPauseMenuHeader* pHeader);
	void AddEntry(int index, PageEntry entry);
	void AddEntry(PageEntry entry);
	PageEntry* GetEntry(int key);
	void ClearEntry(int key);
	std::vector<PageEntry> getAllEntries();
	size_t GetSize() { return m_DataEntries.size(); }
	void SetPageHeader(CPauseMenuHeader* header);
	CPauseMenuHeader* GetHeader();
	CRGBA<float> GetHighlightColor();
	void SetHighlightColor(CRGBA<float> rgba);
	void LoseFocus();
	bool HasFocus();
	void SetFocus();
	void Update();
	static void DrawPage(CPauseMenuPage& page);
	static CPauseMenuHeader GetDefaultHeader();
	int GetSelectionIndex();
	void SetSelectionIndex(int _index);
private:
	std::map<int, PageEntry> m_DataEntries; //aight
	CRGBA<float> highlightColor = { 45, 110, 185, 255 };
	CPauseMenuPaginator* m_pMenuOwner;
	bool m_bHasFocus;
	int selection_index;
	CPauseMenuHeader* m_Header;
};