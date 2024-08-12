#pragma once
#include "../../Textures/CTXD.h"
#include <cstring>
class CPauseMenuHeader {
private:
public:
	struct PauseInfo {
		char header[200];
		char subheader[200];
		char date[16];
		char character[16];
		char additional_info[16];
		CTxd texture;
		PauseInfo() : texture(CTxd("pedmugshot_01", "pedmugshot_01")){
			std::memset(header, 0, sizeof(header));
			std::memset(subheader, 0, sizeof(subheader));
			std::memset(date, 0, sizeof(date));
			std::memset(character, 0, sizeof(character));
			std::memset(additional_info, 0, sizeof(additional_info));
		}
		PauseInfo(const char* head, const char* subhead, const char* _date, const char* _character, const char* _add_info) : texture({"pedmugshot_01", "pedmugshot_01"}) {
			std::strncpy(header, head, sizeof(header) - 1);
			std::strncpy(subheader, subhead, sizeof(subheader) - 1);
			std::strncpy(date, _date, sizeof(date) - 1);
			std::strncpy(character, _character, sizeof(character) - 1);
			std::strncpy(additional_info, _add_info, sizeof(additional_info) - 1);
			header[sizeof(header) - 1] = '\0';
			subheader[sizeof(subheader) - 1] = '\0';
			date[sizeof(date) - 1] = '\0';
			character[sizeof(character) - 1] = '\0';
			additional_info[sizeof(additional_info) - 1] = '\0';
			return;
		}
	};
private:
	PauseInfo* pauseInfo;
public:
	CPauseMenuHeader(PauseInfo* info);
	PauseInfo* getInfo();
	void setInfo(PauseInfo* info);
	static void DrawHeader(CPauseMenuHeader& header);
	static void DrawMissionDetails(CPauseMenuHeader& info);
	static void DrawTime(CPauseMenuHeader& info);
	static void DrawCharacter(CPauseMenuHeader& info);
	static void DrawMoney(CPauseMenuHeader& info);
	static void DrawCharSprite(CPauseMenuHeader& info);
};