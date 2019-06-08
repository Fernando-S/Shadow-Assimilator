#include "PenguinCannon.h"
#include "Game.h"


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> playerBody) : Component(associated) {
	pbody = playerBody;
	angle = 0;

	// Carrega o sprite do PenguinCannon
	auto sprite = new Sprite(associated, "./assets/img/cubngun.png");
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	associated.angleDeg = angle * 180 / PI;
}

void PenguinCannon::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	auto playerBody = pbody.lock();

	// Checa se o Penguin ainda existe
	if (playerBody) {
		// Calculo do angulo para o canhao seguir o mouse
		associated.box.PlaceCenter(playerBody->box.Center());
		angle = Vec2(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y).InclinacaoDaDiferenca(associated.box.Center());
		associated.angleDeg = angle * 180 / PI;
		cooldownTimer.Update(dt);

		// Atira somente se o tempo de cooldown do tiro ja tiver passado
		if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && cooldownTimer.Get() > PENGUIN_SHOOTING_COLLDOWN) {
			Shoot();
			cooldownTimer.Restart();
		}
	}
	else
		associated.RequestDelete();			// Exlui o Penguin caso ele nao exista mais
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
	if (type == "PenguinCannon")
		return true;
	else
		return false;
}

void PenguinCannon::Shoot() {

	// Carrega o tiro do Penguin
	auto bulletGO = new GameObject();
	auto bullet = new Bullet(*bulletGO, angle, PENGUIN_BULLET_SPEED, std::rand() % 11 + PENGUIN_BULLET_MAX_DAMAGE - 10,
							 PENGUIN_BULLET_MAX_DISTANCE, "./assets/img/penguinbullet.png",	4, 0.2);
	bullet->playerBullet = true;

	bulletGO->AddComponent(bullet);
	bulletGO->box.PlaceCenter(associated.box.Center());

	auto bulletPos = Vec2(associated.box.w / 2, 0);
	bulletPos = bulletPos.GetRotated(angle);

	bulletGO->box += bulletPos;

//	Game::GetInstance().GetState().AddObject(bulletGO);
	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}


void PenguinCannon::NotifyCollision(GameObject& other) {

}
