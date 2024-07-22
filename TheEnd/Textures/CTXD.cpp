#include "CTXD.h"
#include "../SHVNative/natives.h"
CTxd::CTxd(const char* dictionary, const char* name): textureDict(dictionary), textureName(name){
    while (!IsReady()) {
        Request();
        WAIT(0);
    }
}
void* CTxd::operator new(size_t buffer) {
    void* p = ::operator new(buffer); 
    return p;
}
void CTxd::Request() { //Doesn't call the wait 
    GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(this->textureDict, 1);
}

bool CTxd::IsReady() {
    return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(this->textureDict);
}

const char* CTxd::getDict() {
    return this->textureDict;
}

const char* CTxd::getName() {
    return this->textureName;
}

void CTxd::Remove() {
    GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(this->textureDict);
}