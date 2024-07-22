#pragma once
#include <string>
/*
* class Created as like a subclass of CTxd without actually being a subclass. Mainly because I don't want to bring in headshots into this file because I am a idiot and won't rewrite that side of the program.
*/
class CMTxd {
public:
	/*
	Constructor will NOT Request the txd or txn because you should handle that logic yourself.
	You're a programmer do it.
	*/
	CMTxd(std::string& txd, std::string& txn);
	CMTxd(std::string& txd);
	~CMTxd(); 
	void Request(); 
	static CMTxd Request(std::string& txd, std::string& txn); //Quick for creating an object.
	bool isRequested(); //Don't bother checking value rather update isRq and return isRq;
	void NativeCleanUp();
private:
	bool req;
	std::string& txd;
	std::string& txn;
};
