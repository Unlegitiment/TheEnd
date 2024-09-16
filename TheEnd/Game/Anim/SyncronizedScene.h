#pragma once
#include "../../SHVNative/types.h"
#include <vector>
class CSynchronizedScene {
private:
	bool m_bIsSynchronizedSceneSetup = false;
	bool m_bCanSceneRun = false;
	bool m_bIsSynchronizedSceneDone = false;
	bool m_bIsSceneRunning = false;
	bool m_bIsSceneInitalized = false;
	std::string m_AnimDictionary = "";
	struct sAnimationData {
		float fAnimProgression = 0.0f;
		const char* pAnimName;
		Entity ObjectInScene;  
		float blendIn = 1.0f, blendOut = 1.0f, moverBlendDelta = 0.0f;
		int flags = 0, ragdollBlockingFlags = 0, ikFlags = 0;
	};
	float m_fSceneProgression = 0.0f;
	int m_iSceneId = -1;
	CVector3<float> Position = {0,0,0};
	CVector3<float> Rotation = { 0,0,0 };
	std::vector<sAnimationData> m_Animations;
public:
	std::string& GetAnimDictionary();
	void SetupScene(const char* animdictionary, CVector3<float> pos, CVector3<float> rot);
	void QueueAnimation(int entityHandle, const char* name);
	sAnimationData* GetAnimation(int index);
	virtual void RunScene();
	float GetSceneProgression(); 
	void ReportAllInformationToLogger();
	void Destroy();
};