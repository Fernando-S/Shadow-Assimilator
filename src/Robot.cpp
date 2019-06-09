#include "Robot.h"
#include "Game.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define ROBOT_SPEED 400
#define ROBOT_JUMP 600

using namespace std;

Robot* Robot::robot = nullptr;

Robot::Robot(GameObject& associated) : Component(associated)/*, pcannon() */ {
	robot = this;
	speedH = { 1, 0 };
	speedV = { 0, -1 };
	linearSpeed = 0;
	angle = 0;
	oppositeAccel = 0;
	oppositeSpeed = 0;
	hp = ROBOT_INITIAL_HP;

	// Carrega o sprite da personagem idle
	sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);

	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

Robot::~Robot() {
	robot = nullptr;
}

void Robot::Start() {
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

void Robot::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;

	if (hp <= 0) {
		// Deleta os Penguins se o hp deles acabou
		associated.RequestDelete();
		//pcannon.lock()->RequestDelete();
		Camera::Unfollow();				// Camera para de segui-los

	}
	else {
		double accelSpeedGain = ROBOT_ACCELERATION * dt;

		// aplica gravidade funcional a todo momento
		if (verticalSpeed > -900) {
			verticalSpeed -= accelSpeedGain * 0.9; //QUEDA
		}

		if (inputManager.KeyRelease(SPACE_KEY)) {
			associated.box.PlaceCenter(Vec2(694, 100));
			airbone = true;
			tchfloor = false;
		}

		
		if (inputManager.IsKeyDown(I_KEY) && tchfloor && !airbone) {

			verticalSpeed = ROBOT_JUMP;

			tchfloor = false;
			airbone = true;
			doubleJump = false;
		}
		else
			if (inputManager.IsKeyDown(J_KEY)) {

				if (linearSpeed == 0)
					oppositeSpeed = 0;

				if (Getspeed1 == false) {
					oppositeSpeed = linearSpeed;
					//std::cout << "\n\nPassarvalor1" << endl << endl;
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
				if (oppositeSpeed > -ROBOT_SPEED) {

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
			else if (inputManager.IsKeyDown(L_KEY)) {
				speedH = { 1, 0 };

				if (Getspeed2 == false) {
					oppositeSpeed = linearSpeed;
					//std::cout << "\n\nPassarvalor2" << endl << endl;
					Getspeed2 = true;

					Run = 0;
					Stop = 0;
					Setidle = false;
					Setrun = true;

				}

				if (Run < 10) {
					Run++;
				}

				if (linearSpeed < ROBOT_SPEED + 50) {

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

		double atrictSpeedLoss = ROBOT_ATRICT * dt;

		if (!inputManager.IsKeyDown(J_KEY))
			Getspeed1 = false;

		if (!inputManager.IsKeyDown(L_KEY)) {
			Getspeed2 = false;
		}

		if (!inputManager.IsKeyDown(J_KEY) && !inputManager.IsKeyDown(L_KEY) /*&& !inputManager.IsKeyDown(I_KEY)/* && !inputManager.IsKeyDown(K_KEY)*/) {

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
		//cout << "Centro: " << chao << endl;
		

		//////////////////////////////////////////////////////////////

		// Idle para a direita
		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
			
			/// todo - isso arruma a posicao quando colide com algo a direita, mas andar a direita fica estranho
			// arruma a posicao para o sprite do personagem idle aparecer do pe mais a frente apos a corrida
			//associated.box.x += associated.box.w;//121;

			associated.AddComponent(sprite);

			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Idle para a esquerda
		if ((Setidle == true) && (Setrun == false) && (Stop == 2) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);

			associated.AddComponent(sprite);
			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Corrida para a direita
		if ((Setidle == false) && (Setrun == true) && (Run == 1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);

			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}

		// Corrida para a esquerda
		if ((Setidle == false) && (Setrun == true) && (Run == -1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);

			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE ESQUERDA\n\n";
		}

		// Pulo para a direita
		if ((Setidle == false) && (Setjump == true)) {
			////////////////////////
			//	SPRITE DE PULO PARA A DIREITA
			////////////////////////


			//cout << "\nTROCA, PULO DIREITA\n\n";
		}

		// Pulo para a esquerda
		if ((Setidle == false) && (Setjump == true) && (Run == -1)) {
			////////////////////////
			//	SPRITE DE PULO PARA A ESQUERDA
			////////////////////////

			//cout << "\nTROCA, PULO ESQUERDA\n\n";
		}

		if (inputManager.IsKeyDown(NUMPAD_ONE_KEY)) {
			if(Player::player)
				Shoot(Player::player->GetCenter());
		}
	}

}

void Robot::Render() {

}

bool Robot::Is(std::string type) {
	if (type == "Robot")
		return true;
	else
		return false;
}


void Robot::NotifyCollision(GameObject& other) {
	auto bullet = (Bullet*)other.GetComponent("Bullet");
	auto tile = (TileMap*)other.GetComponent("TileMap");

	// Prosfere dano ao jogador se o tiro for dos Aliens
	if (bullet /*&& bullet->targetsPlayer*/ && bullet->alienBullet) {
		std::cout << "Vida do Robo: " << hp << std::endl;
		hp -= bullet->GetDamage();
	}

	//tile.DistRecs(associated.box.y);

	// todo - pensar em como fazer essa colisao com o chao
	if (tile) {
		if (tile->colide) {
			// Colisoes laterais
			if ((this->associated.box.x <= tile->GetX() + tile->GetWidth() * 80) &&
				(tile->GetY() <= this->associated.box.y /*+ this->associated.box.h*2/4 /*<= tile->GetY() * tile->GetHeight() * 80*/)) {
				// Paredes a ESQUERDA da personagem
				if (tile->GetX() <= this->associated.box.x) {
					//cout << " << Parede a esquerda\n\n";
					this->associated.box.x = tile->GetX() + tile->GetWidth() * 80;
					linearSpeed = 0;
					oppositeSpeed = 0;
				}
				// Paredes a DIREITA da personagem
				else if (this->associated.box.x + this->associated.box.w >= tile->GetX()) {
					//cout << " << Parede a direita\n\n";
					this->associated.box.x = tile->GetX() - this->associated.box.w;
					linearSpeed = 0;
					oppositeSpeed = 0;
				}
			}
			// Colisao com o chao
			else if ((tile->GetY() <= this->associated.box.y + this->associated.box.h) &&
				(this->associated.box.x <= tile->GetX() + tile->GetWidth() * 80) &&
				(tile->GetX() <= this->associated.box.x + this->associated.box.w)) {
				if (!airbone && tchfloor) {
					this->associated.box.y = tile->GetY() - this->associated.box.h;		// trava sem poder fazer o pulo
					verticalSpeed = 0;
				}
				tchfloor = true;
				airbone = false;
				//cout << "Chao abaixo\n\n";
			}
			// Momento que sai da colisao com o chao para impedir pulo aereo
			else
			{
				airbone = true;
				tchfloor = false;
			}
		}
	}
}


Vec2 Robot::GetCenter() {
	return associated.box.Center();
}

void Robot::Shoot(Vec2 target) {
	// Carrega um Tiro do Robo
	auto bulletGO = new GameObject();
	bulletGO->box = associated.box.Center();

	auto bullet = new Bullet(*bulletGO, target.InclinacaoDaDiferenca(associated.box.Center()), BULLET_SPEED,
		std::rand() % 11 + BULLET_MAX_DAMAGE - 10, BULLET_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	bullet->robotBullet = true;
	bulletGO->AddComponent(bullet);

	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}