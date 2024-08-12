#include "PauseMenuHeader.h"
#include "../../SHVNative/natives.h"
#include "../../UIEditor/TextDraw/Text.h"
#include "../../UIEditor/BoxDraw/CBoxUI.h"
#include "assert.h"
CPauseMenuHeader::CPauseMenuHeader(PauseInfo* info) 
{
    assert(info == nullptr, "CPauseMenuHeader::CPauseMenuHeader(PauseMenu*) cannot be nullptr");
    this->pauseInfo = info;
}

CPauseMenuHeader::PauseInfo* CPauseMenuHeader::getInfo() {
    return this->pauseInfo;
}

void CPauseMenuHeader::setInfo(PauseInfo* info) {
    this->pauseInfo = info;
    return;
}

void CPauseMenuHeader::DrawHeader(CPauseMenuHeader& header) {
    bool isSubheaderActive = false;
    if (header.getInfo()->subheader != nullptr || std::strcmp("", header.getInfo()->subheader) != 0) {
        isSubheaderActive = true;
    }
    DrawMissionDetails(header);
    DrawTime(header);
    DrawCharacter(header);
    DrawMoney(header);
    if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(header.getInfo()->texture.getDict())) {
        DrawCharSprite(header);
    } else {
        GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(header.getInfo()->texture.getDict(), 1);
    }
}

void CPauseMenuHeader::DrawMissionDetails(CPauseMenuHeader& info) {
    bool isSubheaderActive = false;
    if (info.getInfo()->subheader[0] != '\0') {
        isSubheaderActive = true;
    }
    CTextUI masthead = CTextUI(info.pauseInfo->header, { 0.216796875f - (0.0381944444f * 1.501), isSubheaderActive ? 0.075f : 0.102f }, { 240,240,240,255 });
    masthead.size = 0.85f;
    masthead.font = masthead.FONT_CHALET_COMPRISE_COLOGNE;
    masthead.Draw();
    if (isSubheaderActive) {
        CTextUI subhead = CTextUI(info.getInfo()->subheader, { 0.216796875f - (0.0381944444f * 1.501), 0.12 }, { 240,240,240,255 });
        subhead.size = 0.3f;
        //subhead.font = subhead.FONT_CHALET_COMPRISE_COLOGNE;
        subhead.Draw();
    }
}

void CPauseMenuHeader::DrawTime(CPauseMenuHeader& info) {
    CVector2 baseVector = { 0.750f,0.0772f };
    CTextUI m_Date = CTextUI(info.getInfo()->date, { baseVector.x, baseVector.y + CTextUI::CharacterHeight(1, 0.46) + 0.003f }, { 240,240,240,255 });
    m_Date.font = m_Date.FONT_CHALET_COMPRISE_COLOGNE;
    m_Date.hasOutline = true;
    //m_Date.dropShadow = CTextDropshadow(2, { 0,0,0,255 });
    m_Date.textJustification = 2;
    m_Date.size = 0.46;
    HUD::SET_TEXT_WRAP(0.0, 0.803f);
    HUD::SET_TEXT_LEADING(1);
    m_Date.Draw();
}

void CPauseMenuHeader::DrawCharacter(CPauseMenuHeader& info) {
    CVector2 baseVector = { 0.750f,0.0772f };
    CTextUI m_CHAR_NAME = CTextUI(info.getInfo()->character, baseVector, { 240,240,240,255 });
    m_CHAR_NAME.font = m_CHAR_NAME.FONT_CHALET_COMPRISE_COLOGNE;
    m_CHAR_NAME.dropShadow = CTextDropshadow(2, { 0,0,0,255 });
    m_CHAR_NAME.textJustification = 2;
    m_CHAR_NAME.size = 0.46;
    m_CHAR_NAME.hasOutline = true;

    HUD::SET_TEXT_WRAP(0.0, 0.803f);
    HUD::SET_TEXT_LEADING(0);
    m_CHAR_NAME.Draw();

}

void CPauseMenuHeader::DrawMoney(CPauseMenuHeader& info) {
    CVector2 baseVector = { 0.750f,0.0772f };
    CTextUI m_ADDINFO = CTextUI(info.getInfo()->additional_info, { baseVector.x, baseVector.y + CTextUI::CharacterHeight(1,0.46) * 2 + 0.003f }, { 240,240,240,255 });
    m_ADDINFO.font = m_ADDINFO.FONT_CHALET_COMPRISE_COLOGNE;
    m_ADDINFO.dropShadow = CTextDropshadow(2, { 0,0,0,255 });
    m_ADDINFO.textJustification = 2;
    m_ADDINFO.size = 0.46;
    m_ADDINFO.hasOutline = true;

    HUD::SET_TEXT_WRAP(0.0, 0.803f);
    HUD::SET_TEXT_LEADING(0);
    m_ADDINFO.Draw();

}

void CPauseMenuHeader::DrawCharSprite(CPauseMenuHeader& info) {
    CBox({ 0.8237, 0.115 }, CRGBA(0, 0, 0, 255), 0.025f * 1.5, 0.045f * 1.5).Draw();
    GRAPHICS::DRAW_SPRITE(info.getInfo()->texture.getDict(), info.getInfo()->texture.getName(), 0.8237, 0.115, 0.025f * 1.5, 0.045f * 1.5, 0, 255, 255, 255, 255, 1, 1);
}
