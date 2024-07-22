#include "MenuHeader.h"
#include "../../BoxDraw/CBoxUI.h"
#include "../../TextDraw/Text.h"
CMenuHeader::CMenuHeader(CRGBA* solidBackground)
    : MH_OPTIONS{ 0 },
    mainStr(std::string("")),
    currentMenu(std::string("")),
    menuItems(std::string(""))
{
    MH_OPTIONS.SolidRGBAColor = solidBackground;
}

CMenuHeader::CMenuHeader(std::string txd):
    MH_OPTIONS{ new CMTxd(txd) },
    mainStr(std::string(" ")),
    currentMenu(std::string(" ")),
    menuItems(std::string(" "))
{
}

void CMenuHeader::SetColor(CRGBA __newinstnce)
{
}

void CMenuHeader::SetTxd(CMTxd __newinstnce)
{
}

void CMenuHeader::SetMainStr(std::string& __newinstnce)
{
}

void CMenuHeader::SetMenuItem(std::string& __newinstnce)
{
}

void CMenuHeader::SetCurrentMenu(std::string& __newinstnce)
{
}

CMTxd& CMenuHeader::GetTxd()
{
    // TODO: insert return statement here
}

CRGBA& CMenuHeader::GetColor()
{
    // TODO: insert return statement here
}

std::string& CMenuHeader::GetMainStr()
{
    // TODO: insert return statement here
}

std::string& CMenuHeader::GetMenuItem()
{
    // TODO: insert return statement here
}

std::string& CMenuHeader::GetCurrentMenu()
{
    // TODO: insert return statement here
}

void CMenuHView::DrawTxd(std::string& mainStr, std::string& currentMenu, std::string& menuIndex, CMTxd& color, CVector2& drawPos)
{
}

/*
* I'd advise rewriting some of this so that you can just take like two parameters like a subheader and a primary header model(s) so that you can actually have this be better.
* Ideally create two objects one for a subheader and another for a primary header and have both do different things.
* The primary header will be the colored in like major header and the subheader will be like the small little thing that tells you your spot in a menu and what menu you are in. 
* Just so that we have the difficiation between the two. Like in general its not that big of a deal however it would be nice to just combine those two into one mega and just be able to draw it via that. 
* Way easier    +
* More Modular  +
* Rewriting     -
* 
*/
void CMenuHView::DrawCol(std::string& mainStr, std::string& currentMenu, std::string& menuIndex, CRGBA& color, CVector2& drawPos)
{
    constexpr float WIDTH = 0.2;
    constexpr float HEIGHT = 0.03;
    CBox* header = new CBox(drawPos, color, WIDTH,0.1);
    if (header == nullptr) {
        return;
    }
    CBox* subHeader = new CBox(CVector2(drawPos.x, header->GetDrawPos().y + ((header->GetHeight() / 2)+(HEIGHT/2))), CRGBA(0, 0, 0, 255), WIDTH, HEIGHT);
    if (subHeader == nullptr) {
        return;
    }
    header->Draw();
    subHeader->Draw();
    CVector2 mainStrDraw = CVector2((header->GetDrawPos().x - header->GetWidth() / 2)+0.003f, header->GetDrawPos().y - 0.003f);
    CVector2 curMenuDraw = CVector2((subHeader->GetDrawPos().x - (subHeader->GetWidth() / 2))+0.004f,subHeader->GetDrawPos().y);
    CVector2 menuIndexDraw = CVector2(subHeader->GetDrawPos().x + (subHeader->GetWidth() / 2), subHeader->GetDrawPos().y);
    CTextUI* mainStrObj = new CTextUI(mainStr, mainStrDraw, CRGBA(255,255,255,255));
    mainStrObj->size = 0.7f;
    mainStrObj->pos = CVector2(mainStrDraw.x, mainStrDraw.y - (mainStrObj->CharacterHeight(2)/2.0F));
    CTextUI* curMenuT = new CTextUI(currentMenu, curMenuDraw, CRGBA(255, 255, 255, 255));
    curMenuT->pos = CVector2(curMenuDraw.x, curMenuDraw.y - (curMenuT->CharacterHeight(1.7) / 2.0F));
    CTextUI* menuIndexObj = new CTextUI(menuIndex, CVector2(curMenuDraw.x + subHeader->GetWidth(), curMenuDraw.y),0.3965, 0, CRGBA(255, 255, 255, 255), CTextDropshadow(1,CRGBA(0,0,0,180)),new CRightJustify(curMenuDraw.x, subHeader->GetCornerPos(subHeader->BOTTOMRIGHT).x - 0.004f), false);
    menuIndexObj->pos = CVector2(menuIndexDraw.x , menuIndexDraw.y - (menuIndexObj->CharacterHeight(1.9)/2.0));
    
    mainStrObj->Draw();
    curMenuT->Draw();
    menuIndexObj->Draw();

    delete menuIndexObj;
    delete curMenuT;
    delete mainStrObj;
    delete subHeader;
    delete header;
}

CMenuHeaderController::CMenuHeaderController(CMenuHeader& _header, CMenuHView _view) :
    view(_view),
    header(_header)
{
}

void CMenuHeaderController::Update()
{
}
