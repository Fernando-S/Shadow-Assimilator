#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go/*, bool adjCenter*/) : Component(go) {
	//adjustCenter = adjCenter;
}

void CameraFollower::Update(float dt) {
	associated.box.x = Camera::pos.x;
	associated.box.y = Camera::pos.y;

	/*if (adjustCenter) {
		AdjustCenter();
		associated.box.Centralize();
		//associated.SetCenter();
	}*/
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
	if (type == "CameraFollower")
		return true;
	else
		return false;
}
/*
void CameraFollower::AdjustCenter() {
	associated.box.x += 1280 / 2;
	associated.box.y += 480 / 2;
}*/