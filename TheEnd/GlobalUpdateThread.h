#pragma once
#include "./Game/CGameWorld.h"
#include "./SHVNative/types.h"
#include "./SHVNative/main.h"
//Uhoh raggy!

__forceinline void scriptUpdateGameWorld(CGameWorld* m_WorldPointer) {
	m_WorldPointer->Update();
}
typedef Singleton<CGameWorld> sGameWorld;

__forceinline void ScriptMainThree() {
	sGameWorld::GetInstance()->Init();
	while (true) {
		scriptUpdateGameWorld(sGameWorld::GetInstance());
		scriptWait(0);
	}
}