#pragma once
#include "SolidHeader.h"
class CStylizedHeader : public SSHeader{
public:
	CStylizedHeader(unsigned flags); // 4 bit integer code meaning everything. as to where the style is actually drawn.
	unsigned GetFlags();
private:
	unsigned flags;
	bool hasFlags;
};
class CStylizedHeaderView {
public:
	void Draw(CBox* box, CTextUI* left, CTextUI* right, unsigned DrawFlags);
};
class CStylizedHeaderController {
public:
	
	void Update();
	
private:
	CStylizedHeaderView* view;
	CStylizedHeader*	 header;

};