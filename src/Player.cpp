#include "Player.h"
#include "Game.h"
#include "Sound.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define PLAYER_SPEED 400
#define PLAYER_JUMP 600

using namespace std;

Player* Player::player = nullptr;

Player::Player(GameObject& associated) : Component(associated)/*, pcannon() */ {
	player = this;
	speedH = { 1, 0 };
	speedV = { 0, -1 };
	speedD = { 1, -1 };
	linearSpeed = 0;
	angle = 0;
	oppositeAccel = 0;
	oppositeSpeed = 0;
	hp = PLAYER_INITIAL_HP;

	// Carrega o sprite da personagem idle
	//sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
	sprite = new Sprite(associated, "./assets/img/sprite_prot_idle(63x128).png", 12, 0.1);

	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
//	associated.angleDeg = angle * 180 / PI;
}

Player::~Player() {
	player = nullptr;
}

void Player::Start() {
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

void Player::Update(float dt) {
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
		//explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/penguindeath.png", 5, 0.1, 1.5));
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/prot_morte.png", 21, 0.1, 2.1));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);

	}
	else {
		double accelSpeedGain = PLAYER_ACCELERATION * dt;

		// aplica gravidade funcional a todo momento
		if (verticalSpeed > -800 /*&& !tchfloor*/ && airbone) {
			verticalSpeed -= accelSpeedGain * 0.9;//QUEDA
			//tchfloor = false;
			//airbone = true;
		}

		if (inputManager.KeyRelease(SPACE_KEY)) {
			//associated.box.PlaceCenter(Vec2(704, 100));
			associated.box.x = 704;
			associated.box.y = 100;
			airbone = true;
			tchfloor = false;
			verticalSpeed = 0;
		}

		/*
		// Checa se esta no ar
		if (airbone && !tchfloor) {
			tchCeiling = false;
			cout << "ta no ar\n";
		}
		*/

		//////////////////////////////////////////////////////////////
		//		DOUBLE JUMP
		///////////////////////////////////////////////////////////////

		if (airbone && !inputManager.IsKeyDown(W_KEY) && (Jump == 1) )
			doubleJump = true; // setar para 0 quando encostar no chão

		if (doubleJump && airbone && inputManager.IsKeyDown(W_KEY)) {
			Jump++;
			verticalSpeed = PLAYER_JUMP * 0.7;
			doubleJump = false;
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////
		//		WALL JUMP
		///////////////////////////////////////////////////////////////
		//if ((WallgrabL) && (airbone) && (inputManager.IsKeyDown(W_KEY))) {
			//speedD = { 1, -1 };
			//diagonalSpeed = PLAYER_JUMP;
			//associated.box += speedD * diagonalSpeed*dt;
		//}
		///////////////////////////////////////////////////////////////

		if (inputManager.IsKeyDown(W_KEY) && tchfloor && !airbone && (Jump == 0)) {

			verticalSpeed = PLAYER_JUMP;
			//associated.box += speedV * verticalSpeed*dt;

			//associated.box.y -= 10;
			tchfloor = false;
			//Setjump = true;
			airbone = true;
			Jump++;
		}
		else
			if (inputManager.IsKeyDown(A_KEY)) {

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
					//std::cout << "\n\nPassarvalor2" << endl << endl;
					Getspeed2 = true;

					Run = 0;
					Stop = 0;
					Setidle = false;
					Setrun = true;

				}

				if (Run < 10)
					Run++;

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

		double atrictSpeedLoss = PLAYER_ATRICT * dt;

		if (!inputManager.IsKeyDown(A_KEY))
			Getspeed1 = false;

		if (!inputManager.IsKeyDown(D_KEY)) 
			Getspeed2 = false;

		if (!inputManager.IsKeyDown(A_KEY) && !inputManager.IsKeyDown(D_KEY)/* && !inputManager.IsKeyDown(W_KEY) && !inputManager.IsKeyDown(S_KEY)*/) {

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

		}
		//////////////////////////////////////////////////////////////
		/////////////////////VELOCIDADE///////////////////////////////

		
		associated.box += speedH * linearSpeed*dt;
		
		associated.box += speedV * verticalSpeed*dt;

		//cout << "Centro: " << GetCenter().y << endl;
		//cout << "Centro: " << chao << endl;
		

		//////////////////////////////////////////////////////////////

		//if ((Stop == 2) || (Run == 1) || (Run == -1) || (Jump == 1)) {
		//	cout << "\n\nSetidle: " << Setidle << "\nSetrun: " << Setrun << "\nStop: " << Stop << "\nlinearspeed: " << linearSpeed << "\n\n";
		//}

		//SFX//
		//auto PlayerSFX_Run = new Sound(associated, "./assets/audio/Caminhada_1.wav");

		// Idle para a direita
		if ( Setidle && !Setrun && (Stop == 2) && (Run > 0)) {
			associated.RemoveComponent(sprite);
			//sprite = new Sprite(associated, "./assets/img/sprite_idle.png", 12, 0.1);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_idle(63x128).png", 12, 0.1);
			associated.box.x += associated.box.w/2;

			//SFX//
			//PlayerSFX_Run->Stop();

			/// todo - isso arruma a posicao quando colide com algo a direita, mas andar a direita fica estranho
			// arruma a posicao para o sprite do personagem idle aparecer do pe mais a frente apos a corrida
			//associated.box.x += associated.box.w;//121;

			associated.AddComponent(sprite);

			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Idle para a esquerda
		if (Setidle && !Setrun && (Stop == 2) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			//srite = new Sprite(associated, "./assets/img/sprite_idle_espelhado.png", 12, 0.1);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_idle_invertida.png", 12, 0.1);
			associated.box.x += 1;

			//SFX//
			//PlayerSFX_Run->Stop();

			associated.AddComponent(sprite);
			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Corrida para a direita
		if (!Setidle && Setrun && (Run == 1)) {
			associated.RemoveComponent(sprite);
			//sprite = new Sprite(associated, "./assets/img/sprite_corrida2.png", 12, 0.1);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_corrida(142x128).png", 12, 0.1);
			associated.AddComponent(sprite);
			//SFX//
			//PlayerSFX_Run->Play();

			//cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}

		// Corrida para a esquerda
		if (!Setidle && Setrun && (Run == -1)) {
			associated.RemoveComponent(sprite);
			//sprite = new Sprite(associated, "./assets/img/sprite_corrida2_espelhado.png", 12, 0.1);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_corrida_invertida.png", 12, 0.1);
			
			//SFX//
			//PlayerSFX_Run->Play();
			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE ESQUERDA\n\n";
		}

		// Pulo para a direita
		if (!Setidle && (Jump == 1)) {
			////////////////////////
			//	SPRITE DE PULO PARA A DIREITA
			////////////////////////


			//cout << "\nTROCA, PULO DIREITA\n\n";
		}

		// Pulo para a esquerda
		if (!Setidle && (Jump == 1) && (Run < 0)) {
			////////////////////////
			//	SPRITE DE PULO PARA A ESQUERDA
			////////////////////////

			//cout << "\nTROCA, PULO ESQUERDA\n\n";
		}
		if (inputManager.IsKeyDown(Q_KEY)) {
			if (Player::player)
				Shoot(Player::player->GetCenter());
		}

		/*
		BeforeCollision();

		auto tile = (TileMap*)other.GetComponent("TileMap");

		if (!tchfloor && (this->associated.box.y + this->associated.box.h <= tile->GetY() - 1)) {
			verticalSpeed = 0;
		}
		*/
	}
	//cout << "aribone = " << airbone << endl;
	//cout << "tchfloor = " << tchfloor << endl;

}

void Player::Render() {

}

bool Player::Is(std::string type) {
	if (type == "Player")
		return true;
	else
		return false;
}


void Player::NotifyCollision(GameObject& other) {
	auto bullet = (Bullet*)other.GetComponent("Bullet");
	auto tile = (TileMap*)other.GetComponent("TileMap");

	// Prosfere dano ao jogador se o tiro for dos Aliens
	//if ((bullet && bullet->targetsPlayer) && bullet->alienBullet) {
	if (bullet && bullet->robotBullet) {
		//std::cout << "Vida do Jogador: " << hp << std::endl;
		hp -= bullet->GetDamage();
		damaged = true;
	}


	if (tile) {
		if (tile->colide) {
			//Wallgrab = true;

			/// todo - dá ruim ao pular de lugares altos se for soh 80
			/// mas tbm dá ruim se for muito maior na hora de encostar pelo lado da plataforma
			// Colisao com chaos
			if ( /*(tile->GetY() <= this->associated.box.y + this->associated.box.h)
				&&*/ (this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149*//* + 90*/ + 120) ) {
			//if (tile->GetBox().ContainsY(this->associated.box.y + this->associated.box.h) //||
				//tile->GetBox().ContainsY(this->associated.box.h)
				//){
				if (!airbone && tchfloor) {
					verticalSpeed = 0;
					this->associated.box.y = tile->GetY() - this->associated.box.h;
				}
				tchfloor = true;
				airbone = false;
				Jump = 0;
				doubleJump = false;
				tchCeiling = false;

				// Checa se esta saindo de uma plataforma
				if ((this->associated.box.x + this->associated.box.w < tile->GetX()) || (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x)) {
					airbone = true;
					tchfloor = false;
					//tchCeiling = false;
					cout << "Desencostou\n";
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE) //&& (tile->GetY() /*+ 149/* +120*/ < this->associated.box.y /*+ this->associated.box.h*/) //&& tchCeiling
					  && this->associated.box.y + this->associated.box.h/4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE) {
					this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE;
					/// todo - comentar o vertical speed = 0 e mostrar pro nego o q acontece
					verticalSpeed = 0;
					tchCeiling = true;
			}
			// Colisao com uma parede A DIREITA
			else if ( (tile->GetX() <= this->associated.box.x + this->associated.box.w)
					  && (this->associated.box.x + this->associated.box.w <= tile->GetX() + ONETILESQUARE/*/4*/
					  && !tchCeiling) ) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				WallgrabL = false;
				WallgrabR = true;
				tchCeiling = false;
				
				// Wall Slide A DIREITA
				if(airbone && !tchfloor)
					verticalSpeed /= 2;//QUEDA
			}
			// Coliscao com uma parede A ESQUERDA
			else if ( (associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				      && (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)
					  && !tchCeiling) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * ONETILESQUARE;
				linearSpeed = 0;
				oppositeSpeed = 0;
				WallgrabL = true;
				WallgrabR = false;
				tchCeiling = false;

				// Wall Slide A ESQUERDA
				if (airbone && !tchfloor)
					verticalSpeed /= 2;//QUEDA
			}

			/// todo - checar se isso ainda funciona
			else {
				WallgrabL = false;
				WallgrabR = false;
				tchfloor = false;
				tchCeiling = false;
				airbone = true;
				cout << "desencostou do tile\n";
				/*
				// Checa se saiu de algum chao/plataforma e bateu em um teto
				if (airbone && !tchfloor) {
					tchCeiling = true;
					cout << "Bateu no teto\n";
				}
				*/
				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					cout << "desencostou dessa parede <<\n";
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					cout << "desencostou dessa parede >>\n";
				}
				
				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					cout << "desencostou do teto ^\n";
					for (int i = 0; i < 500; i++);
					tchCeiling = false;
				}
			}
		}
		/*
		else {
			Wallgrab = false;
		}
		*/
	}
}


Vec2 Player::GetCenter() {
	return associated.box.Center();
}


void Player::Shoot(Vec2 target) {
	// Carrega um Tiro do Robo
	auto bulletGO = new GameObject();
	bulletGO->box = associated.box.Center();

	auto bullet = new Bullet(*bulletGO, target.InclinacaoDaDiferenca(associated.box.Center()), BULLET_SPEED,
		std::rand() % 11 + BULLET_MAX_DAMAGE - 10, BULLET_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	bullet->playerBullet = true;
	bulletGO->AddComponent(bullet);

	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}


int Player::GetHP() {
	return hp;
}

/*
void Player::BeforeCollision() {

}
*/