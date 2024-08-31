#include "HelpText.h"

void CHelpText::SetCanHelpTextShow(bool b) {
    this->m_bCanHelpTextShow = b;
}

bool CHelpText::CanHelpTextShow() {
    return this->m_bCanHelpTextShow;
}

void CHelpText::SetHelpText(const char* text) {
    this->m_TextString = text;
}

const char* CHelpText::GetHelpText() {
    return this->m_TextString;
}

bool CHelpText::IsHelpTextShowing() {
    return this->m_bIsHelpTextShowing;
}

void CHelpText::SetHelpTextActive(bool b) {
    this->m_bIsHelpTextShowing = b;
}
