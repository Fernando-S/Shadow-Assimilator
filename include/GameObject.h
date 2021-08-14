#pragma once

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

#include <vector>
#include <tr1/memory>
#include "Component.h"
#include "Rect.h"


class GameObject {
public:
	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void ChangeComponent(Component* cpt, Component* newCPT);
	void RemoveComponent(Component *cpt);
	void NotifyCollision(GameObject& other);

	Component* GetComponent(std::string type);
	Rect box;
	void Start();
	double angleDeg;
	bool render = true;
	int initialX = 0, initialY = 0;

private:
	std::vector<std::shared_ptr<Component>> components;
	bool isDead;
	bool started;

};

#endif	//GAMEOBJECT_H