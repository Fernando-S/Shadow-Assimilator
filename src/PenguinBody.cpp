#include "PenguinBody.h"
#include "Game.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define PLAYER_SPEED 400

using namespace std;

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated)/*, pcannon() */{
	player = this;
	speed = { 1, 0 };
	linearSpeed = 0;
	angle = 0;
	oppositeAccel = 0;
	oppositeSpeed = 0;
	hp = PENGUIN_INITIAL_HP;

	// Carrega o sprite do PenguinBody
//	auto sprite = new Sprite(associated, "./assets/img/penguin.png");
//	auto sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
	SetSprite("./assets/img/sprite_idle.png", 12, 0.1);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	associated.angleDeg = angle * 180 / PI;
}

PenguinBody::~PenguinBody() {
	player = nullptr;
}

void PenguinBody::Start() {
	/*
	// Adiciona ao PenguinCannon
	auto cannonGO = new GameObject();
	//	auto cannon = new PenguinCannon(*cannonGO, Game::GetInstance().GetState().GetObjectPtr(&associated));
	auto cannon = new PenguinCannon(*cannonGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
	cannonGO->AddComponent(cannon);

	//	pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
	pcannon = Game::GetInstance().GetCurrentState().AddObject(cannonGO);
	*/
}

void PenguinBody::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;

	if (hp <= 0) {
		// Deleta os Penguins se o hp deles acabou
		associated.RequestDelete();
		//pcannon.lock()->RequestDelete();
		Camera::Unfollow();				// Camera para de segui-los

		// Toca o som e mostra a explosao
		auto explosionGO = new GameObject();
		auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/penguindeath.png", 5, 0.1, 1.5));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);
	}
	else {
	double accelSpeedGain = PENGUIN_ACCELERATION * dt;

	// Acelera ou Desacelera os Penguins dependendo da tecla pressionada
	if (inputManager.IsKeyDown(W_KEY) && (PENGUIN_MAX_LINEAR_SPEED - abs(linearSpeed) > accelSpeedGain)) {
		speed = { 0, -1 };
		linearSpeed += accelSpeedGain;
	}
	else if (inputManager.IsKeyDown(S_KEY) && (PENGUIN_MAX_LINEAR_SPEED - abs(linearSpeed) > accelSpeedGain)) {
		speed = { 0, -1 };
		linearSpeed -= accelSpeedGain;		// Acelera

	}
	else if (inputManager.IsKeyDown(A_KEY)) {

		if (linearSpeed == 0)
			oppositeSpeed = 0;

		if (Getspeed1 == false) {
			oppositeSpeed = linearSpeed;
			cout << "\n\nPassarvalor1" << endl << endl;
			Getspeed1 = true;
		}

		speed = { -1, 0 };
		if (oppositeSpeed > -PLAYER_SPEED) {

			if (oppositeSpeed > 0) {
				oppositeSpeed -= accelSpeedGain;
				linearSpeed = -oppositeSpeed;
			}
			if (oppositeSpeed <= 0) {
				oppositeSpeed -= accelSpeedGain;
				linearSpeed = -oppositeSpeed;
			}
		}
		else
			linearSpeed = -oppositeSpeed;

		cout << "linearSpeed1: " << linearSpeed << endl;
		cout << "oppositeSpeed1: " << oppositeSpeed << endl;
		//SetSprite("./assets/img/sprite_corrida.png", 12, 0.1);
	}

	else if (inputManager.IsKeyDown(D_KEY)) {
		speed = { 1, 0 };

		if (linearSpeed == 0)
			oppositeSpeed = 0;

		if (Getspeed2 == false) {
			oppositeSpeed = linearSpeed;
			cout << "\n\nPassarvalor2" << endl << endl;
			Getspeed2 = true;
		}

		if (linearSpeed < PLAYER_SPEED + 50) {

			if (oppositeSpeed >= 0) {
				oppositeSpeed -= accelSpeedGain;
				linearSpeed = -oppositeSpeed;
			}
			else {
				linearSpeed += accelSpeedGain;
			}

		}
		cout << "linearSpeed2: " << linearSpeed << endl;
		cout << "oppositeSpeed2: " << oppositeSpeed << endl;
		//cout << linearSpeed << endl;

		setaNovoSprite = true;
		moving = true;
	}


	double atrictSpeedLoss = PENGUIN_ATRICT * dt;

	/*
	if (abs(linearSpeed) > atrictSpeedLoss) {
		linearSpeed -= (linearSpeed < 0) ? -1 * atrictSpeedLoss : atrictSpeedLoss;
		Rect newPos = associated.box + speed * linearSpeed*dt;

		if (newPos.Center().x > PENGUIN_WALKING_LIMIT_X_MIN && newPos.Center().x < PENGUIN_WALKING_LIMIT_X_MAX
			&& newPos.Center().y > PENGUIN_WALKING_LIMIT_Y_MIN && newPos.Center().y < PENGUIN_WALKING_LIMIT_Y_MAX) {
			associated.box = newPos;
		}
	}
	else {
		linearSpeed = 0;
	}
	*/

	if (!(inputManager.IsKeyDown(A_KEY)))
		Getspeed1 = false;

	if (!(inputManager.IsKeyDown(D_KEY)))
		Getspeed2 = false;


		if ((!(inputManager.IsKeyDown(A_KEY))) && (!(inputManager.IsKeyDown(D_KEY))) && (!(inputManager.IsKeyDown(W_KEY))) && (!(inputManager.IsKeyDown(S_KEY)))) {
			if (linearSpeed > 0)
				linearSpeed -= accelSpeedGain;
			else if (linearSpeed < 0)
				linearSpeed += accelSpeedGain;
		}

		// Aplica atrito no movimento acelerado do Penguin

		if (abs(linearSpeed) > atrictSpeedLoss) {
			if (linearSpeed < 0)
				linearSpeed -= -1 * atrictSpeedLoss;
			else
				linearSpeed -= atrictSpeedLoss;

			//speed = { 1, 0 };
			associated.box += speed * linearSpeed*dt;
		}
		else 
			linearSpeed = 0;

	}



/*
	if ( inputManager.KeyRelease(A_KEY) && inputManager.KeyRelease(D_KEY) &&
		 inputManager.KeyRelease(W_KEY) && inputManager.KeyRelease(S_KEY) && (linearSpeed == 0)) {
		moving = false;
		setaNovoSprite = true;
	}
*/

/*
	if (linearSpeed == 0) {
		moving = false;
		setaNovoSprite = true;
	}
*/

	// todo - pensar em como trocar de parado para andando e de andando para parado
	if (setaNovoSprite) {
		associated.RemoveComponent(sprite);
		if (moving)
			SetSprite("./assets/img/sprite_corrida2.png", 12, 0.1);
		else
			SetSprite("./assets/img/sprite_idle.png", 12, 0.1);
		associated.AddComponent(sprite);
		setaNovoSprite = false;
	}
	
}


void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
	if (type == "PenguinBody")
		return true;
	else
		return false;
}


void PenguinBody::NotifyCollision(GameObject& other) {
	auto bullet = (Bullet*)other.GetComponent("Bullet");

	// Prosfere dano ao jogador se o tiro for dos Aliens
	if ((bullet && bullet->targetsPlayer) && bullet->alienBullet) {
		std::cout << "Vida do Penguin: " << hp << std::endl;
		hp -= bullet->GetDamage();
	}
}

Vec2 PenguinBody::GetCenter() {
	return associated.box.Center();
}

void PenguinBody::SetSprite(const char* file, int frameCount, float frameTime) {
	sprite = new Sprite(associated, file, frameCount, frameTime);
}

/*
bool PenguinBody::IsMoving() {
	return moving;
}
*/