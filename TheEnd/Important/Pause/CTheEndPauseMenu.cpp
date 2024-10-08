#include "CTheEndPauseMenu.h"

#include "../../keyboard.h"
#include "../../SHVNative/natives.h"
#include "../../UIEditor/TextDraw/Text.h"
CTheEndPauseMenu::CTheEndPauseMenu() : m_PauseParams(CTheEndPauseParams()), m_pCurPage(nullptr) {
    scriptLogI("called.");
}
//"Header", "False", "true", "false", "true"
void CTheEndPauseMenu::Init() { // what the fuck is this shit lmao.
    CPauseMenuPaginator paginator = CPauseMenuPaginator();
    CPauseMenuHeader* m_OnlineHeader = this->m_PauseParams.GetHeader(CTheEndPauseParams::ONLINE);
    CPauseMenuPage* m_OnlinePage = this->m_PauseParams.GetPage(CTheEndPauseParams::ONLINE);
    CPauseMenuPage* page = this->m_PauseParams.GetPage(CTheEndPauseParams::MAP);
    CPauseMenuHeader* hlol = this->m_PauseParams.GetHeader(CTheEndPauseParams::MAP);

    page->Init(this->GetPaginator(), hlol);
    page->AddEntry(0, { "Quick Join","" });
    page->AddEntry(1, { "Join Friends","" });
    page->AddEntry(2, { "Join Crew Member","" });
    page->AddEntry(3, { "Playlists", "" });
    page->AddEntry(4, { "Players", "" });
    page->AddEntry(5, { "Crews", "" });
    page->AddEntry(6, { "Rockstar Creator", "" });
    page->AddEntry(7, { "Manage Characters", "" });
    page->AddEntry(8, { "Migrate Profile", "" });
    page->AddEntry(9, { "GTA+ Membership", "" });
    page->AddEntry(10, { "Purchase Shark Cards", "" });
    page->AddEntry(11, { "Options", "" });
    page->AddEntry(12, { "Find New Session", "" });
    page->AddEntry(13, { "Credits & Legal", "" });
    page->AddEntry(14, { "Quit To Story Mode", "" });
    page->AddEntry(15, { "Quit To Main Menu", "" });
    m_OnlinePage->Init(this->GetPaginator(), m_OnlineHeader);
    m_OnlinePage->AddEntry(0, { "Join Friends","" });
    m_OnlinePage->AddEntry(1, { "Join Crew Members","" });
    m_OnlinePage->AddEntry(2, { "Crews","" });
    m_OnlinePage->AddEntry(3, { "Creator","" });
    m_OnlinePage->AddEntry(4, { "Choose Character","" });
    m_OnlinePage->AddEntry(5, { "Play GTA Online","\n\nCut to the chase and head straight into the world of GTA Online" });
    m_OnlinePage->SetHighlightColor({ 171, 237, 171, 255 });
    if (this->GetPaginator() == nullptr) {
        scriptLogE("GetPaginator() is null!");
        CanRender = false;
        return;
    }
    this->GetPaginator()->RegisterPage("MAP", *m_OnlinePage);
    this->GetPaginator()->RegisterPage("ONLINE", *page);
    this->GetPaginator()->RegisterPage("FRIENDS", *page);
    this->GetPaginator()->RegisterPage("SETTINGS", *page);
}

void CTheEndPauseMenu::Update() {
    if (IsKeyJustUp(VK_F15)) {
        this->CanRender = true;
        if (!m_bIsPageFocused) {
            m_bIsPaginatorFocused = true;
        }
    }
    if (CanRender) {

        this->m_pCurPage = GetPaginator()->GetPageFromIndex(this->m_iPaginatorSelection); // we might have to rework but thats fine.
        if (this->m_bIsPaginatorFocused == false) {
            if (this->m_pCurPage == nullptr) {
                int gameTime = MISC::GET_GAME_TIMER();
                while (gameTime + 5000 > MISC::GET_GAME_TIMER()) {
                    CTextUI("currentPage passed is nullptr", { 0.5,0.5 }, { 255,0,0,255 }).Draw();
                    WAIT(0);
                }
                return;
            }
        }
        if (m_bIsPaginatorFocused) {
            if (IsKeyJustUp(VK_RIGHT)) {
                //if (m_iPaginatorSelection + 1 < this->GetPaginator()->GetMaxSelections()) {
                //    this->m_iPaginatorSelection =+ 1;
                //}
                this->m_iPaginatorSelection = (m_iPaginatorSelection + 1 < this->GetPaginator()->GetMaxSelections() ? m_iPaginatorSelection += 1 : 0);
                scriptLogI("RIGHT PRESSED!\n\tUpdating m_iSelection : ", this->m_iPaginatorSelection, " \n\tMax Selections : ", GetPaginator()->GetMaxSelections());
            }
            if (IsKeyJustUp(VK_LEFT)) {
                this->m_iPaginatorSelection = (m_iPaginatorSelection - 1 >= 0 ? m_iPaginatorSelection - 1 : this->GetPaginator()->GetMaxSelections() - 1);
                scriptLogI("LEFT PRESSED! \n\tUpdating m_iSelection: ", this->m_iPaginatorSelection, " \n\tMax Selections: ", GetPaginator()->GetMaxSelections());
            }
            if (IsKeyJustUp(VK_RETURN)) {
                this->m_iPageSelection = 0;
                this->m_bIsPaginatorFocused = false;
                this->m_bIsPageFocused = true;
            }
            if (IsKeyJustUp(VK_BACK)) {
                this->m_bIsPaginatorFocused = false;
                CanRender = false;
                this->m_iPaginatorSelection = 0;
                this->m_bIsPageFocused = 0;
            }
        }
        if (!m_bIsPaginatorFocused) {
            if (IsKeyJustUp(VK_BACK)) {
                this->m_bIsPageFocused = false;
                this->m_iPageSelection = -1;
                this->m_pCurPage->LoseFocus();
                this->m_bIsPaginatorFocused = true;
            }
            if (IsKeyJustUp(VK_DOWN)) {
                if (m_iPageSelection == m_pCurPage->getAllEntries().size() - 1) {
                    this->m_iPageSelection = -1;
                }
                this->m_iPageSelection++;
                scriptLogI("called DOWN PRESSED! m_iPageSelection: ", this->m_iPageSelection);
            }
            if (IsKeyJustUp(VK_UP)) {
                if (this->m_iPageSelection == 0) {
                    this->m_iPageSelection = m_pCurPage->getAllEntries().size() - 1;
                    return;
                }
                this->m_iPageSelection--;
                scriptLogI("called UP PRESSED! m_iPageSelection: ", this->m_iPageSelection);

            }
            if (IsKeyJustUp(VK_RETURN)) {
                //Call the function with the arguments of currentPage;
                int gameTimer = MISC::GET_GAME_TIMER(); // TODO -- Update this stuff with logger and put this all somewhere else as we don't need it!
                while (gameTimer + 2500 > MISC::GET_GAME_TIMER()) {
                    CTextUI text = CTextUI("VK_RETURN Pressed", { 0.5,0.5 }, { 255,255,255,255 });
                    text.size = 1;
                    text.dropShadow = CTextDropshadow(0, CRGBA<float>{ 0, 0, 0, 0 });
                    text.SetTextJustification(0);
                    text.Draw();
                    if (IsKeyJustUp(VK_BACK)) {
                        break;
                    }
                    WAIT(0);
                }
            }
        }
        this->GetPaginator()->SetSelection(m_iPaginatorSelection);
        this->GetPaginator()->SetPaginatorFocus(m_bIsPaginatorFocused);
        m_pCurPage->SetFocus(m_bIsPageFocused);
        m_pCurPage->SetSelectionIndex(m_iPageSelection);
        this->GetPaginator()->Update(this->m_pLastPage);
    }
}

void CTheEndPauseMenu::Destroy() {
}


//if (pageinator_focused == false) {
//    if (currentPage == nullptr) {
//        int gameTime = MISC::GET_GAME_TIMER();
//        while (gameTime + 5000 > MISC::GET_GAME_TIMER()) {
//            CTextUI("currentPage passed is nullptr", { 0.5,0.5 }, { 255,0,0,255 }).Draw();
//            WAIT(0);
//        }
//        return;
//    }
//    currentPage->SetFocus();
//    page_focused = true;
//}
//if (pageinator.GetIfPaginatorHasFocus()) {
//    if (IsKeyJustUp(VK_RIGHT)) {
//        pageinator_selection = (pageinator.GetSelection() + 1 < pageinator.GetMaxSelections() ? pageinator.GetSelection() + 1 : 0);
//    }
//    if (IsKeyJustUp(VK_LEFT)) {
//        pageinator_selection = (pageinator.GetSelection() - 1 >= 0 ? pageinator.GetSelection() - 1 : pageinator.GetMaxSelections() - 1);
//    }
//    if (IsKeyJustUp(VK_RETURN)) {
//        page_selection = 0;
//        page_focused = 0;
//        pageinator_focused = false;
//    }
//    if (IsKeyJustUp(VK_BACK)) {
//        pageinator_focused = false;
//        page_selection = 0;
//        page_focused = 0;
//        m_bCanShowPause = false;
//    }
//}
//if (!pageinator.GetIfPaginatorHasFocus()) {
//    if (IsKeyJustUp(VK_BACK)) {
//        page_focused = false;
//        page_selection = -1;
//        currentPage->LoseFocus();
//        pageinator_focused = true;
//    }
//    if (IsKeyJustUp(VK_DOWN)) {
//        if (page_selection == currentPage->getAllEntries().size() - 1) {
//            page_selection = -1;
//        }
//        page_selection++;
//    }
//    if (IsKeyJustUp(VK_UP)) {
//        if (page_selection == -2) {
//            page_selection = currentPage->getAllEntries().size() - 1;
//        }
//        page_selection--;
//    }
//    if (IsKeyJustUp(VK_RETURN)) {
//        //Call the function with the arguments of currentPage;
//        int gameTimer = MISC::GET_GAME_TIMER(); // TODO -- Update this stuff with logger and put this all somewhere else as we don't need it!
//        while (gameTimer + 2500 > MISC::GET_GAME_TIMER()) {
//            CTextUI text = CTextUI("VK_RETURN Pressed", { 0.5,0.5 }, { 255,255,255,255 });
//            text.size = 1;
//            text.dropShadow = CTextDropshadow(0, CRGBA<float>{ 0, 0, 0, 0 });
//            text.SetTextJustification(0);
//            text.Draw();
//            if (IsKeyJustUp(VK_BACK)) {
//                break;
//            }
//            WAIT(0);
//        }
//    }