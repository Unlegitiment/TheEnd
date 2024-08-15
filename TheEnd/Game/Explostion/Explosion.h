#pragma once
#include "../../SHVNative/enums.h"
#include <vector>
class CGameWorld;
class CGameEntity;
template<typename T>
class CVector3;
class CExplosion {
private:
	eExplosionType explosionType;
	bool bRequirePTFXRequest; // check it. against a back ground of required explosions.
public:
	struct sExpParams {
		eExplosionType	type;
		CVector3<float>&		position;
		float			effectiveRadius;
		union {
			struct {
				bool requireEffects;
				using ParticleEffect = const char*;
				std::vector<ParticleEffect> m_effect;
			};
		};
	};
};