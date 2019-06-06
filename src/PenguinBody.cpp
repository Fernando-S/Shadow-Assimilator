#include "PenguinBody.h"
#include "Game.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define PLAYER_SPEED 400
#define PLAYER_JUMP 600

using namespace std;

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated)/*, pcannon() */ {
	player = this;
	speedH = { 1, 0 };
	speedV = { 0, -1 };
	linearSpeed = 0;
	angle = 0;
	oppositeAccel = 0;
	oppositeSpeed = 0;
	hp = PENGUIN_INITIAL_HP;

	// Carrega o sprite da personagem idle
	sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);

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

	}
	else {
		double accelSpeedGain = PENGUIN_ACCELERATION * dt;

		// todo - ver se esse eh o lugar certo da gravidade
		//associated.box.y += 100 * dt;


		if (verticalSpeed == PLAYER_JUMP) {
			Quedalivre = true;
		}
		//cout << "\nJump: " << Jump << endl;

		if ((verticalSpeed <= PLAYER_JUMP) && (verticalSpeed > 0)) {
			if (Jump < 10) {
				Jump++;
				//cout << "\nJump: " << Jump;
			}
		}
		//cout << "\nverticalSpeed: " << verticalSpeed;
		if ((tchfloor == false) && (Quedalivre == true)) {
			if (verticalSpeed > -900) {
				verticalSpeed -= accelSpeedGain * 0.9; //QUEDA
				//cout << "\ndecrementa\n";
				//cout << "\nverticalSpeed: " << verticalSpeed;
			}

		}



		// Acelera ou Desacelera os Penguins dependendo da tecla pressionada
		if (inputManager.IsKeyDown(W_KEY) && (Floorgrab == true) && (Jump == 0)) {
			Jump++;
			verticalSpeed = 0;
			tchfloor = false;
			verticalSpeed = PLAYER_JUMP;
			Setjump = true;
		}
		else if (inputManager.IsKeyDown(S_KEY) && (PENGUIN_MAX_LINEAR_SPEED - abs(linearSpeed) > accelSpeedGain)) {

			linearSpeed -= accelSpeedGain;		// Acelera
		}
		else
			if (inputManager.IsKeyDown(A_KEY)) {

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

				speedH = { -1, 0 };
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

				//std::cout << "linearSpeed1: " << linearSpeed << endl;
				//std::cout << "oppositeSpeed1: " << oppositeSpeed << endl;

			}
			else if (inputManager.IsKeyDown(D_KEY)) {
				speedH = { 1, 0 };

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

				//cout << "linearSpeed: " << linearSpeed << endl;
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
				linearSpeed -= accelSpeedGain * 1.5;

			}
			if (linearSpeed < -40) {
				linearSpeed += accelSpeedGain * 1.5;
			}
			if ((linearSpeed < 40) && (linearSpeed > -40)) {
				linearSpeed = 0;
			}

			if (Stop < 10) {
				Stop++;
				if (Stop == 1) {
					Setrun = false;
				}
			}
			Setidle = true;

			//cout << "Stop: " << Stop << endl;

		}
		//////////////////////////////////////////////////////////////
		/////////////////////VELOCIDADE///////////////////////////////

		//if (Wallgrab == false) {
		associated.box += speedH * linearSpeed*dt;
		//}
		associated.box += speedV * verticalSpeed*dt;

		//cout << "Centro: " << GetCenter().y << endl;
		cout << "Centro: " << chao << endl;
		

		//////////////////////////////////////////////////////////////

		if ((Stop == 2) || (Run == 1) || (Run == -1) || (Jump == 1)) {
			cout << "\n\nSetidle: " << Setidle << "\nSetrun: " << Setrun << "\nStop: " << Stop << "\nlinearspeed: " << linearSpeed << "\n\n";
		}

		// Idle para a direita
		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);

			// arruma a hitbox da personagem animacao idle
			associated.box.w = 80;
			//associated.box.x += 64;

			associated.AddComponent(sprite);

			cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Idle para a esquerda
		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);

			// arruma a hitbox da personagem para animacao idle
			associated.box.w = 80;
			//associated.box.x += 64;

			associated.AddComponent(sprite);
			cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Corrida para a direita
		if ((Setidle == false) && (Setrun == true) && (Run == 1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);

			// arruma a hitbox da personagem
			//associated.box.w = 80;
			//associated.box.x += 64;

			associated.AddComponent(sprite);


			cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}

		// Corrida para a esquerda
		if ((Setidle == false) && (Setrun == true) && (Run == -1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);

			// arruma a hitbox da personagem
			//associated.box.w = 80;
			//associated.box.x += 64;

			associated.AddComponent(sprite);


			cout << "\nTROCA, PARA > CORRE ESQUERDA\n\n";
		}

		// Pulo para a direita
		if ((Setidle == false) && (Setjump == true)) {
			////////////////////////
			//	SPRITE DE PULO PARA A DIREITA
			////////////////////////


			cout << "\nTROCA, PULO DIREITA\n\n";
		}

		// Pulo para a esquerda
		if ((Setidle == false) && (Setjump == true) && (Run == -1)) {
			////////////////////////
			//	SPRITE DE PULO PARA A ESQUERDA
			////////////////////////

			cout << "\nTROCA, PULO ESQUERDA\n\n";
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
	auto tile = (TileMap*)other.GetComponent("TileMap");

	// Prosfere dano ao jogador se o tiro for dos Aliens
	if ((bullet && bullet->targetsPlayer) && bullet->alienBullet) {
		std::cout << "Vida do Penguin: " << hp << std::endl;
		hp -= bullet->GetDamage();
	}

	//tile.DistRecs(associated.box.y);

	// todo - pensar em como fazer essa colisao com o chao
	if (tile) {
		if (tile->floor) {
			//this->associated.box.y = tile->GetY() - this->associated.box.h - 1;	// flica q nem louco
			this->associated.box.y = tile->GetY() - this->associated.box.h;		// trava sem poder fazer o pulo
			cout << "colidiu com o chao\n";
			verticalSpeed = 100;
			associated.box += speedV * verticalSpeed*0.035;
			verticalSpeed = 0;
			Jump = 0;


			Setjump = false;
			tchfloor = true;
			Quedalivre = false;
			Floorgrab = true;
		}
		else if (!(tile->floor) && (tchfloor == false)) {
			Floorgrab = false;
		}
		if (tile->wall) {
			Wallgrab = true;
			cout << "colidiu com o parede\n";
		}
		else {
			Wallgrab = false;
		}

	}


}

Vec2 PenguinBody::GetCenter() {
	return associated.box.Center();
}

//Vec2 PenguinBody::GetFloor() {
	//return floor.box.DistRecs(associated.box.y);
//}