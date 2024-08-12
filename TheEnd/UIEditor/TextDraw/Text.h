#pragma once
#include <string>
#include "../../SHVNative/types.h"
#include "TextJustify.h"
#include "TextDropshadow.h"
using std::string;
struct s_TextConfig {
	CTextDropshadow&	dropShadow;
	TextJustify&		textJustification;
	bool hasOutline;
	s_TextConfig(CTextDropshadow& _dropShadow, TextJustify& _textJustification, bool _hasOutline):
		dropShadow(_dropShadow),
		textJustification(_textJustification),
		hasOutline(_hasOutline)
	{

	}
};
class CTextUI {
public: // functions
	enum eFonts {
		FONT_CHALET_LONDON = 0,
		FONT_HOUSE_SCRIPT = 1,
		FONT_MONOSPACE = 2,
		FONT_CHALET_COMPRISE_COLOGNE= 4,
		FONT_PRICEDOWN = 7
	};
	CTextUI(string text, CVector2 position, float size, int font, CRGBA colour, CTextDropshadow _dropShadow_, int _justification_, bool _hasOutline_);
	/*
	* @brief We'll handle most things. :)
	* @brief Uses a default size, font, and basic settings allowing more things to apply.
	*/
	CTextUI();
	CTextUI(string text, CVector2 position, CRGBA colour);
	CTextUI operator=(CTextUI & other);
	~CTextUI();
	float CharacterHeight(float iLead);
	static float CharacterHeight(float iLead, float size);
	/// <summary>
	/// Similar to Tick method in other functions. 
	/// This goes within a thread main as it initalized every native call nessicary.
	/// </summary>
	/// 
	void Draw();
	bool getIsDrawn();
	void SetTextJustification(TextJustify* newJustification);
	void SetTextJustification(int newJust);
	void DrawDebugInfo(float x, float yOffset = 17.0F);
	void DrawDebugText(const std::string& debugText, float x, float yOffset, int lineIndex);
public: //variables 
	string text;
	CVector2 pos;
	CRGBA colour;
	float size;
	int font; //make font enum? (yes)
	CTextDropshadow dropShadow;
	int textJustification;
	bool hasOutline;
protected://Subclasses (someday)
	void setDrawn(bool drawState);
private: // Variables
	bool isDrawn;
};
