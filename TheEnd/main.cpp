/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#include "./SHVNative/main.h"
#include "script.h"
#include "keyboard.h"
#include "./Launcher/ScriptDisable.h"
#include "./Logger/CLoggerInstances.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, LoggerThread);
		scriptRegisterAdditionalThread(hInstance, ScriptMainThree);
		scriptRegisterAdditionalThread(hInstance, ScriptMain);
		keyboardHandlerRegister(OnKeyboardMessage);
		break;
	case DLL_PROCESS_DETACH: // you see if I was like competent i would send a event that says that the program is shutting down here so we can call all the program's destroy and cleanup methods. instead of doing it here.
		scriptUnregister(hInstance);
		keyboardHandlerUnregister(OnKeyboardMessage);
		CLogger::GetInst()->GetNetworkLogger()->Cleanup();
		break;
	}		
	return TRUE;
}