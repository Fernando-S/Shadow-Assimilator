#include "Alien.h"
#include "Game.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions, float timeOffset) : Component(associated) {
	speed = {0, 0};
	hp = ALIEN_MAX_HP;
	Minions = nMinions;
	state = RESTING;
	destination = {0, 0};

	associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
	associated.AddComponent(new Collider(associated));
	alienCount++;
}


Alien::~Alien() {
	minionArray.clear();			// Esvazia o array com minions
	alienCount--;
}

void Alien::Start() {
	GameObject* minionGO = nullptr;
	Minion* minion = nullptr;
	double minionArc = 0;
	int i;

	// Carrega os minions
	for (i = 0; i < Minions; i++) {	
		minionGO = new GameObject();
		minionArc = i * 2 * PI / Minions;
//		minion = new Minion(*minionGO, Game::GetInstance().GetState().GetObjectPtr(&associated)/*, this*/, (float)minionArc);
		minion = new Minion(*minionGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated)/*, this*/, (float)minionArc);

		minionGO->AddComponent(minion);
//		minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGO));
		minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(minionGO));
	}
}

void Alien::Update(float dt) {
	int i;

	if (hp <= 0) {
		associated.RequestDelete();				// Remove o Alien se ele nao tem mais vida

		// Carrega a animacao e som de explosao da morte do Alien
		auto explosionGO = new GameObject();
		auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/aliendeath.png", 4, 0.15, 1.2));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
//		Game::GetInstance().GetState().AddObject(explosionGO);
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);
	}
	else {
		associated.angleDeg += ALIEN_ANGULAR_SPEED * dt;

		if (PenguinBody::player) {
			// Descansa enquanto o timer ainda nao terminou
			if (state == RESTING && restTimer.Get() < ALIEN_RESTING_TIME)
				restTimer.Update(dt);
			else if (state == RESTING) {		// Obtem posicao do jogador
				destination = PenguinBody::player->GetCenter();

				speed = { 1, 0 };
				speed = speed.GetRotated(destination.InclinacaoDaDiferenca(associated.box.Center()));

				state = MOVING;

			}	// Atira contra o jogador se chegou ao destino
			else if (state == MOVING && destination.Distancia(associated.box.Center()) <= ALIEN_SPEED * dt) {
				associated.box.PlaceCenter(destination);

				destination = PenguinBody::player->GetCenter();

				if (Minions > 0) {
					auto closestMinionGO = minionArray[0].lock();
					auto minionGO = closestMinionGO;

					for (i = 1; i < Minions; i++) {
						minionGO = minionArray[i].lock();

						if (closestMinionGO.get() && minionGO.get()) { 			// verifica se os dois shared_ptrs estao populados
							if (destination.Distancia({ minionGO->box.x,minionGO->box.y }) <
								destination.Distancia({ closestMinionGO->box.x,closestMinionGO->box.y }))
								closestMinionGO = minionGO;					// Se ha algum minion mais perto, eh ele que deve atirar
							else
								closestMinionGO = closestMinionGO;			// Se nao, mantem-se o mesmo atirador
						}
					}

					auto closestMinion = (Minion*)closestMinionGO->GetComponent("Minion");
					closestMinion->Shoot(destination);		// Atira no destino calculado
				}

				restTimer.Restart();		// Resta o timer

				state = RESTING;
			}
			else if (state == MOVING)		// Realiza o movimento do Alien
				associated.box += speed * ALIEN_SPEED*dt;
		}
	}

}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
	if (type == "Alien")
		return true;
	else
		return false;
}

void Alien::NotifyCollision(GameObject &other) {
	auto bullet = (Bullet*)other.GetComponent("Bullet");

	// Prosfere dano ao Alien se o tiro for do jogador
	if ((bullet && !bullet->targetsPlayer) && bullet->playerBullet /*|| minionHit*//* || MinionGotHit()*/) {
		hp -= bullet->GetDamage();
		std::cout << "Vida do ALIEN: " << hp << std::endl;
	}
}