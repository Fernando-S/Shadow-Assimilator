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
	sprite_runningR = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
	sprite_runningL = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
	sprite_idleR = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
	sprite_idleL = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
	SetSprite("./assets/img/sprite_idle.png", 12, 0.1);
	
	associated.AddComponent(sprite);
	//associated.AddComponent(sprite_idle);
	//associated.AddComponent(sprite_running);
	//associated.ChangeComponent(sprite, sprite_idle);

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
		
										/*
		// Toca o som e mostra a explosao
		auto explosionGO = new GameObject();
		auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/penguindeath.png", 5, 0.1, 1.5));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);
		*/


		/*
		// Tentativa do Negrao de fazer animacao funcionar
		if ((Getspeed2 == true) && (Setrun == true)) {
			Setrun = false;
			associated.RemoveComponent(sprite);
			auto CorridaGO = new GameObject();
			auto explosionSound = new Sound(*CorridaGO, "./assets/audio/boom.wav");
			CorridaGO->AddComponent(new Sprite(*CorridaGO, "./assets/img/sprite_corrida2.png", 12, 0.1, 1.5));
			//system("PAUSE");
			CorridaGO->AddComponent(explosionSound);
			explosionSound->Play();
			CorridaGO->box.PlaceCenter(associated.box.Center());
			Game::GetInstance().GetCurrentState().AddObject(CorridaGO);

			std::cout << "\n\nCORRIDA\n\n";
			associated.AddComponent(sprite);
		}

		if ((Getspeed2 == false) && (Setidle == true)) {
			std::cout << "Setidle: " << Setidle << endl;
			std::cout << "Getspeed2: " << Getspeed2 << endl;
			system("PAUSE");
			Setidle = false;
			associated.RemoveComponent(sprite);
			auto IdleGO = new GameObject();
			auto explosionSound = new Sound(*IdleGO, "./assets/audio/boom.wav");
			IdleGO->AddComponent(new Sprite(*IdleGO, "./assets/img/sprite_idle.png", 12, 0.1, 1.5));
			//system("PAUSE");
			IdleGO->AddComponent(explosionSound);
			explosionSound->Play();
			IdleGO->box.PlaceCenter(associated.box.Center());
			Game::GetInstance().GetCurrentState().AddObject(IdleGO);

			std::cout << "\n\nCORRIDA\n\n";
			associated.AddComponent(sprite);
		}
		*/



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

			//	Setrun = true;
			//	SwitchSetidle = 0;
			}

			if (linearSpeed < PLAYER_SPEED + 50) {

				if (oppositeSpeed >= 0) {
					oppositeSpeed -= accelSpeedGain;
					linearSpeed = -oppositeSpeed;
				}
				else
					linearSpeed += accelSpeedGain;

			}
			std::cout << "linearSpeed2: " << linearSpeed << endl;
			std::cout << "oppositeSpeed2: " << oppositeSpeed << endl;
			//cout << linearSpeed << endl;

			// Controle de flags de animacao
			setaNovoSprite = true;
			startedMovingR = true;
			startedMovingL = false;
			idleR = false;
			idleL = false;
		}

		double atrictSpeedLoss = PENGUIN_ATRICT * dt;

		if (!(inputManager.IsKeyDown(A_KEY)))
			Getspeed1 = false;

		if (!(inputManager.IsKeyDown(D_KEY)))
			Getspeed2 = false;

		/*
		// Tambem eh tentativa do Negrao de fazer a animacao funcion/ar
		if (!(inputManager.IsKeyDown(D_KEY))) {
			//a avariável SwitchSetidle serve para que Setidle seja setado apenas uma vez
			if ((Setidle == false) && (SwitchSetidle == false)) {
				Setidle = true;
				SwitchSetidle = true;
			}
			else 
				Setidle = false;

			Getspeed2 = false;
		}
		*/

		if ((!(inputManager.IsKeyDown(A_KEY))) && (!(inputManager.IsKeyDown(D_KEY))) && (!(inputManager.IsKeyDown(W_KEY))) && (!(inputManager.IsKeyDown(S_KEY)))) {

			if (linearSpeed > 40)
				linearSpeed -= accelSpeedGain;
			else if (linearSpeed < -40)
				linearSpeed += accelSpeedGain;
			else if (linearSpeed < 40) {
				if (linearSpeed != 0)
					linearSpeed--;
			}
			else if (linearSpeed > -40) {
				if (linearSpeed != 0)
					linearSpeed--;
			}
			//std::cout << "linearSpeed: " << linearSpeed << endl;

			//startedMoving = false;
			//idle = true;
			//setaNovoSprite = true;
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
		else {
			linearSpeed = 0;


			startedMovingR = false;
			idleR = true;
			setaNovoSprite = true;
		}

	}




	// todo - pensar em como trocar de parado para andando e de andando para parado
	if (setaNovoSprite) {
	//	associated.RemoveComponent(sprite);
	//	if (startedMoving && !alreadyMoving) {
	//		SetSprite("./assets/img/sprite_corrida2.png", 12, 0.1);
	//		startedMoving = false;
	//		alreadyMoving = true;
	//6	}
	//	else if (idle) {
	//		SetSprite("./assets/img/sprite_idle.png", 12, 0.1);
	//		idle = false;
	//	}
		//associated.AddComponent(sprite);
		if (startedMovingR) {
			associated.ChangeComponent(sprite, sprite_runningR);
			//associated.ChangeComponent(sprite_idleR, sprite_runningR);
			
			//sprite->Open("./assets/img/sprite_corrida2.png");
			//sprite->SetFrameCount(12);
			//sprite->SetFrameTime(0.1);
			//sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
		}
		else if (idleR) {
			associated.ChangeComponent(sprite_runningR, sprite_idleR);
			//associated.ChangeComponent(sprite_runningR, sprite);
		}
		/*else if (startedMovingL) {
			//associated.ChangeComponent(sprite, sprite_runningR);
			associated.ChangeComponent(sprite_idleR, sprite_runningR);
		}
		else if (idleR)
			associated.ChangeComponent(sprite_runningR, sprite_idleR);
		*/

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

/*
bool PenguinBody::IsMoving() {
	return moving;
}
*/