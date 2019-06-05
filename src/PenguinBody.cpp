#include "PenguinBody.h"
#include "Game.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define PLAYER_SPEED 400

using namespace std;

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated)/*, pcannon() */ {
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
	//sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
	sprite_runningR = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
	sprite_runningL = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);
	sprite_idleR = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
	sprite_idleL = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);
	SetSprite("./assets/img/sprite_idle.png", 12, 0.1);

	//sprite = sprite_idleR;
	//sprite = sprite_runningR;

	associated.AddComponent(sprite);
	//associated.AddComponent(sprite_idleR);
	//associated.AddComponent(sprite_runningR);
	//associated.ChangeComponent(sprite, sprite_idle);

	//associated.AddComponent(new Collider(associated));
	//associated.angleDeg = angle * 180 / PI;
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




	}
	else {
		double accelSpeedGain = PENGUIN_ACCELERATION * dt;
		/*
		// Acelera ou Desacelera os Penguins dependendo da tecla pressionada
		if (inputManager.IsKeyDown(W_KEY) && (PENGUIN_MAX_LINEAR_SPEED - abs(linearSpeed) > accelSpeedGain)) {
			speed = { 0, -1 };
			linearSpeed += accelSpeedGain;
		}
		else if (inputManager.IsKeyDown(S_KEY) && (PENGUIN_MAX_LINEAR_SPEED - abs(linearSpeed) > accelSpeedGain)) {
			speed = { 0, -1 };
			linearSpeed -= accelSpeedGain;		// Acelera
		}
		else*/ if (inputManager.IsKeyDown(A_KEY)) {

			if (linearSpeed == 0)
				oppositeSpeed = 0;

			if (Getspeed1 == false) {
				oppositeSpeed = linearSpeed;
				std::cout << "\n\nPassarvalor1" << endl << endl;
				Getspeed1 = true;
				Setidle = false;
				Setrun = true;
				Run = 0;
				Stop = 0;
			}

			if (Run > -10) {
				Run--;
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

			std::cout << "linearSpeed1: " << linearSpeed << endl;
			std::cout << "oppositeSpeed1: " << oppositeSpeed << endl;
			//SetSprite("./assets/img/sprite_corrida.png", 12, 0.1);

			// Controle de flags de animacao
			setaNovoSprite = true;
			startedMovingR = false;
			startedMovingL = true;
			idleR = false;
			idleL = false;
		}
		else if (inputManager.IsKeyDown(D_KEY)) {
			speed = { 1, 0 };

			if (Getspeed2 == false) {
				oppositeSpeed = linearSpeed;
				std::cout << "\n\nPassarvalor2" << endl << endl;
				Getspeed2 = true;

				Run = 0;
				Stop = 0;
				Setidle = false;
				Setrun = true;

			}

			if (Run < 10) {
				Run++;
			}

			if (linearSpeed < PLAYER_SPEED + 50) {

				if (oppositeSpeed >= 0) {
					oppositeSpeed -= accelSpeedGain;
					linearSpeed = -oppositeSpeed;
				}
				else
					linearSpeed += accelSpeedGain;

			}

			//cout << "Run: " << Run << endl;
		}

		double atrictSpeedLoss = PENGUIN_ATRICT * dt;

		if (!(inputManager.IsKeyDown(A_KEY)))
			Getspeed1 = false;

		if (!(inputManager.IsKeyDown(D_KEY))) {
			Getspeed2 = false;
		}

		if ((!(inputManager.IsKeyDown(A_KEY))) && (!(inputManager.IsKeyDown(D_KEY))) && (!(inputManager.IsKeyDown(W_KEY))) && (!(inputManager.IsKeyDown(S_KEY)))) {

			if (linearSpeed > 40) {
				linearSpeed -= accelSpeedGain;
			}
			if (linearSpeed < -40) {
				linearSpeed += accelSpeedGain;
			}
			if ((linearSpeed < 40) && (linearSpeed > -40)) {
				linearSpeed = 0;
			}


			//cout << "linearSpeed: " << linearSpeed << endl;
			//cout << "Stop: " << Stop << endl;

			//startedMovingR = false;
			//idleR = true;
			//setaNovoSprite = true;
		}

		// Aplica atrito no movimento acelerado do Penguin

		if (abs(linearSpeed) > atrictSpeedLoss) {
			if (linearSpeed < 0)
				linearSpeed -= -1 * atrictSpeedLoss;
			else
				linearSpeed -= atrictSpeedLoss;
			associated.box += speed * linearSpeed*dt;
		}
		else {
			linearSpeed = 0;

			if (Stop < 10) {
				Stop++;
				if (Stop == 1) {
					Setrun = false;
				}
			}
			Setidle = true;

		}

		if ((Stop == 2) || (Run == 1) || (Run == -1)) {
			cout << "\n\nSetidle: " << Setidle << "\nSetrun: " << Setrun << "\nStop: " << Stop << "\nlinearspeed: " << linearSpeed << "\n\n";
		}

		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run > 0)) {	//para pra direita
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
			associated.AddComponent(sprite);

			cout << "\nTROCA, CORRE > PARA\n\n";
		}

		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run < 0)) {	//para pra esquerda
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);
			associated.AddComponent(sprite);

			cout << "\nTROCA, CORRE > PARA\n\n";
		}

		if ((Setidle == false) && (Setrun == true) && (Run == 1)) {		//corre
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
			associated.AddComponent(sprite);


			cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}
		if ((Setidle == false) && (Setrun == true) && (Run == -1)) {		//corre
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);
			associated.AddComponent(sprite);


			cout << "\nTROCA, PARA > CORRE ESQUERDA\n\n";
		}
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
	auto chao = (TileMap*)other.GetComponent("TileMap");

	// Prosfere dano ao jogador se o tiro for dos Aliens
	if ((bullet && bullet->targetsPlayer) && bullet->alienBullet) {
		std::cout << "Vida do Penguin: " << hp << std::endl;
		hp -= bullet->GetDamage();
	}

	// todo - pensar em como fazer essa colisao com o chao
	/*
	if (chao->associated.box.y) {
	}
	*/
}

Vec2 PenguinBody::GetCenter() {
	return associated.box.Center();
}

void PenguinBody::SetSprite(const char* file, int frameCount, float frameTime) {
	sprite = new Sprite(associated, file, frameCount, frameTime);
}