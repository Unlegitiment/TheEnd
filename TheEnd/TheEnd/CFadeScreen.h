#pragma once
#include "../SHVNative/types.h"
class CFade {
	float m_fCurrentFade =  0.0f;
	CRGBA<float> m_FadeColor = { 0,0,0,0 };
	bool m_bIsFading = false;
	bool m_bHoldFade = false;
	bool m_bIsFadingOut = false;
	int m_iLaunchTime = 0;
	
public:
	bool GetIsHoldingFade() { return m_bHoldFade; }
	void DoFadeWhite(int time);
	void DoFadeOutWhite(int time);
	void Update();
};