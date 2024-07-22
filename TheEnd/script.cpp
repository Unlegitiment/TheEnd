#include "script.h"
#include "keyboard.h"

#include <string>
#include <ctime>
#include "MarkerLauncher/VisualMarker.h"
#include "ScaleformHelper/CScaleform.h"
#include "UIEditor/TextDraw/Text.h"
#include "PauseMenuItems/Generic/MenuPaginator.h"
#include "PauseMenuItems/Generic/PauseMenuHeader.h"
#include "PauseMenuItems/Generic/MenuPage.h"
#pragma warning(disable : 4244 4305) // double <-> float conversions
std::string ClockToDay(int day) {
    switch (day) {
    case 0: 
        return "SUNDAY";
    case 1:
        return "MONDAY";
    case 2:
        return "TUESDAY";
    case 3:
        return "WEDNESDAY";
    case 4:
        return "THURSDAY";
    case 5:
        return "FRIDAY";
    case 6:
        return "SATURDAY";

    }
}
#include <string>

void main() {
    CVector3 v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
    bool isOnlineReq = false;
    bool isHalloweenInteriorActive = false;
    bool forceFirstPerson = true;
    int pageinator_selection = 0;
    int page_selection = 0;
    int page_focused = 0;
    bool pageinator_focused = true;
    bool m_bCanShowPause = false;
    bool isMissionStarted = false;
    CPauseMenuPage* lastPageSelected = nullptr;
    while (true){
        if (forceFirstPerson) {
            CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(4);
            PAD::DISABLE_CONTROL_ACTION(0, 0,false);
        }
        if (IsKeyJustUp(VK_F13)) {
            forceFirstPerson = !forceFirstPerson;
        }
        if (isOnlineReq == false) {
            DLC::ON_ENTER_MP();
            isOnlineReq = true;
        }
        if (!STREAMING::IS_IPL_ACTIVE("m23_1_dlc_int_03_m23_1")) {
            STREAMING::REQUEST_IPL("m23_1_dlc_int_03_m23_1");
            isHalloweenInteriorActive = true;
        }
        if (IsKeyJustUp(VK_DIVIDE)) {
            ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1876.62134, 3750, -100, 1,0,0,0); // interior stuff
        }
        if (v.Dist(CVector3{ -1921.955, 3749.7202, -99 }) < 1.76) {
            CTextUI("You are inside area", {0.5, 0.2}, { 255,255,255,255 }).Draw();
            if (PAD::IS_CONTROL_JUST_RELEASED(0, 51)) {
                CAM::DO_SCREEN_FADE_OUT(100);
                WAIT(150);
                ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -2056.26, 3239.9, 30.8,1,0,0,0);
                ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 60);
                WAIT(400);
                CAM::DO_SCREEN_FADE_IN(150);
            }
        }
        v = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
        CMarkerInfo markerInfo = CMarkerInfo("Mission", "The End", "", "100%", "", false, "1", "", "", "");
        CMissionMarker marker = CMissionMarker({v.x, v.y, v.z + 2.f}, { 5.f,5.f,1.f }, CRGBA(255, 255, 255, 255), CTxd("mpmissmarkers256", "custom_icon")); // please kys!
        CVisMarker vismarker = CVisMarker(markerInfo, marker);
        CVector3 v = CAM::GET_GAMEPLAY_CAM_ROT(2);


#pragma region PauseMenuInit
        CPauseMenuPaginator pageinator = CPauseMenuPaginator();
        pageinator.SetSelection(pageinator_selection);
        pageinator.SetPaginatorFocus(pageinator_focused); // forces the focus on the user's side now.
        //vismarker.DrawAll({0,0,-v.z}, {4,4,1});
        CPauseMenuPage OnlinePage = CPauseMenuPage();
        CPauseMenuHeader onlineHeader = CPauseMenuHeader(&CPauseMenuHeader::PauseInfo("Header", "False", "true", "false", "true"));
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
        CPauseMenuHeader hlol = CPauseMenuHeader(&CPauseMenuHeader::PauseInfo("{main_header: \"Grand_Theft_Auto_Online\"}", "", "{date}", "{character}", "{money}"));

        page.Init(&pageinator, &hlol);
        //page.AddEntry(0, { "Quick Join",""});
        //page.AddEntry(1, { "Join Friends","" });
        //page.AddEntry(2, { "Join Crew Member","" });
        //page.AddEntry(3, { "Playlists", "" });
        //page.AddEntry(4,{ "Players", "" });
        //page.AddEntry(5,{ "Crews", "" });
        //page.AddEntry(6,{ "Rockstar Creator", "" });
        //page.AddEntry(7,{ "Manage Characters", "" });
        //page.AddEntry(8,{ "Migrate Profile", "" });
        //page.AddEntry(9,{ "GTA+ Membership", "" });
        //page.AddEntry(10,{ "Purchase Shark Cards", "" });
        //page.AddEntry(11,{ "Options", "" });
        //page.AddEntry(12,{ "Find New Session", "" });
        //page.AddEntry(13,{ "Credits & Legal", "" });
        //page.AddEntry(14,{ "Quit To Story Mode", "" });
        //page.AddEntry(15,{ "Quit To Main Menu", "" });
        page.AddEntry(0, { "{menu_option_online0: \"QUICK_JOIN\"}","" });
        page.AddEntry(1, { "{menu_option_online1: \"JOIN_FRIEND\"}","" });
        page.AddEntry(2, { "{menu_option_online2: \"JOIN_CREWMBR\"}","" });
        page.AddEntry(3, { "{menu_option_online3: \"PLAYLIST\"}", "" });
        page.AddEntry(4, { "{menu_option_online4: \"PLAYERS\"}", "" });
        page.AddEntry(5, { "{menu_option_online5: \"CREWS\"}", "" });
        page.AddEntry(6, { "{menu_option_online6: \"CREATOR\"}", "" });
        page.AddEntry(7, { "{menu_option_online7: \"MNG_CHAR\"}", "" });
        page.AddEntry(8, { "{menu_option_online8: \"MIG_PROF\"}", "" });
        page.AddEntry(9, { "{menu_option_online9: \"GTA+_PROMO\"}", "" });
        page.AddEntry(10, { "{menu_option_online10: \"BUY_SHK_CRD\"}", "" });
        page.AddEntry(11, { "{menu_option_online11: \"SETTINGS\"}", "" });
        page.AddEntry(12, { "{menu_option_online12: \"NEW_SESSION\"}", "" });
        page.AddEntry(13, { "{menu_option_online13: \"CRED+LEGAL\"}", "" });
        page.AddEntry(14, { "{menu_option_online14: \"QUIT_STORY\"}", "" });
        page.AddEntry(15, { "{menu_option_online15: \"QUIT_MAIN\"}", "" });


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
                    int gameTimer = MISC::GET_GAME_TIMER();
                    while (gameTimer + 2500 > MISC::GET_GAME_TIMER()) {
                        CTextUI text = CTextUI("VK_RETURN Pressed", { 0.5,0.5 }, { 255,255,255,255 });
                        text.size = 1;
                        text.dropShadow = CTextDropshadow(0, { 0,0,0,0 });
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
#pragma endregion
        //CPauseMenuPaginator::DrawPage(page);
        if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("pedmugshot_01")) {
            //CPauseMenuHeader h = CPauseMenuHeader(CPauseMenuHeader::PauseInfo("The End", "[Error]: Disconnection detected; Breach breach breach!", std::string(ClockToDay(CLOCK::GET_CLOCK_DAY_OF_WEEK()) + " " + std::to_string(CLOCK::GET_CLOCK_HOURS()) + (CLOCK::GET_CLOCK_MINUTES() <= 9 ? ":0" : ":") + std::to_string(CLOCK::GET_CLOCK_MINUTES())).c_str(), "FRANKLIN", "$2,147,365,094"));
            //CPauseMenuHeader::DrawHeader(h);
        } else {
            GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("pedmugshot_01",1);
        }
        //vCorona.Draw();eeee
        WAIT(0);
    }
}

void ScriptMain()
{
    srand(GetTickCount());
    main();
}
