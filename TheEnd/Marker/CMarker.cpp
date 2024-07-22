#include "CMarker.h"
#include "../SHVNative/natives.h"
CMarker::CMarker(eMarkerType type, CVector3 pos, CVector3 dir, CVector3 rot, CVector3 scale, CRGBA rgba, bool bob, bool faceCam, int drawRot, bool rotate, CTxd* txd, bool drawOnEnter, bool p24) :
	m_Type(type),
	pos(pos),
	dir(dir),
	rotation(rot),
	scale(scale),
	rgba(rgba),
	bob(bob),
	faceCam(faceCam),
	drawRot(drawRot),
	rotate(rotate),
	texture(txd), // this will get auto deleted right? we just gonna get fucked by stack.
	drawonEnt(drawOnEnter),
	p24(p24)
{
}
#include <string>
void CMarker::Draw() {
	GRAPHICS::DRAW_MARKER_EX((int)this->m_Type,
		//pos
		this->pos.x,
		this->pos.y,
		this->pos.z,
		this->dir.x,
		this->dir.y,
		this->dir.z,
		this->rotation.x,
		this->rotation.y,
		this->rotation.z,
		this->scale.x,
		this->scale.y,
		this->scale.z,
		this->rgba.r,
		this->rgba.g,
		this->rgba.b,
		this->rgba.a,
		bob,
		faceCam,
		this->drawRot,
		rotate,
		this->texture->getDict(),
		this->texture->getName(),
		drawonEnt,
		p24,1
		);
}

CMarker::eMarkerType CMarker::getType() {
	return this->m_Type;
}

CVector3 CMarker::getPos() {
	return this->pos;
}

CVector3 CMarker::getDir() {
	return this->dir;
}

CVector3 CMarker::getRot() {
	return this->rotation;
}

CVector3 CMarker::getScale() {
	return this->scale;
}

CRGBA CMarker::getColor() {
	return this->rgba;
}

bool CMarker::getIfMarkerBobs() {
	return this->bob;
}

bool CMarker::getIfMarkerFacesCam() {
	return this->faceCam;
}

bool CMarker::getIfMarkerRotates() {
	return this->rotate;
}

bool CMarker::getIfMarkerDrawsOnEnter() {
	return this->drawonEnt;
}

int CMarker::getDrawRotation() {
	return this->drawRot;
}

CTxd* CMarker::getTxd() {
	return this->texture;
}
