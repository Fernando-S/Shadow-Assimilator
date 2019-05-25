#pragma once

#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
	float x, y, w, h;
	Rect(float x, float y, float w, float h);
	Rect();
	bool Contains(Vec2 vector);
	Vec2 Center();
	void Centralize();
	void PlaceCenter(Vec2 pos);

	Rect operator+(Vec2 vec);
	Rect operator=(Vec2 vec);
	Rect operator+=(Vec2 vec);
	
};

#endif	//RECT_H