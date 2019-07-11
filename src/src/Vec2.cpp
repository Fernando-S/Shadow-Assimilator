#include "Vec2.h"

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2::Vec2(){						// Vec2 nulo
	this->x = 0.0;
	this->y = 0.0;
}

Vec2 Vec2::GetRotated(float radians) {
	Vec2 vector;

	vector.x = this->x*std::cos(radians) - this->y*std::sin(radians);
	vector.y = this->y*std::cos(radians) + this->x*std::sin(radians);

	return vector;
}

Vec2 Vec2::operator+(Vec2 vector2) {
	Vec2 vector;

	vector.x = this->x + vector2.x;
	vector.y = this->y + vector2.y;

	return vector;
}

Vec2 Vec2::operator-(Vec2 vector2) {
	Vec2 vector;

	vector.x = this->x - vector2.x;
	vector.y = this->y - vector2.y;

	return vector;
}

Vec2 Vec2::operator*(float c) {
	Vec2 vector;

	vector.x = this->x * c;
	vector.y = this->y * c;

	return vector;
}

float Vec2::Modulo() {
	Vec2 vector;
	float raiz;

	vector.x = this->x * this->x;
	vector.y = this->y * this->y;
	raiz = std::sqrt(vector.x + vector.y);

	return raiz;
}

Vec2 Vec2::Normal() {
	Vec2 normal;
	auto modulo = this->Modulo();

	normal.x = this->x / modulo;
	normal.y = this->y / modulo;

	return normal;
}

float Vec2::Distancia(Vec2 vector2) {
	float dist = (*this - (vector2) ).Modulo();

	return dist;
}

float Vec2::Inclinacao() {
	float tangente = std::atan2(this->y, this->x);

	return tangente;
}

float Vec2::InclinacaoDaDiferenca(Vec2 vector2) {
	Vec2 vector = *this - (vector2);
	float inclinacao = vector.Inclinacao();
	return inclinacao;
}