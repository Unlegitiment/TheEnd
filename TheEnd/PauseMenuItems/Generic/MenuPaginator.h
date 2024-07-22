#pragma once
#include <vector>
#include <map>
#include "../../UIEditor/BoxDraw/CBoxUI.h"
class CPauseMenuPage;
/*
* Goals however right now mean that we need to add a way for the polymorphic abilities. 
* What I mean by this is that we need a way so that the menus handle everything on their own however just supply a base to that. 
* And we force attach them to Pages. 
* Quick defining:
* Page - A total screen of information (not a whole menu just a part of the menu)
* Menu - The general purpose application of general user wide activity.
* Pause Menu - A Pause menu can mean different things while reading HOWEVER. In general its the entire thing around menus. They get created and submenus are added onto the pause menu.
*	This means you DON'T have one global Pause Menu rather submenus that make up a "Pause Menu"
* Contexts - These are short little blabbers in the source that allows MenuItems to have meaning. This is most notibly seen in the Interaction Menu at the bottom of it.
* Paginator - This is what cycles through different menu's. Assets drawn when a specific one is requested.
* Nav - Short for Navigation or Navigational buttons. Typically used above menus and effectively not used in Submenus because they have no reason to have these.
* Scroller - This allows a horizontal or vertical scroll. (Undeveloped yet) that allows the viewer to control whether or not they should see a specific item. Likely set by a global menu variable.
*	* NOTE: Scrollers are as of writing undeveloped as I have no use for them as well the math behind it is a little complex ( for scaling purposes ), as well i'm unsure of how to feed the information to the Draw calls.
* Header - This is defined as a Pause Header; These typically are not super crazy right for things. Pause Headers likely should be Page specific, however as of now they are globally specific. 
*	* Note: This is because the underlying code that creates and manages pages is HIGHLY underengineered. Meaning that to have some sort of menu system that works I have to rewrite those. 
*	* Note: Headers likely have a reason to be page specific. This is because they can and SHOULD be changeable per page. Each page should have FULL control over every UI element on their Page.
* Interface - These are not like the ITextComponent stuff. They are not extensible, however they are core classes that hold global logic. Effectively what they are is like a resource for outside members to access internal details of Menus.
*	Note: As of writing the current PauseInterface.h and the general lineup doesn't work and should NOT be used. This is because I'm still working on Pause Menu logic and so I shall get to higher up code, later.
* Manager - Managers are effectively Object Trackers. What I mean by this is when a specific object that I want tracked is created. I'm allowed to input it in a database of preexisting tracked objects.
*	* Note this goes well with Interfaces. Specifically PauseInterface. When I create a CPauseMenu I have to register it with the PauseInterface. This also allows all derrived classes of CPauseMenu to automatically register with the Manager.
* Focus - These items labeled focus require some context. Its effectively the button set that the View should follow. 
*	* Note: These are not developed yet. I need to develop the Page, Paginator, and Header objects to be more effective at general use cases for UI elements. 
*	* Note: All objects within a focus must be declared. This allows the Focuser to highlight the option and make it clickable. 
*	
*/
/*
* Overall Nice work with this class. However we do have to rewrite some of the stuff. As accordance with Updated guidelines. 
* Generally tho I mean I like this approach to programming. Any drawables like CBox, CTextUI etc. are locked away and the data is the only accessible partition of this. Its rather unique.
*/
class CPauseMenuPaginator {
public:
	void RegisterPage(const char* name, CPauseMenuPage& page);
	void Update(CPauseMenuPage*& __last_page);
	static void DrawPage(CPauseMenuPage& page, int selection_index);
	void DrawAllPages();
	static void DrawNavBtn(const char* buffer, CVector2 position, CRGBA boxColor); // now this is gonna be interesting because each page needs to know some stuff.
	void DrawAllNavButtons();
	void DrawAllMenus();
	void SetSelection(int selection);
	int GetSelection();
	int GetMaxSelections();
	void SetPaginatorFocus(bool focus);
	bool GetIfPaginatorHasFocus();
	void SetPageInFocus(int page_selection);
	int GetPageSelected();
	CPauseMenuPage* GetPageFromIndex(int index);
	void TransferPage(CPauseMenuPage* page);
	CPauseMenuPage* GetHighlightedPage();
	void Close();
private:
	using Item = std::pair<const char*, CPauseMenuPage>;
	int box_selection; // this dictates the page that has the users focus.
	std::vector<Item> m_Pages; // This ties the top thing ([ONLINE] to the "Play GTA Online")
	bool m_bisFocused = true;
	CPauseMenuPage* m_pPageSelected; // this is the highlighted page
};