#pragma once
#include <string>
#include <vector>
#include "./LoadButtons.h"
/*
Lets get something very clear we do NOT need an update for every class only the ones we actually intent on drawing stuff in so our implementation classes and those should be as simple as possible or only be effectively draw commands.
*/
class CLoadMenu {
private:
	using Buttons = std::vector<CLoadButton*>;
	std::string m_Header; // not a pause menu header.
	Buttons m_AllButtons;
public:
	CLoadMenu();
	void Init(std::string header);
	void SetHeader(std::string header);
	std::string& GetHeader();
	Buttons* GetButtons();
	void PushNewButton(CLoadButton* loadBtn);
	void RemoveButtonAtIndex(int index);
	void ClearAllButtons();
};