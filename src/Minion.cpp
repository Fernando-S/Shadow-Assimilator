#include "Minion.h"
#include "Game.h"


//Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alCenter, float arcOffsetDeg) : Component(associated), alienCenter(*(alCenter.lock().get())), arc(arcOffsetDeg*PI / 180){
Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	//this->alienCenter = *alienCenter.lock().get() ;
	this->alienCenter = alienCenter;
	arc = arcOffsetDeg;
	
	// Carrega o Minion
	auto minion = new Sprite(associated, "./assets/img/minion.png");
	auto randScale = (std::rand() % 51 + 100) / 100.0;
	minion->SetScale(randScale, randScale);
	associated.AddComponent(minion);
	associated.AddComponent(new Collider(associated));

	Vec2 initialPos(RADIUS, 0);
	initialPos = initialPos.GetRotated(arcOffsetDeg);

	//auto alienGO = alienCenter;
	auto alienGO = alienCenter.lock();

//	if (alienGO.GetComponent("Alien")) {
	if(alienGO){
//		associated.box = alienGO.box.Center() + initialPos;
		associated.box = alienGO->box.Center() + initialPos;
		associated.box.Centralize();
	}
	else {
		std::cout << "ERROR: null pointer to GameObject Alien!" << std::endl;
		associated.RequestDelete();
	}

}

void Minion::Update(float dt) {
	// Mantem o Minion em orbita
//	auto alienGO = alienCenter;
	auto alienGO = alienCenter.lock();
	
//	if (alienGO.GetComponent("Alien")) {
	if(alienGO){
		Vec2 pos(RADIUS, 0);

		arc += ANGULAR_SPEED * dt;

		associated.angleDeg = (180 / PI)*arc;

		pos = pos.GetRotated(arc);
//		associated.box = alienGO.box.Center() + pos;
		associated.box = alienGO->box.Center() + pos;
		associated.box.Centralize();
	}
	else {
		associated.RequestDelete();

		// Carrega a animacao da explosao da morte do Minion
		auto minionExplosionGO = new GameObject();
		minionExplosionGO->AddComponent(new Sprite(*minionExplosionGO, "./assets/img/miniondeath.png", 4, 0.15, 1.2));
		minionExplosionGO->box.PlaceCenter(associated.box.Center());
//		Game::GetInstance().GetState().AddObject(minionExplosionGO);
		Game::GetInstance().GetCurrentState().AddObject(minionExplosionGO);
	}
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	if (type == "Minion")
		return true;
	else
		return false;
}

void Minion::Shoot(Vec2 target) {
	// Carrega um Tiro
	auto bulletGO = new GameObject();
	bulletGO->box = associated.box.Center();

	auto bullet = new Bullet(*bulletGO, target.InclinacaoDaDiferenca(associated.box.Center()), BULLET_SPEED,
							 std::rand() % 11 + BULLET_MAX_DAMAGE - 10,	BULLET_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	bullet->alienBullet = true;
	bulletGO->AddComponent(bullet);

//	Game::GetInstance().GetState().AddObject(bulletGO);
	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}

// decidir se o minion deve morrer separadamente ou nao
void Minion::NotifyCollision(GameObject& other) {
	auto bullet = (Bullet*)other.GetComponent("Bullet");

	// conseguir nao bugar isso e dar dano no Alien
	if (bullet /*&& !bullet->targetsPlayer*/ && bullet->playerBullet)
		std::cout << "Minion acertado! Mas nao deu dano..." << std::endl;
}
