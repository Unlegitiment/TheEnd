#include "GameLoadMenu.h"
#include "../SHVNative/types.h"
CLoadMenu::CLoadMenu() {
    this->Init("");
}

void CLoadMenu::Init(std::string header) {
    this->m_Header = header;
}

void CLoadMenu::SetHeader(std::string header) {
    this->m_Header = header;
}

std::string& CLoadMenu::GetHeader() {
    return this->m_Header;
}

CLoadMenu::Buttons* CLoadMenu::GetButtons() {
    return &this->m_AllButtons;
}

void CLoadMenu::PushNewButton(CLoadButton* loadBtn) {
    if (loadBtn == nullptr) {
        scriptLogI("inserting a nullptr button @ index", this->m_AllButtons.size(), "! (ignoring)");
        return;
    }
    scriptLogI("Inserting button: 0x%p@%i", loadBtn, this->m_AllButtons.size());
    this->m_AllButtons.push_back(loadBtn);
    return;
}

void CLoadMenu::RemoveButtonAtIndex(int index) {
    if (index > this->m_AllButtons.size()) scriptLogW("index suppled is greater than size of array, ", index, " current size: ", this->m_AllButtons.size(), "!"); return;
    Buttons::iterator it = this->m_AllButtons.begin() + index;
    this->m_AllButtons.erase(it); // i hate c++ base classes guys. but idk how to write an iterator help.
    return;
}

void CLoadMenu::ClearAllButtons() {
    scriptLogI("called, clearing buttons of: ", this->m_AllButtons.size(), "!");
    this->m_AllButtons.clear();
}
