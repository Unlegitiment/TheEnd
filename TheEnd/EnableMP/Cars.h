#pragma once
#include "../SHVNative/main.h"
#include <Psapi.h>
#include "Windows.h"
#define STATIC_ASSERT_SIZE(Type, Size) static_assert(sizeof(Type) == Size, "invalid " #Type " size")


struct ScriptHeader {
    char padding1[16];                    //0x0
    unsigned char** codeBlocksOffset;    //0x10
    char padding2[4];                    //0x18
    int codeLength;                        //0x1C
    char padding3[4];                    //0x20
    int localCount;                        //0x24
    char padding4[4];                    //0x28
    int nativeCount;                    //0x2C
    __int64* localOffset;                //0x30
    char padding5[8];                    //0x38
    __int64* nativeOffset;                //0x40
    char padding6[16];                    //0x48
    int nameHash;                        //0x58
    char padding7[4];                    //0x5C
    char* name;                            //0x60
    char** stringsOffset;                //0x68
    int stringSize;                        //0x70
    char padding8[12];                    //0x74
    //END_OF_HEADER

    bool IsValid() const { return codeLength > 0; }
    int CodePageCount() const { return (codeLength + 0x3FFF) >> 14; }
    int GetCodePageSize(int page) const {
        return (page < 0 || page >= CodePageCount() ? 0 : (page == CodePageCount() - 1) ? codeLength & 0x3FFF : 0x4000);
    }
    unsigned char* GetCodePageAddress(int page) const { return codeBlocksOffset[page]; }
    unsigned char* GetCodePositionAddress(int codePosition) const {
        return codePosition < 0 || codePosition >= codeLength ? NULL : &codeBlocksOffset[codePosition >> 14][codePosition & 0x3FFF];
    }
    char* GetString(int stringPosition)const {
        return stringPosition < 0 || stringPosition >= stringSize ? NULL : &stringsOffset[stringPosition >> 14][stringPosition & 0x3FFF];
    }

};

#pragma pack(pop)

struct ScriptTableItem {
    ScriptHeader* Header;
    char padding[4];
    int hash;

    inline bool IsLoaded() const {
        return Header != NULL;
    }
};

struct ScriptTable {
    ScriptTableItem* TablePtr;
    char padding[16];
    int count;
    ScriptTableItem* FindScript(int hash) {
        if (TablePtr == NULL) {
            return NULL;//table initialisation hasnt happened yet
        }
        for (int i = 0; i < count; i++) {
            if (TablePtr[i].hash == hash) {
                return &TablePtr[i];
            }
        }
        return NULL;
    }
};
struct GlobalTable {
    __int64** GlobalBasePtr;
    __int64* AddressOf(int index) const { return &GlobalBasePtr[index >> 18 & 0x3F][index & 0x3FFFF]; }
    bool IsInitialised()const { return *GlobalBasePtr != NULL; }
};
GlobalTable globalTable;
ScriptTable* scriptTable;
ScriptHeader* shopController;
uintptr_t FindPattern(const char* pattern, const char* mask, const char* startAddress, size_t size) {
    const char* address_end = startAddress + size;
    const auto mask_length = static_cast<size_t>(strlen(mask) - 1);

    for (size_t i = 0; startAddress < address_end; startAddress++) {
        if (*startAddress == pattern[i] || mask[i] == '?') {
            if (mask[i + 1] == '\0') {
                return reinterpret_cast<uintptr_t>(startAddress) - mask_length;
            }
            i++;
        } else {
            i = 0;
        }
    }
    return 0;
}

uintptr_t FindPattern(const char* pattern, const char* mask) {
    MODULEINFO modInfo = { };
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof(MODULEINFO));

    return FindPattern(pattern, mask, reinterpret_cast<const char*>(modInfo.lpBaseOfDll), modInfo.SizeOfImage);
}
bool findShopController() {
    // FindPatterns
    __int64 patternAddr = FindPattern("\x4C\x8D\x05\x00\x00\x00\x00\x4D\x8B\x08\x4D\x85\xC9\x74\x11", "xxx????xxxxxxxx");
    if (!patternAddr) {
        return false;
    }
    globalTable.GlobalBasePtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);


    patternAddr = FindPattern("\x48\x03\x15\x00\x00\x00\x00\x4C\x23\xC2\x49\x8B\x08", "xxx????xxxxxx");
    if (!patternAddr) {

        return false;
    }
    scriptTable = (ScriptTable*)(patternAddr + *(int*)(patternAddr + 3) + 7);

    DWORD startTime = GetTickCount();
    DWORD timeout = 10000; // in millis

    // FindScriptAddresses
    while (!globalTable.IsInitialised()) {
        scriptWait(100); //Wait for GlobalInitialisation before continuing
        if (GetTickCount() > startTime + timeout) {

            return false;
        }
    }

    //logger.Write(INFO, "Found global base pointer " + std::to_string((__int64)globalTable.GlobalBasePtr));

    ScriptTableItem* Item = scriptTable->FindScript(0x39DA738B);
    if (Item == NULL) {

        return false;
    }
    while (!Item->IsLoaded())
        Sleep(100);

    shopController = Item->Header;
    //logger.Write(INFO, "Found shopcontroller");
    return true;
}

void enableCarsGlobal() {
    const char* patt617_1 = "\x2C\x01\x00\x00\x20\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
    const char* mask617_1 = "xx??xxxxxx?xx????xxxx?x";
    const unsigned int offset617_1 = 13;

    const char* patt1604_0 = "\x2D\x00\x00\x00\x00\x2C\x01\x00\x00\x56\x04\x00\x6E\x2E\x00\x01\x5F\x00\x00\x00\x00\x04\x00\x6E\x2E\x00\x01";
    const char* mask1604_0 = "x??xxxx??xxxxx?xx????xxxx?x";
    const unsigned int offset1064_0 = 17;

    // Updated pattern entirely thanks to @alexguirre
    const char* patt2802_0 = "\x2D\x00\x00\x00\x00\x2C\x01\x00\x00\x56\x04\x00\x71\x2E\x00\x01\x62\x00\x00\x00\x00\x04\x00\x71\x2E\x00\x01";
    const char* mask2802_0 = "x??xxxx??xxxxx?xx????xxxx?x";
    const unsigned int offset2802_0 = 17;

    const char* pattern = patt617_1;
    const char* mask = mask617_1;
    int offset = offset617_1;

    if (getGameVersion() >= 80) {
        pattern = patt2802_0;
        mask = mask2802_0;
        offset = offset2802_0;
    } else if (getGameVersion() >= 46) {
        pattern = patt1604_0;
        mask = mask1604_0;
        offset = offset1064_0;
    }

    for (int i = 0; i < shopController->CodePageCount(); i++) {
        int size = shopController->GetCodePageSize(i);
        if (size) {
            uintptr_t address = FindPattern(pattern, mask, (const char*)shopController->GetCodePageAddress(i), size);
            if (address) {
                int globalindex = *(int*)(address + offset) & 0xFFFFFF;
                *globalTable.AddressOf(globalindex) = 1;
                return;
            }
        }
    }

}

void Init() {
    uintptr_t addr;

    if (getGameVersion() <= 57) {
        addr = FindPattern(
            "\x0F\xB7\x05\x00\x00\x00\x00"
            "\x45\x33\xC9\x4C\x8B\xDA\x66\x85\xC0"
            "\x0F\x84\x00\x00\x00\x00"
            "\x44\x0F\xB7\xC0\x33\xD2\x8B\xC1\x41\xF7\xF0\x48"
            "\x8B\x05\x00\x00\x00\x00"
            "\x4C\x8B\x14\xD0\xEB\x09\x41\x3B\x0A\x74\x54",
            "xxx????"
            "xxxxxxxxx"
            "xx????"
            "xxxxxxxxxxxx"
            "xx????"
            "xxxxxxxxxxx");

        if (!addr) {
        }
    } else {
        addr = FindPattern("\xEB\x09\x41\x3B\x0A\x74\x54", "xxxxxxx");
        if (!addr) {
        }
        addr = addr - 0x2C;
    }


    // find enable MP cars patterns
    if (findShopController())
        enableCarsGlobal();

    

}