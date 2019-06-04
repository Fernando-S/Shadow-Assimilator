#pragma once

#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include <iostream>
#include "Component.h"

class CameraFollower: public Component {
public:
		CameraFollower(GameObject& go/*, bool adjCenter = false*/);
		void Update(float dt);
		void Render();
		bool Is(std::string type);

private:
	//bool adjustCenter;

	//void AdjustCenter();
};

#endif	//CAMERAFOLLOWER_H