#define NOMINMAX
#include "CFadeScreen.h"
#include "../UIEditor/BoxDraw/CBoxUI.h"
#include "../SHVNative/natives.h"
#include <algorithm>

void CFade::DoFadeWhite(int time) {
	this->m_bIsFading = true;
	this->m_iLaunchTime = time;
	scriptLogI("Starting fade with: ", this->m_iLaunchTime);
}

void CFade::DoFadeOutWhite(int time) {
	this->m_bIsFading = false;
	this->m_iLaunchTime = time;
	this->m_bIsFadingOut = true;
}

void CFade::Update() {
	const float duration = 1000;
	if (this->m_bIsFading) {
		if (m_iLaunchTime + duration > MISC::GET_REAL_WORLD_TIME() ) { // currently fading
			float fElapsed = (MISC::GET_GAME_TIMER() - this->m_iLaunchTime);
			float t = std::min(fElapsed / duration, 1.0f);
			float fFadeAmount = (t * t);
			int alpha = static_cast<int>(fFadeAmount * 255);
			//scriptLogI("\n\tfElapsed: ", fElapsed, "\n\tt: ", t, "\n\tfFadeAmount: ", fFadeAmount, "\n\tAlpha: ",alpha);
			GRAPHICS::DRAW_RECT(0.5, 0.5, 1, 1, 0, 0, 0, alpha, true);
			if (t >= 0.960f) {
				scriptLogI("[FADE] t >= 1.0f, t:", t);
				this->m_bHoldFade = true;
				this->m_bIsFading = false;
			}
		}
	} 
	if (m_bHoldFade) {
		GRAPHICS::DRAW_RECT(0.5, 0.5, 1, 1, 0, 0, 0, 255, 0);
	}
	if (m_bIsFadingOut) { // we need to start from 255 and go down;
		if (m_iLaunchTime + duration > MISC::GET_REAL_WORLD_TIME()) { // currently fading
			this->m_bHoldFade = false;
			float fElapsed = (MISC::GET_GAME_TIMER() - this->m_iLaunchTime);
			float t = std::min(fElapsed / duration, 1.0f);
			float fFadeAmount = 1.0f - (t * t);
			int alpha = static_cast<int>(fFadeAmount * 255);
			GRAPHICS::DRAW_RECT(0.5, 0.5, 1, 1, 0, 0, 0, alpha, true);
			if (t >= 0.960f) {
				scriptLogI("[FADE] t >= 1.0f, t:", t);
				this->m_bIsFadingOut = false;
			}
		}
	}
}
