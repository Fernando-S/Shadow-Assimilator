#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"

#define CAMERA_SPEED 300 // em pixels/s

class Camera{
public:
	static void Follow(GameObject* newFocus);
		static void Unfollow();
		static void Update(float dt);
		static Vec2 pos;
		static Vec2 speed;
		static bool isMoving;
		
private:
	static GameObject* focus;

};

#endif	//CAMERA_H