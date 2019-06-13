#include "Robot.h"
#include "Game.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define ROBOT_SPEED 400
#define ROBOT_JUMP 600

using namespace std;

bool moveDireita = false;
bool moveEsquerda = false;

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
	initialX = associated.box.x;
	initialY = associated.box.y;
}

void Robot::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;

	if (hp <= 0) {
		// Deleta os Penguins se o hp deles acabou
		associated.RequestDelete();
		//pcannon.lock()->RequestDelete();
	//	Camera::Unfollow();				// Camera para de segui-los

		// Carrega a animacao e som de explosao da morte do Alien
		auto explosionGO = new GameObject();
		auto explosionSound = new Sound(*explosionGO, "./assets/audio/boom.wav");
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/aliendeath.png", 4, 0.15, 1.2));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);

	}
	else {
		double accelSpeedGain = ROBOT_ACCELERATION * dt;

		// aplica gravidade funcional a todo momento
		if (verticalSpeed > -900)
			verticalSpeed -= accelSpeedGain * 0.9; //QUEDA

		if (inputManager.KeyRelease(SPACE_KEY)) {
			associated.box.PlaceCenter(Vec2(694, 100));
			airbone = true;
			tchfloor = false;
		}

		// Tentativa de IA apenas quando esta no chao
		if (!airbone && tchfloor) {
			//mudaDeLado.Update(dt);

			if (!moveDireita && !moveEsquerda)
				moveEsquerda = true;

			//if (mudaDeLado.Get() < ROBOT_TIME) {
			if (associated.box.x < initialX - 250) {
				moveDireita = true;
				moveEsquerda = false;
			}
			//else if (mudaDeLado.Get() < 2 * ROBOT_TIME) {
			else if (associated.box.x > initialX + 250) {
				moveDireita = false;
				moveEsquerda = true;
			}
			//else if (mudaDeLado.Get() >= 2 * ROBOT_TIME)
			//	mudaDeLado.Restart();
		}

		/*
		if (inputManager.IsKeyDown(I_KEY) && tchfloor && !airbone) {

			verticalSpeed = ROBOT_JUMP;

			tchfloor = false;
			airbone = true;
			doubleJump = false;
		}
		else*/
			if (inputManager.IsKeyDown(J_KEY) || moveEsquerda) {

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

				if (Run > -10)
					Run--;

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
			else if (inputManager.IsKeyDown(L_KEY) || moveDireita) {
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

				if (Run < 10)
					Run++;

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
		/*
		double atrictSpeedLoss = ROBOT_ATRICT * dt;

		if (!inputManager.IsKeyDown(J_KEY))
			Getspeed1 = false;

		if (!inputManager.IsKeyDown(L_KEY))
			Getspeed2 = false;

		if (!inputManager.IsKeyDown(J_KEY) && !inputManager.IsKeyDown(L_KEY) /*&& !inputManager.IsKeyDown(I_KEY)/* && !inputManager.IsKeyDown(K_KEY)/) {

			if (linearSpeed > 40)
				linearSpeed -= accelSpeedGain * 1.5;

			if (linearSpeed < -40)
				linearSpeed += accelSpeedGain * 1.5;

			if ((linearSpeed < 40) && (linearSpeed > -40))
				linearSpeed = 0;

			if (Stop < 10) {
				Stop++;
				if (Stop == 1)
					Setrun = false;
			}
			Setidle = true;

			//cout << "Stop: " << Stop << endl;

		}*/
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
		if (Setidle && !Setrun && (Stop == 2) && (Run > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
			
			/// todo - isso arruma a posicao quando colide com algo a direita, mas andar a direita fica estranho
			// arruma a posicao para o sprite do personagem idle aparecer do pe mais a frente apos a corrida
			//associated.box.x += associated.box.w;//121;

			associated.AddComponent(sprite);

			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Idle para a esquerda
		if (Setidle && !Setrun && (Stop == 2) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);

			associated.AddComponent(sprite);
			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Corrida para a direita
		if (!Setidle && Setrun && (Run == 1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);

			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}

		// Corrida para a esquerda
		if (!Setidle && Setrun && (Run == -1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);

			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE ESQUERDA\n\n";
		}

		// Pulo para a direita
		if (!Setidle && Setjump) {
			////////////////////////
			//	SPRITE DE PULO PARA A DIREITA
			////////////////////////


			//cout << "\nTROCA, PULO DIREITA\n\n";
		}

		// Pulo para a esquerda
		if (!Setidle && Setjump && (Run == -1)) {
			////////////////////////
			//	SPRITE DE PULO PARA A ESQUERDA
			////////////////////////

			//cout << "\nTROCA, PULO ESQUERDA\n\n";
		}

		if (inputManager.IsKeyDown(NUMPAD_ONE_KEY)) {
		//	if(Player::player && (Player::player->GetCenter() ))
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
	if (bullet && bullet->playerBullet) {
		std::cout << "Vida do Robo: " << hp << std::endl;
		hp -= bullet->GetDamage();
	}
	

	if (tile) {
		if (tile->colide) {

			// Colisao com o chao
			if ((tile->GetY() <= this->associated.box.y + this->associated.box.h)
				&& (this->associated.box.y + this->associated.box.h <= tile->GetY() + 149)) {
				if (!airbone && tchfloor) {
					this->associated.box.y = tile->GetY() - this->associated.box.h;
					verticalSpeed = 0;
				}
				tchfloor = true;
				airbone = false;
				Jump = 0;
				doubleJump = false;

				// Checa se esta saindo de uma plataforma
				if ((this->associated.box.x + this->associated.box.w < tile->GetX()) || (tile->GetX() + tile->GetWidth() * 80 < this->associated.box.x)) {
					airbone = true;
					tchfloor = false;
				}
			}
			// Colisao com uma parede A DIREITA
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w)
				&& (this->associated.box.x + this->associated.box.w <= tile->GetX() + 90)) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
			}
			// Coliscao com uma parede A ESQUERDA
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * 80)
				&& (tile->GetX() + tile->GetWidth() * 80 - 80 <= associated.box.x)) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * 80;
				linearSpeed = 0;
				oppositeSpeed = 0;
			}
			
			/// todo - checar se isso ainda funciona
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