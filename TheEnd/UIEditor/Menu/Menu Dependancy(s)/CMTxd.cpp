#include "CMTxd.h"
#include "../../../SHVNative/natives.h"

CMTxd::CMTxd(std::string& txd, std::string& txn) :
    txd(txd),
    txn(txn)
{
}

CMTxd::CMTxd(std::string& txd) :
    CMTxd(txd, std::string())
{
}

CMTxd::~CMTxd()
{
    NativeCleanUp();
}

void CMTxd::Request()
{
    GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(txd.c_str(),1);
    while (!isRequested()) { // I am not sure if this would block if the txd was wrong.
        WAIT(0);
    }
}

CMTxd CMTxd::Request(std::string& txd, std::string& txn)
{
    return CMTxd(txd,txn);
}
bool msBooltostdBOOL(BOOL b) {
    if (b == TRUE) {
        return true;
    }
    return false;
}
bool CMTxd::isRequested()
{
    req = msBooltostdBOOL(GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(txd.c_str()));
    return req;
}

void CMTxd::NativeCleanUp()
{
    GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(txd.c_str());
}
