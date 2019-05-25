#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::Rect() {								// Rect nulo
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0.0;
	this->h = 0.0;
}

bool Rect::Contains(Vec2 vector) {
	if ( (vector.x >= this->x) && ( vector.x <= (this->x + this->w) ) &&
		 (vector.y >= this->y) && ( vector.y <= (this->y + this->h) ) )
		return true;
	else
		return false;
}

Vec2 Rect::Center() {
	Vec2 vector;

	vector.x = this->x + this->w/2;
	vector.y = this->y + this->h/2;

	return vector;
}

void Rect::Centralize() {
	x = x - (w/2);
	y = y - (h/2);
}

Rect Rect::operator+(Vec2 vector) {
	Rect rect;

	rect.x = this->x + vector.x;
	rect.y = this->y + vector.y;
	rect.w = this->w;
	rect.h = this->h;

	return rect;
}

Rect Rect::operator=(Vec2 vector) {
	this->x = vector.x;
	this->y = vector.y;
	return *this;
}

Rect Rect::operator+=(Vec2 vector) {
	this->x += vector.x;
	this->y += vector.y;
	return *this;
}

void Rect::PlaceCenter(Vec2 pos) {
	x = pos.x - (w/2);
	y = pos.y - (h/2);
}
