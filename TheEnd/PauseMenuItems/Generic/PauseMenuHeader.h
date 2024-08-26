#pragma once
#include "../../Textures/CTXD.h"
#include <cstring>
class CPauseMenuHeader {
private:
	char m_pHeader[200];
	char m_pSubheader[200];
	char m_pDate[16];
	char m_pCharacter[16];
	char m_pAdditional_info[16];
	CTxd m_Texture;
public:
	CPauseMenuHeader(char* header, char* subheader, char* date, char* character, char* add_info);
	static void DrawHeader(CPauseMenuHeader& header);
	static void DrawMissionDetails(CPauseMenuHeader& info);
	static void DrawTime(CPauseMenuHeader& info);
	static void DrawCharacter(CPauseMenuHeader& info);
	static void DrawMoney(CPauseMenuHeader& info);
	static void DrawCharSprite(CPauseMenuHeader& info);
};