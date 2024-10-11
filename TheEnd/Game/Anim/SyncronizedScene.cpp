#include "SyncronizedScene.h"
#include "../../SHVNative/natives.h"
#include <cassert>
std::string& CSynchronizedScene::GetAnimDictionary() {
	return this->m_AnimDictionary;
}
void CSynchronizedScene::SetupScene(const char* animdictionary, CVector3<float> pos, CVector3<float> rot) {
	if (!STREAMING::DOES_ANIM_DICT_EXIST(animdictionary)) {
		scriptLogW("[SYNCHRONIZED_SCENE] %s Does not exist!", animdictionary);
		return;
	}
	while (!STREAMING::HAS_ANIM_DICT_LOADED(animdictionary)) {
		STREAMING::REQUEST_ANIM_DICT(animdictionary);
		WAIT(0);
	}
	if (!this->m_bIsSceneInitalized) {
		this->m_AnimDictionary = animdictionary;
		this->Position = pos;
		this->Rotation = rot;
		this->m_bIsSceneInitalized = true;
	}
}

void CSynchronizedScene::QueueAnimation(int entityHandle, const char* name) {
	this->m_Animations.push_back({ 0.0f, name, entityHandle});
}

CSynchronizedScene::sAnimationData* CSynchronizedScene::GetAnimation(int index) {
	if (index > this->m_Animations.size()) return nullptr;
	return &this->m_Animations[index];
}
#include "../../UIEditor/TextDraw/Text.h"
void CSynchronizedScene::RunScene() {
	if (!this->m_bIsSynchronizedSceneSetup) {
		this->m_iSceneId = PED::CREATE_SYNCHRONIZED_SCENE(this->Position.x, this->Position.y, this->Position.z, this->Rotation.x, this->Rotation.y, this->Rotation.z, 2);
		this->m_bCanSceneRun = true;
		this->m_bIsSynchronizedSceneSetup = true;
	}
	if (this->m_bCanSceneRun && !this->m_bIsSceneRunning) {
		scriptLogI("[SYNCHRONIZE SCENE] Scene ID: %i (AnimDict: %s): can run", this->m_iSceneId, this->m_AnimDictionary.c_str());
		for (int i = 0; i < this->m_Animations.size(); i++) {
			sAnimationData* curAnim = &this->m_Animations[i];
			assert(curAnim != nullptr, "Anim is null");
			TASK::TASK_SYNCHRONIZED_SCENE(curAnim->ObjectInScene, this->m_iSceneId, this->m_AnimDictionary.c_str(), curAnim->pAnimName, curAnim->blendIn,
				curAnim->blendOut, curAnim->flags, curAnim->ragdollBlockingFlags, curAnim->moverBlendDelta, curAnim->ikFlags);
		}
		this->m_bIsSceneRunning = true;
	}
	if (this->m_bIsSceneRunning) {
		if (this->GetSceneProgression() >= 1.0f) {
			scriptLogI("[SYNCHRONIZED_SCENE] %s  has finished running.", this->m_AnimDictionary);
			this->m_bIsSynchronizedSceneDone = true;
			this->m_bIsSceneRunning = false;
		}
	}
}

float CSynchronizedScene::GetSceneProgression() {
	return PED::GET_SYNCHRONIZED_SCENE_PHASE(this->m_iSceneId);
}

void CSynchronizedScene::ReportAllInformationToLogger() {
}
void CSynchronizedScene::Destroy() {
	this->m_Animations.clear();
	this->m_AnimDictionary = "";
	this->m_bCanSceneRun = false;
	this->m_bIsSceneInitalized = false;
	this->m_bIsSceneRunning = false;
	this->m_bIsSynchronizedSceneDone = false;
	this->m_bIsSynchronizedSceneSetup = false;
	this->m_fSceneProgression = 0.0f;
	this->m_iSceneId = -1;
	this->Position = { 0,0,0 };
	this->Rotation = { 0,0,0 };
}
/*
	For later this is just a base implementation of Synchronized Scenes. However if we want we can write a manager class and write a CSyncSceneWrapper 
	which takes two parameters and assigns them to each other.
	One being the actual CSynchronizedScene itself and the other being the object's owner/manager.
	The Manager would probably be like a Singleton with an update loop removing all animations that happen to be finished with their animation loop however with the specification of a flag you could probably save this. (for later)


*/