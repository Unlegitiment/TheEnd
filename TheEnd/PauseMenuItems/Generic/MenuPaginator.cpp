#include "MenuPaginator.h"
#include "../../UIEditor/TextDraw/Text.h"
#include "../../UIEditor/BoxDraw/CBoxUI.h"
#include "../../keyboard.h"
#include "MenuPage.h"

void CPauseMenuPaginator::RegisterPage(const char* name, CPauseMenuPage& page) {
	this->m_Pages.push_back(Item(name, page)); // kewl one benefit of C++ is you don't need to explicitly state objects as long as you have all info in the constructor is all it cares about.
}
void CPauseMenuPaginator::Update(CPauseMenuPage*& __last_page) { // this actually isn't that bad. might extract some functionality out just to allow the stuff to breathe lol.
	const float spacing = 0.002f;
	const float selectionHeight = 0.0079875f; // 287 × 55 | 2560 × 1440 | 124 × 25 (important info) verydesc
	CVector2 baseVectorText = { 0.216796875f, 0.184722222f };
	for (int i = 0; i < m_Pages.size(); i++) {
		//This stuff can be extracted out into a seperate thing.
		CPauseMenuPage* curPage = &m_Pages[i].second;
		CTextUI curText = CTextUI(m_Pages[i].first, baseVectorText, {240,240,240,255});
		curText.font = curText.FONT_CHALET_LONDON;
		float xForm = 0.216796875f + ((0.112109375f + spacing) * i);
		CBox curBoxObj = CBox({ xForm, baseVectorText.y }, {0,0,0,150}, 0.112109375f, 0.0381944444f);
		if (i == box_selection) {
			CTextUI("CurPage Has Focus", { 0.1,0.025 }, { 255,255,255,255 }).Draw();
			CTextUI("i == box_selection", {0.1, 0.050}, { 255,255,255,255 }).Draw();
			CTextUI(std::to_string(m_bisFocused), { 0.1,0.075 }, { 255,255,255,255 }).Draw();
			curBoxObj.SetColour(CRGBA(240,240,240,255));
			CBox selectionBox = CBox({ curBoxObj.GetDrawPos().x, curBoxObj.GetDrawPos().y - ((curBoxObj.GetHeight() / 2.f) + (selectionHeight / 2.f))}, m_Pages[i].second.GetHighlightColor(), curBoxObj.GetWidth(), selectionHeight);
			selectionBox.Draw();
			curText.colour = CRGBA(0, 0, 0, 255);
			curText.dropShadow = { 0,{0,0,0,0} };
			__last_page = curPage;
			CTextUI(std::to_string((unsigned long long) __last_page->GetHeader()), { 0.1,0.0 }, {240,240,240,255}).Draw();
			curPage->Update();
			DrawPage(m_Pages[i].second, curPage->GetSelectionIndex());
		}
		curText.size = 0.344375f;
		curText.textJustification = 0;
		curText.pos = { curBoxObj.GetDrawPos().x - 0.0026f, curBoxObj.GetDrawPos().y - curText.CharacterHeight(0.56f) };
		curBoxObj.Draw();
		curText.Draw();
	}
	//DrawAllNavButtons();
}
#include "../../ScaleformHelper/CScaleform.h"
void CPauseMenuPaginator::DrawPage(CPauseMenuPage& page, int selection_index) { //draw one page (edit big bloat lol.) 
	//For this we need one box and two text entries per block (one for right one for left). this is demo code to outline it.
	CVector2 baseVectorText = { 0.216796875f, 0.184722222f }; // from (nav menu) above
	CScaleform scaleform = CScaleform("GTAV_ONLINE");
	scaleform.BeginMethod("SETUP_BIGFEED");
	scaleform.BoolPush(true);
	scaleform.EndFunction();
	scaleform.BeginMethod("HIDE_ONLINE_LOGO");
	scaleform.EndFunction();
	CPauseMenuHeader::DrawHeader(*page.GetHeader());

	bool isSelectionIndexNegative = true;
	bool isPageFocused = page.HasFocus();
	if (selection_index >= 0) {
		isSelectionIndexNegative = false;
	}
	for (int i = 0; i < page.getAllEntries().size(); i++) {
		CVector2 baseVectorBox = { baseVectorText.x + 0.225f / 4.f, baseVectorText.y + 0.0481944444f + ((0.0379544444f) * i) };
		CBox box = CBox({ baseVectorBox.x, baseVectorBox.y }, { 0,0,0,155 }, 0.2265f, 0.0342222222222222f); //576 × 50
		
		CPauseMenuPage::PageEntry curEntry = page.getAllEntries()[i];
		CTextUI ltext = CTextUI(curEntry.leftDataEntry, { 0.1, 0.2f + (ltext.CharacterHeight(1) * i) }, CRGBA(255, 255, 255, 255));
		if (i == selection_index && isSelectionIndexNegative == false) {
			ltext.colour = { 0,0,0,255 };
			ltext.dropShadow = CTextDropshadow(0, { 0,0,0,0 });
			box.SetColour({ 240,240,240,255 });
		}
		box.Draw();
		ltext.pos = { box.GetCornerPos(box.TOPLEFT).x + 0.005f, box.GetDrawPos().y - ltext.CharacterHeight(.69f) };
		ltext.size = 0.345;
		ltext.Draw();
		scaleform.BeginMethod("SET_BIGFEED_INFO");
		scaleform.LiteralStringPush("");//foot
		scaleform.LiteralStringPush(page.getAllEntries()[selection_index].rightDataEntry);//body
		scaleform.IntegerPush(500);//whichtab?
		scaleform.LiteralStringPush("");//txd
		scaleform.LiteralStringPush("");//txn
		scaleform.LiteralStringPush("");//subtitle
		scaleform.LiteralStringPush("url");//urldep
		scaleform.LiteralStringPush(page.getAllEntries()[selection_index].leftDataEntry);//title
		scaleform.IntegerPush(3);//newstype
		scaleform.EndFunction();
	}
	scaleform.BeginMethod("SET_NEWS_CONTEXT");
	scaleform.IntegerPush(3);
	scaleform.EndFunction();
	//scaleform.BeginMethod("OVERRIDE_SIZE");
	//scaleform.FloatPush(0.1);
	//scaleform.FloatPush(0.5);
	//scaleform.EndFunction();
	scaleform.BeginMethod("initScreenLayout");
	scaleform.LiteralStringPush("LT");
	scaleform.EndFunction();
	scaleform.BeginMethod("SET_DISPLAY_CONFIG");
	//1280, 720, 0.05, 0.95, 0.05, 0.95, true, false, false, 1365.33, 768
	scaleform.IntegerPush(720); //scrwidth
	scaleform.IntegerPush(728); //scr height 
	scaleform.FloatPush(0.05); // safeTop%
	scaleform.FloatPush(0.95);// safebottom%
	scaleform.FloatPush(0.97);// safeLeft%
	scaleform.FloatPush(0.02);// safeRight%
	scaleform.IntegerPush(1); //isWideScreen
	scaleform.IntegerPush(0); // isCircleAccept
	scaleform.IntegerPush(1); // _IsAsian
	scaleform.FloatPush(1365.33); //actualWidth
	scaleform.IntegerPush(768); // actualHeitght
	scaleform.EndFunction();
	scaleform.Draw({ 0.343,0.6659 }, {1,1});
}

void CPauseMenuPaginator::DrawAllPages() {
}

void CPauseMenuPaginator::DrawNavBtn(const char* buffer, CVector2 position, CRGBA boxColor) {
	bool isBoxSelected = false;
	const float selectionHeight = 0.0079875f; // 287 × 55 | 2560 × 1440 | 124 × 25 (important info) verydesc
	CBox box = CBox(position, boxColor, 0.112109375f, 0.0381944444f); // note this works on my screen. find the actual way they render these.
	CBox selectionBox = CBox({ position.x, position.y - ((box.GetHeight() / 2.f) + (selectionHeight/2.f)) }, { 45, 110, 185, 255 }, box.GetWidth(), selectionHeight);
	CTextUI text = CTextUI(buffer, box.GetDrawPos(), {255,255,255,255});
	text.font = text.FONT_CHALET_LONDON;
	//CMiddleJustify justify = CMiddleJustify(); I can see it not liking this
	//text.SetTextJustification(&justify); it does not.
	if (boxColor.r >= 240 && boxColor.g >= 240 && boxColor.b >= 240) {
		isBoxSelected = true;
	}
	text.size = 0.384375f;
	text.textJustification = 0;
	text.pos = { box.GetDrawPos().x, box.GetDrawPos().y - text.CharacterHeight(0.75f) };
	box.Draw(); // draw box before so it spawns lower
	if (isBoxSelected) {
		text.colour = { 0,0,0,255 };
		text.dropShadow = CTextDropshadow(0, { 0,0,0,0 });
		selectionBox.Draw();
	}
	text.Draw();
}

void CPauseMenuPaginator::DrawAllNavButtons() {

}

void CPauseMenuPaginator::DrawAllMenus() {
}

void CPauseMenuPaginator::SetSelection(int selection) {
	this->box_selection = selection; // this can't pose an issue because the developer should check if the status is actually under the max amount of selections.
	return;
}

int CPauseMenuPaginator::GetSelection() {
	return this->box_selection;
}

int CPauseMenuPaginator::GetMaxSelections() {
	return m_Pages.size();
}

void CPauseMenuPaginator::SetPaginatorFocus(bool focus) {
	this->m_bisFocused = focus;
}

bool CPauseMenuPaginator::GetIfPaginatorHasFocus() {
	return this->m_bisFocused;
}
void CPauseMenuPaginator::SetPageInFocus(int page_selection) {
	if (page_selection > m_Pages.size()) {
		return;
	}
	m_Pages[page_selection].second.SetFocus();
	return;
}
int CPauseMenuPaginator::GetPageSelected() {
	return box_selection;
}
CPauseMenuPage* CPauseMenuPaginator::GetPageFromIndex(int index) {
	if (index > m_Pages.size()) {
		return nullptr;
	}
	return &m_Pages[index].second;
}
#include "../../SHVNative/natives.h"

void CPauseMenuPaginator::TransferPage(CPauseMenuPage* page) {
	if (page == nullptr) {
		int gameTimer = MISC::GET_GAME_TIMER();
		while (gameTimer + 5000 > MISC::GET_GAME_TIMER()) {
			CTextUI t = CTextUI(std::string{ "Page passed to TransferPage == null"}, { 0.5,0.5 }, { 255,0,0,255 });
			t.SetTextJustification(0);
			t.size = 1;
			t.Draw();
			WAIT(0);
		}
		return;
	}
	page->SetFocus();
	this->SetPaginatorFocus(false);
	page->Update(); // makes me wanna die lmao.
}

CPauseMenuPage* CPauseMenuPaginator::GetHighlightedPage() {
	return this->m_pPageSelected;
}

void CPauseMenuPaginator::Close() {
	// For this all we are going to do is check if a button is rendered then we'll stop allowing the render. Also we should clean up Update() because its probably covered in bloat from Debugging pause.
}


