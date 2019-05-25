#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"


class Collider : public Component{
public:
	Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
	Rect box;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);
		
private:
	Vec2 scale;
	Vec2 offset;

};

#endif	//COLLIDER_H