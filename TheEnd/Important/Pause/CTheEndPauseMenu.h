#pragma once
#include <vector>
#include "../../PauseMenuItems/Generic/MenuPaginator.h"
#include "../../PauseMenuItems/Generic/MenuPage.h"
#include "../../PauseMenuItems/Generic/PauseMenuHeader.h"
#include "../../SHVNative/types.h"

class CTheEndPauseMenu {
private:
    class CTheEndPauseParams{
    private:
        CPauseMenuPaginator paginator;
        //CPauseMenuPage m_page;
        //CPauseMenuHeader m_header;
        std::pair<CPauseMenuPage, CPauseMenuHeader> MAP_PAGE;
        std::pair<CPauseMenuPage, CPauseMenuHeader> ONLINE_PAGE;
        std::pair<CPauseMenuPage, CPauseMenuHeader> INFO_PAGE;

    public:
        enum ePageSelection {
            MAP,
            ONLINE,
            INFO
        };
        CTheEndPauseParams() :
            MAP_PAGE(CPauseMenuPage(), CPauseMenuHeader("Header", "Subheader", "Test1", "Test2", "Test3")),
            ONLINE_PAGE(CPauseMenuPage(), CPauseMenuHeader("Grand Theft Auto Online", "", "8/23/24", "FRANKLIN", "2,147,417,240")),
            INFO_PAGE(CPauseMenuPage(), ONLINE_PAGE.second),
            paginator(CPauseMenuPaginator())
        {  
            scriptLogI("called");
        }

        CPauseMenuHeader* GetHeader(ePageSelection page) {
            switch (page) {
            case MAP: return &MAP_PAGE.second;
            case ONLINE: return &ONLINE_PAGE.second;
            case INFO: return &INFO_PAGE.second;
            default: scriptLogE("page that is passed invalid! "); return nullptr;
            };
        }
        CPauseMenuPage* GetPage(ePageSelection page) {
            switch (page) {
            case MAP: return &MAP_PAGE.first;
            case ONLINE: return &ONLINE_PAGE.first;
            case INFO: return &INFO_PAGE.first;
            default: scriptLogE("page that is passed invalid!"); return nullptr;
            };
        }
        CPauseMenuPaginator* GetPaginator() {
            return &this->paginator;
        }
    }m_PauseParams;
    CPauseMenuPage* m_pCurPage;
    CPauseMenuPage* m_pLastPage = nullptr;
    constexpr static const int MAX_PAGES = 6;
    int m_iPaginatorSelection = 0; // depends on menu.
    int m_iPageSelection = 0;
    bool m_bIsPaginatorFocused = true;
    bool m_bIsPageFocused = false;
    bool CanRender = false;
public:
    CTheEndPauseMenu();
    CTheEndPauseParams* GetAllParams() { return &this->m_PauseParams; }
    void Init();
	void Update();
    void Destroy();
    __forceinline CPauseMenuPaginator* GetPaginator() { return this->m_PauseParams.GetPaginator(); }
};

/*
        CPauseMenuPaginator pageinator = CPauseMenuPaginator();
        pageinator.SetSelection(pageinator_selection);
        pageinator.SetPaginatorFocus(pageinator_focused); // forces the focus on the user's side now.
        //vismarker.DrawAll({0,0,-v.z}, {4,4,1});
        CPauseMenuPage OnlinePage = CPauseMenuPage();
        CPauseMenuHeader::PauseInfo onlineInfo = CPauseMenuHeader::PauseInfo("Header", "False", "true", "false", "true");
        CPauseMenuHeader onlineHeader = CPauseMenuHeader(&onlineInfo);
        CTextUI(std::to_string((unsigned long long) & onlineHeader), { 0.1,0.125 }, { 255,255,255,255 }).Draw();
        OnlinePage.Init(&pageinator, &onlineHeader);
        OnlinePage.AddEntry(0, { "Join Friends","" });
        OnlinePage.AddEntry(1, { "Join Crew Members","" });
        OnlinePage.AddEntry(2, { "Crews","" });
        OnlinePage.AddEntry(3, { "Creator","" });
        OnlinePage.AddEntry(4, { "Choose Character","" });
        OnlinePage.AddEntry(5, { "Play GTA Online","\n\nCut to the chase and head straight into the world of GTA Online" });
        OnlinePage.SetHighlightColor({ 171, 237, 171, 255 });
        OnlinePage.SetPageHeader(&onlineHeader);
        CPauseMenuPage page = CPauseMenuPage();
        CPauseMenuHeader::PauseInfo headerInfo = CPauseMenuHeader::PauseInfo("Grand Theft Auto Online", "", "{date}", "{character}", "{money}");
        CPauseMenuHeader hlol = CPauseMenuHeader(&headerInfo);

        page.Init(&pageinator, &hlol);
        page.AddEntry(0, { "Quick Join",""});
        page.AddEntry(1, { "Join Friends","" });
        page.AddEntry(2, { "Join Crew Member","" });
        page.AddEntry(3, { "Playlists", "" });
        page.AddEntry(4,{ "Players", "" });
        page.AddEntry(5,{ "Crews", "" });
        page.AddEntry(6,{ "Rockstar Creator", "" });
        page.AddEntry(7,{ "Manage Characters", "" });
        page.AddEntry(8,{ "Migrate Profile", "" });
        page.AddEntry(9,{ "GTA+ Membership", "" });
        page.AddEntry(10,{ "Purchase Shark Cards", "" });
        page.AddEntry(11,{ "Options", "" });
        page.AddEntry(12,{ "Find New Session", "" });
        page.AddEntry(13,{ "Credits & Legal", "" });
        page.AddEntry(14,{ "Quit To Story Mode", "" });
        page.AddEntry(15,{ "Quit To Main Menu", "" });
        //page.AddEntry(0, { "{menu_option_online0: \"QUICK_JOIN\"}","" });
        //page.AddEntry(1, { "{menu_option_online1: \"JOIN_FRIEND\"}","" });
        //page.AddEntry(2, { "{menu_option_online2: \"JOIN_CREWMBR\"}","" });
        //page.AddEntry(3, { "{menu_option_online3: \"PLAYLIST\"}", "" });
        //page.AddEntry(4, { "{menu_option_online4: \"PLAYERS\"}", "" });
        //page.AddEntry(5, { "{menu_option_online5: \"CREWS\"}", "" });
        //page.AddEntry(6, { "{menu_option_online6: \"CREATOR\"}", "" });
        //page.AddEntry(7, { "{menu_option_online7: \"MNG_CHAR\"}", "" });
        //page.AddEntry(8, { "{menu_option_online8: \"MIG_PROF\"}", "" });
        //page.AddEntry(9, { "{menu_option_online9: \"GTA+_PROMO\"}", "" });
        //page.AddEntry(10, { "{menu_option_online10: \"BUY_SHK_CRD\"}", "" });
        //page.AddEntry(11, { "{menu_option_online11: \"SETTINGS\"}", "" });
        //page.AddEntry(12, { "{menu_option_online12: \"NEW_SESSION\"}", "" });
        //page.AddEntry(13, { "{menu_option_online13: \"CRED+LEGAL\"}", "" });
        //page.AddEntry(14, { "{menu_option_online14: \"QUIT_STORY\"}", "" });
        //page.AddEntry(15, { "{menu_option_online15: \"QUIT_MAIN\"}", "" });
        pageinator.RegisterPage("MAP", page);
        pageinator.RegisterPage("BRIEF", OnlinePage);
        pageinator.RegisterPage("STATS", OnlinePage);
        pageinator.RegisterPage("SETTINGS", OnlinePage);
        pageinator.RegisterPage("GAME", OnlinePage);
        pageinator.RegisterPage("ONLINE", OnlinePage);
        //CPauseMenuHeader header = CPauseMenuHeader(CPauseMenuHeader::PauseInfo("GrAnd Th3Ft Au0x2 0nIine ?RageParserSchema::NextXMLElement()?0x0fff02bba", "", "T??? ??:??", "UNK_001", "$-ab0x0244f"));
        CPauseMenuPage* currentPage = pageinator.GetPageFromIndex(pageinator_selection);
        currentPage->SetSelectionIndex(page_selection);
        if (IsKeyJustUp(VK_F15) ){
            m_bCanShowPause = true;
        }
        if (m_bCanShowPause) {
            if (pageinator_focused == false) {
                if (currentPage == nullptr) {
                    int gameTime = MISC::GET_GAME_TIMER();
                    while (gameTime + 5000 > MISC::GET_GAME_TIMER()) {
                        CTextUI("currentPage passed is nullptr", { 0.5,0.5 }, { 255,0,0,255 }).Draw();
                        WAIT(0);
                    }
                    return;
                }
                currentPage->SetFocus();
                page_focused = true;
            }
            if (pageinator.GetIfPaginatorHasFocus()) {
                if (IsKeyJustUp(VK_RIGHT)) {
                    pageinator_selection = (pageinator.GetSelection() + 1 < pageinator.GetMaxSelections() ? pageinator.GetSelection() + 1 : 0);
                }
                if (IsKeyJustUp(VK_LEFT)) {
                    pageinator_selection = (pageinator.GetSelection() - 1 >= 0 ? pageinator.GetSelection() - 1 : pageinator.GetMaxSelections() - 1);
                }
                if (IsKeyJustUp(VK_RETURN)) {
                    page_selection = 0;
                    page_focused = 0;
                    pageinator_focused = false;
                }
                if (IsKeyJustUp(VK_BACK)) {
                    pageinator_focused = false;
                    page_selection = 0;
                    page_focused = 0;
                    m_bCanShowPause = false;
                }
            }
            if (!pageinator.GetIfPaginatorHasFocus()) {
                if (IsKeyJustUp(VK_BACK)) {
                    page_focused = false;
                    page_selection = -1;
                    currentPage->LoseFocus();
                    pageinator_focused = true;
                }
                if (IsKeyJustUp(VK_DOWN)) {
                    if (page_selection == currentPage->getAllEntries().size() - 1) {
                        page_selection = -1;
                    }
                    page_selection++;
                }
                if (IsKeyJustUp(VK_UP)) {
                    if (page_selection == -2) {
                        page_selection = currentPage->getAllEntries().size() - 1;
                    }
                    page_selection--;
                }
                if (IsKeyJustUp(VK_RETURN)) {
                    //Call the function with the arguments of currentPage;
                    int gameTimer = MISC::GET_GAME_TIMER(); // TODO -- Update this stuff with logger and put this all somewhere else as we don't need it!
                    while (gameTimer + 2500 > MISC::GET_GAME_TIMER()) {
                        CTextUI text = CTextUI("VK_RETURN Pressed", { 0.5,0.5 }, { 255,255,255,255 });
                        text.size = 1;
                        text.dropShadow = CTextDropshadow(0, CRGBA<float>{ 0,0,0,0 });
                        text.SetTextJustification(0);
                        text.Draw();
                        if (IsKeyJustUp(VK_BACK)) {
                            break;
                        }
                        WAIT(0);
                    }
                }
            }
            pageinator.Update(lastPageSelected);

        }
*/