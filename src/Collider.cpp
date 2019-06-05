#include "Collider.h"


#define DEBUG		// Comentar isso no jogo final para nao ver as hitboxes

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include "SDL.h"
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	Collider::scale = scale;
	Collider::offset = offset;
}

void Collider::Update(float dt) {
	// Box de colisao se torna uma copia da box do GameObject
	box = associated.box;

	// Multiplica a box de colisao pela escala
	box.w *= scale.x;
	box.h *= scale.y;

	// Centraliza a box de colisao com a box do GameObject e orienta sua direcao
	box.PlaceCenter(associated.box.Center());
	box += offset.GetRotated(associated.angleDeg * PI / 180);
}

void Collider::Render() {
	// Forma de ver, em tempo de execucao, se as hitboxes estao corretas
#ifdef DEBUG
	Vec2 center(box.Center());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[1] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[2] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x, box.y + box.h) - center).GetRotated(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
	if (type == "Collider")
		return true;
	else
		return false;
}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}

