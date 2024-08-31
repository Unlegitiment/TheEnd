#pragma once
#include "./HelpText.h"
/*
	Interfacing with the Game's help Text System already present
*/
class CGameHelpText : private CHelpText{ 
private:
	bool isFlashing;
public:
	const char* GetHelpString();
	void SetHelpText(const char* text);
	void RenderNow();
	bool CanHelpTextRender();
	void SetHelpTextCanRender(bool b);
	/*
		Warn must be a stable capture of time for fDelta. If you don't have a stable it will persistantly display.
	*/
	void RenderForTime(float fDelta, int msToDisplay);
};