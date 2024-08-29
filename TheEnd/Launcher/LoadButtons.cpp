#include "LoadButtons.h"
#include <string>
#include <cassert>

void CLoadButton::CallCallback() {
    this->MyCallback(this);
}

void CLoadButton::SetFunction(Func call_back) {
    this->MyCallback = call_back;
}
CLoadMenu* CLoadButton::GetOwner() {
    return nullptr;
}

std::string* CLoadButton::GetText() {
    return &this->m_sText;
}

bool CLoadButton::IsHighlighted() {
    return this->m_bIsHighlighted;
}

void CLoadButton::SetHighlighted(bool stat) {
    this->m_bIsHighlighted = stat;
}

void CLoadButton::SetText(std::string text) {
    this->m_sText = text;
}

CLoadButton::CLoadButton(CLoadMenu* menu, Func callback) {
    this->m_pOwner = menu;
    this->MyCallback = callback;
    this->m_sText = "";
    this->m_bIsHighlighted = false;
}
