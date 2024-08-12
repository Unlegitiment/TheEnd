#pragma once
namespace UIType {
	enum UIType {
		UIT_LIST,
		UIT_PLAYER_LIST,
		UIT_SCALEFORM_INFO,
		UIT_MAX
	};
	typedef UIType UIIdentity;
};
using namespace UIType;
template<UIIdentity ID>
class UIElement {
private:
	UIIdentity id = ID;
public:
	UIIdentity getType() {
		return this->id;
	}
	virtual void Draw() = 0;
};