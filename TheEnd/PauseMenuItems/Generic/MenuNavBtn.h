#pragma once
#include "../../SHVNative/types.h"
class CMenuNavButton {
private:
	const char* m_Data;
	CRGBA box_color;
	CRGBA box_selection;
	enum eBoxCharacterCol {
		BCC_FRANKLIN = 0,
		BCC_MICHAEL = 1,
		BCC_TREVOR = 2,
		BCC_MP = 3
	};
public:
	static CRGBA getSelectionBoxColor(eBoxCharacterCol colorSelection) {
		switch (colorSelection) {
		case BCC_FRANKLIN:
			return CRGBA(45, 110, 185, 255);
		case BCC_MICHAEL:
			return CRGBA(101, 180, 212, 255);
		case BCC_TREVOR:
			return CRGBA(255, 163, 87, 255);
		case BCC_MP:
			return CRGBA(45, 110, 185, 255);
		} 
	}
};