#include "CFadeScreen.h"
#include "../UIEditor/BoxDraw/CBoxUI.h"
#include "../SHVNative/natives.h"
#include <algorithm>
float CFade::GetFadeProgression() {
	return this->m_fCurrentFade;
}

void CFade::SetFadeProgression(float f) {
	
}

void CFade::DoWhiteScreenFade(bool fadeout) {
	int iR = 255;
	int iG = 255;
	int iB = 255;

	if (fadeout) {
		this->m_FadeColor.a += 5;
	} else {
		this->m_FadeColor.a -= 5;
	}
	this->m_FadeColor.a = std::clamp<float>(this->m_FadeColor.a, 0.0, 255.0);

	GRAPHICS::DRAW_RECT(0.5, 0.5, 3.0, 3.0, iR, iG, iB, this->m_FadeColor.a, 1);

	if (fadeout){
		if (this->m_FadeColor.a >= 255) {
			HoldWhite();
			return;
		}
	} else {
		if (this->m_FadeColor.a <= 0) {
			return;
		}
	}
	scriptLogI("[FADE] called");
}

void CFade::HoldWhite() {
	int iR = 255;
	int iG = 255;
	int iB = 255;
	GRAPHICS::DRAW_RECT(0.5, 0.5, 3.0, 3.0, iR, iG, iB, 255, 1);
}

void CFade::Render() {
}
