#pragma once
#include <vector>
#include "../SHVNative/types.h"
#include <functional>
class CPlayerMenu {
public:
	struct sMenuItem {
		const char* MenuLeft;
		const char* MenuRight;
		const char* MenuContext;
		std::function<void(CPlayerMenu*, sMenuItem*)> CallBack;
	};
	struct sHeaderInformation {
		const char* pHeaderString; // Main string
		const char* pSubHeaderString;
		bool bDoesContainIndex;
	};
	CPlayerMenu();
	void SetHeader(const sHeaderInformation& header);
	void AddMenuItem(const sMenuItem& menuItem);
	void Display();
	void SetSelected(int _new);
	int GetSelected();
	sMenuItem* GetItem(int index);
	size_t GetSize() { return this->MenuItems.size(); }
private:
	void DisplayItem(sMenuItem& menuItem, int index, bool selected);
	void DisplayHeader();
	CVector2<float> MenuScreenPosition = {0.1625f, 0.2f}; // woohoo
	float fGlobalHeight = 0.04f;
	float fGlobalWidth = 0.225f; // which is probably accurate lol
	sHeaderInformation* header = nullptr;
	std::vector<sMenuItem> MenuItems;
	int m_iSelectedIndex = 0;
};