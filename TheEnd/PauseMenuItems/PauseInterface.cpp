#include "PauseInterface.h"

CPauseMenuMgr* MenuInterface::GetPauseMgr() {
    return MenuMgr;
}
CPauseMenuMgr* MenuInterface::MenuMgr = new CPauseMenuMgr(); //kewl
