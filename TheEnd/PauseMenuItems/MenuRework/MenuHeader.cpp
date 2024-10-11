#include "MenuHeader.h"

baseHeader::baseHeader(const CVector2<float> offset) : fOffset((CVector2<float>)offset){
}

CVector2<float>& baseHeader::GetOffset() {
    return this->fOffset;
}
