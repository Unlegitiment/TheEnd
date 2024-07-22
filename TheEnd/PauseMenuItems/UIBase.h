#pragma once
class CUIBase { // 
public:
	enum eUIType {
		UIT_PLAYERS,
		UIT_DESCRIPTION,
		UIT_LIST,
		UIT_JOB_DESC
	};
private:
	eUIType eType; // 
public:
	CUIBase(eUIType t);
	eUIType getType();
	void setType(eUIType t);
	virtual void Draw();
};