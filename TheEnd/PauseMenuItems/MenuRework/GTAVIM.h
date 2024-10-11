#pragma once
#include "./Item.h"
#include "./Menu.h"
#include "./MenuHeader.h"
#include "../../SHVNative/types.h"
#include <vector>
/*
	I just realized what I am doing in my head. Im artificially representing the menuItem class in a way that it should know how to draw the object. 
	In reality thats upto the specific button.

*/
class CGTAVMenu : baseMenu{
public:
	class CGTAVHeader : public baseHeader{
	private:
		const char* MenuPlayerName;
		const char* MenuName;
		const char* MenuIndex;
	public:
		CGTAVHeader(const char* param0, const char* param1, const char* param2); // header text, menu name, menu index
		const char* GetPlayerName() { return this->MenuPlayerName; }
		const char* GetMenuName() { return this->MenuName; }
		const char* GetMenuIndex() { return this->MenuIndex; }
		void Draw();
	};
private:
	bool m_bIsMenuShown;
	std::vector<baseMenuItem*> items;
	CGTAVHeader m_Header;
private:
	CVector2<float>& MenuPos;
public:
	CGTAVMenu(const CVector2<float>& __menubasepos);
	void AddItem(baseMenuItem* item);
	void Show();
	void Hide(); 
};