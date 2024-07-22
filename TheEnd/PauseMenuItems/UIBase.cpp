#include "UIBase.h"
#include "../UIEditor/TextDraw/Text.h"
CUIBase::CUIBase(eUIType t):
    eType(t)
{
}

CUIBase::eUIType CUIBase::getType() {
    return this->eType;
}

void CUIBase::setType(eUIType t) {
    this->eType = t;
}

void CUIBase::Draw() {
    CTextUI text = CTextUI("You probably didn't extend the draw call ~r~dumbass", { 0.5,0.5 }, {240,240,240,255});
    text.size = 1;
    text.textJustification = 0;
    text.Draw();
}
