#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

class GameObject;

class Component {
public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool Is(std::string type) = 0;
	virtual void Start();
	virtual void NotifyCollision(GameObject& other);

protected:
	GameObject& associated;

};

#endif	//COMPONENT_H