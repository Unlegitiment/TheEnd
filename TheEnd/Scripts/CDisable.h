#pragma once
#include <vector>
#include <string>
class CDisableScripts {
private:
	using ScrName = const char*;
	struct ScrInfo {
		bool isDisabled;
		ScrName name;
	};
	std::vector<ScrInfo> m_AllScriptsToDisable;
	bool m_ForceRefresh;
public:
	void PushBackScript(ScrName name);
	void Update();
	void ClearAllScripts();
	void Destroy();
	static bool RestartScript(ScrName name, int stackSize); // this is in development a nullsub rn
	std::string GetLogStatement();
};