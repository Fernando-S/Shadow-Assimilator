#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {
}

void CameraFollower::Update(float dt) {
	associated.box.x = associated.initialX + Camera::pos.x;
	associated.box.y = associated.initialY + Camera::pos.y;

}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
	if (type == "CameraFollower")
		return true;
	else
		return false;
}