#pragma once
class CGameSpinner {
public:
	enum eBusySpinnerType {
		BUSY_SPINNER_LEFT,
		BUSY_SPINNER_LEFT_2,
		BUSY_SPINNER_LEFT_3,
		BUSY_SPINNER_SAVE,
		BUSY_SPINNER_RIGHT,
	};
	void SetType(eBusySpinnerType e) { this->m_Type = e; }
	void SetText(const char* text);
	const char* GetText();
	void StartRender();
	void ForceStopRender();
private:
	const char* m_Text;
	eBusySpinnerType m_Type;
};