#pragma once
#include "../SHVNative/types.h"
class CFade {
	float m_fCurrentFade =  0.0f;
	CRGBA<float> m_FadeColor = { 0,0,0,0 };
public:
	float GetFadeProgression();
	void SetFadeProgression(float f);
	void DoWhiteScreenFade(bool fadeout);
	void HoldWhite();
	void Render();
};