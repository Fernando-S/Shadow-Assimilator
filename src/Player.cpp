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
		if (facingR) {
			explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/prot_morte.png", 21, 0.1, 2.1));
			associated.box.x += 40;
		}
		else if (facingL) {
			explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/prot_morte_inv.png", 21, 0.1, 2.1));
			associated.box.x -= 40;
		}
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);

	}
	else {
		double accelSpeedGain = PLAYER_ACCELERATION * dt;
		WallJumpTimer.Update(dt);
		ShootCooldownTimer.Update(dt);

		//////////////////////////////////////////
		//		TERMINO DO WALL JUMP
		//////////////////////////////////////////
		if (WallJump && (WallJumpTimer.Get() > 0.3)) {
			WallJump = false;
			linearSpeed = 0;
			verticalSpeed = 0;
		}

		/////////////////////////////////////////
		//		GRAVIDADE
		////////////////////////////////////////
		cout << "airbone: " << airbone << "\n";
		cout << "verticalSpeed: " << verticalSpeed << "\n";

		if (verticalSpeed > -800 && airbone) {
			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
			Stop = 0;
			if ((Jump != 0) && (verticalSpeed < 0))
				if (Fall < 10) {
					Fall++;
				}
			//tchfloor = false;
			//airbone = true;
		}

		//////////////////
		//		SPAWN DE TESTE
		/////////////////
		if (inputManager.KeyRelease(SPACE_KEY)) {
			associated.box.x = 704;
			associated.box.y = 100;
			airbone = true;
			tchfloor = false;
			verticalSpeed = -800;
		}


		//////////////////////////////////////////////////////////////
		//		DOUBLE JUMP
		///////////////////////////////////////////////////////////////
		//cout << "DJ: " << DJ << "\n";
		if (airbone && !inputManager.IsKeyDown(W_KEY) && (Jump == 2) && (DJ == 0))
			doubleJump = true; // setar para 0 quando encostar no chão

		if (doubleJump && airbone && inputManager.IsKeyDown(W_KEY)) {
			Jump = 0;
			Fall = 0;
			Ground = 0;
			Jump++;
			verticalSpeed = PLAYER_JUMP * 0.7;
			doubleJump = false;
			DJ++;
		}
		//////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////
		////WALL SLIDE/////
		/////////////////////////////////////////////////////////////

		//cout << "wallAUX: " << wallAUX << endl;
		// Wall Slide A DIREITA
		if (airbone && !tchfloor && WallgrabR) {
			if (wallAUX < 0) {
				wallAUX = 0;
			}
			if (wallAUX < 10) {
				wallAUX++;
			}
			//cout << "wallAUX: " << wallAUX << endl;
			if (inputManager.IsKeyDown(D_KEY) && (wallAUX > 0)) {
				verticalSpeed = -30;		// QUEDA
				Jump = 0;
				DJ = 0;
			}
			Fall = 0;
			Ground = 0;
		}
		// Wall Slide A ESQUERDA
		else if (airbone && !tchfloor && WallgrabL) {
			if (wallAUX > 0) {
				wallAUX = 0;
			}
			if (wallAUX > -10) {
				wallAUX--;
			}
			if (inputManager.IsKeyDown(A_KEY) && (wallAUX < 0)) {
				Jump = 0;
				verticalSpeed = -30;		// QUEDA
				linearSpeed -= accelSpeedGain;
				DJ = 0;
			}
			Fall = 0;
			Ground = 0;
		}


		//////////////////////////////////////////////////////////////
		//		WALL JUMP
		///////////////////////////////////////////////////////////////
		//NA PAREDE DA DIREITA
		if (WallgrabR && inputManager.IsKeyDown(D_KEY) && inputManager.IsKeyDown(W_KEY) && (wallAUX > 0)) {
			verticalSpeed += 500;
			speedH = { 1, 0 };
			oppositeSpeed += 250;
			wallAUX = 0;
			Jump++;
		}

		//NA PAREDE DA ESQUERDA
		if (WallgrabL && inputManager.IsKeyDown(A_KEY) && inputManager.IsKeyDown(W_KEY) && (wallAUX < 0)) {
			verticalSpeed += 500;
			speedH = { -1, 0 };
			oppositeSpeed += 250;
			associated.box += speedH * linearSpeed*dt;
			wallAUX = 0;
			Jump++;
		}
		///////////////////////////////////////////////////////////////

		/////////////////
		//		JUMP
		///////////////
		if (airbone)
			SetJump = false;

		if (inputManager.IsKeyDown(W_KEY) && tchfloor && !airbone && (Jump == 0)) {
			//this->associated.box.y -= 10;
			verticalSpeed = PLAYER_JUMP;
			tchfloor = false;
			SetJump = true;
			airbone = true;
			Jump++;
			Ground = 0;
		}
		else
			if (inputManager.IsKeyDown(A_KEY) && !WallJump) {

				WallgrabR = false;

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
				if ((oppositeSpeed > -PLAYER_SPEED) && !WallgrabL) {

					oppositeSpeed -= accelSpeedGain;
					linearSpeed = -oppositeSpeed;

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

		if (!inputManager.IsKeyDown(A_KEY) && !inputManager.IsKeyDown(D_KEY)) {

			if (linearSpeed > 40)
				linearSpeed -= accelSpeedGain * 1.5;

			if (linearSpeed < -40)
				linearSpeed += accelSpeedGain * 1.5;

			if ((linearSpeed <= 40) && (linearSpeed >= -40))
				linearSpeed = 0;
			Setidle = true;

			//cout << "Stop: " << Stop << endl;
		}

		if ((linearSpeed == 0) && (verticalSpeed == 0)) {
			if (Stop < 10) {
				Stop++;
			}
		}

		//////////////////////////////////////////////////////////////
		/////////////////////VELOCIDADE///////////////////////////////

		associated.box += speedH * linearSpeed*dt;
		associated.box += speedV * verticalSpeed*dt;

		//cout << "Centro: " << GetCenter().y << endl;
		//cout << "Centro: " << chao << endl;
		

		//////////////////////////////////////////////////////////////


		//SFX//
		//auto PlayerSFX_Run = new Sound(associated, "./assets/audio/Caminhada_1.wav");



		///////////////////////////////////////
		//			SPRITES
		//////////////////////////////////////
		/*
		cout << "\nStop: " << Stop << endl;
		cout << "Run: " << Run << endl;
		cout << "Jump: " << Jump << endl;
		cout << "Fall: " << Fall << endl;
		cout << "wallAUX: " << wallAUX << endl;
		cout << "Ground: " << Ground << endl;
		*/
		//cout << "verticalSpeed: " << verticalSpeed << endl << endl;


		// Idle para a direita
		if ((Stop == 1) && (Run >= 0) && (wallAUX == 0) && (Ground > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_idle(63x128).png", 12, 0.1);
			associated.box.x += associated.box.w / 2;
			facingR = true;
			facingL = false;

			//SFX//
			//PlayerSFX_Run->Stop();

			/// todo - isso arruma a posicao quando colide com algo a direita, mas andar a direita fica estranho
			// arruma a posicao para o sprite do personagem idle aparecer do pe mais a frente apos a corrida
			//associated.box.x += associated.box.w;//121;

			associated.AddComponent(sprite);
			
			cout << "\nIDLE DIREITA\n\n";
		}

		// Idle para a esquerda
		if ((Stop == 1) && (Run < 0) && (wallAUX == 0) && (Ground > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_idle_invertida.png", 12, 0.1);
			facingR = false;
			facingL = true;

			//SFX//
			//PlayerSFX_Run->Stop();

			associated.AddComponent(sprite);

			cout << "\nIDLE ESQUERDA\n\n";

		}

		// Corrida para a direita

		if (((Run == 1) && (wallAUX == 0) && (Jump == 0)) || (Ground == 1) && (Run > 1)) {
			//if ((Run == 1) && (wallAUX == 0) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_corrida(142x128).png", 12, 0.1);
			associated.AddComponent(sprite);
			facingR = true;
			facingL = false;
			//SFX//
			//PlayerSFX_Run->Play();
		
			
			cout << "\nCORRIDA DIREITA\n\n";

			Run++;
		}

		// Corrida para a esquerda
		if (((Run == -1) && (wallAUX == 0) && (Jump == 0)) || (Ground == 1) && (Run < -1)) {
			//if ((Run == -1) && (wallAUX == 0) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/sprite_prot_corrida_invertida.png", 12, 0.1);
			associated.AddComponent(sprite);
			facingR = false;
			facingL = true;
			//SFX//
			//PlayerSFX_Run->Play();

			cout << "\nCORRIDA ESQUERDA\n\n";
			Run--;
		}

		// Pulo para a direita
		//cout << "verticalspeed: " << verticalSpeed << endl;

		if (((((Run >= 0) && (Jump == 1)) || (Jump > 1) && (Run == 1)) && (Fall == 0)) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/prot_pulo.png", 8, 0.1);
			associated.AddComponent(sprite);

			cout << "\nPULO DIREITA\n\n";

			Jump++;
			//cout << "\nTROCA, PULO DIREITA\n\n";
		}

		// Pulo para a esquerda
		if (((((Run < 0) && (Jump == 1)) || (Jump > 1) && (Run == -1)) && (Fall == 0)) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/prot_pulo_inv.png", 8, 0.1);
			associated.AddComponent(sprite);

			cout << "\nPULO ESQUERDA\n\n";

			Jump++;
			//cout << "\nTROCA, PULO ESQUERDA\n\n";
		}
		
		// WallSlide A DIREITA
		if ((wallAUX == 1) && (Ground == 0) && (Run > 0)) {

			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/prot_desliza_inv.png", 8, 0.1);
			associated.AddComponent(sprite);

			associated.box.x += 50;

			cout << "\nWALLSLIDE DIREITA\n\n";

			//cout << "\nTROCA, WallSlide A DIREITA\n\n";
		}

		// WallSlide A ESQUERDA
		if ((wallAUX == -1) && (Ground == 0) && (Run < 0)) {

			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/prot_desliza.png", 8, 0.1);
			associated.AddComponent(sprite);

			cout << "\nWALLSLIDE ESQUERDA\n\n";
		}

		// QUEDA PRA DIREITA
		if (Fall > 0) {
			if ((((Fall == 1) && (Run >= 0) && (Jump > 0)) || (Jump > 0) && (Run == 1) && (Fall > 0)) && (wallAUX == 0)) {

				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/prot_queda.png", 6, 0.1);
				associated.AddComponent(sprite);

				cout << "\nQUEDA DIREITA\n\n";
			}

			// QUEDA PRA ESQUERDA
			if ((((Fall == 1) && (Run < 0) && (Jump > 0)) || (Jump > 0) && (Run == -1) && (Fall > 0)) && (wallAUX == 0)) {

				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/prot_queda_inv.png", 6, 0.1);
				associated.AddComponent(sprite);

				cout << "\nQUEDA ESQUERDA\n\n";
			}
		}

		///////////////////////////////
		//		TIRO DA PROTAGONISTA
		///////////////////////////////
		if (inputManager.IsKeyDown(J_KEY) && ShootCooldownTimer.Get() > 1.8) {
			if (facingR)
				Shoot(GetCenter());
			else if (facingL)
				Shoot(Vec2(-1*GetCenter().x, GetCenter().y));
			ShootCooldownTimer.Restart();
		}
	}

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

	// Prosfere dano ao jogador se o tiro for inimigo
	if (bullet && bullet->robotBullet) {
		//std::cout << "Vida do Jogador: " << hp << std::endl;
		hp -= bullet->GetDamage();
		damaged = true;
	}


	if (tile) {
		if (tile->colide) {
			//Wallgrab = true;

			// Colisao com chaos
			if ( /*(tile->GetY() <= this->associated.box.y + this->associated.box.h)
				&&*/ (this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149*//* + 90*/ /* + 120*/)				
					  || this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY()) ) <= this->associated.box.h/2
				) {
				if (!airbone && tchfloor && !SetJump) {
					verticalSpeed = 0;
					this->associated.box.y = tile->GetY() - this->associated.box.h;
					if (facingR) {
						/*associated.RemoveComponent(sprite);
						sprite = new Sprite(associated, "./assets/img/sprite_prot_idle(63x128).png", 12, 0.1);
						associated.AddComponent(sprite);*/
					}
					else if (facingL) {/*
						associated.RemoveComponent(sprite);
						sprite = new Sprite(associated, "./assets/img/sprite_prot_idle_invertida.png", 12, 0.1);
						associated.AddComponent(sprite);
						*/
					}
				}
				WallgrabL = false;
				WallgrabR = false;
				tchfloor = true;
				airbone = false;
				doubleJump = false;
				tchCeiling = false;
				if (Ground < 10) {
					Ground++;
				}
				DJ = 0;
				wallAUX = 0;
				Jump = 0;
				Fall = 0;

				// Checa se esta saindo de uma plataforma
				if ((this->associated.box.x + this->associated.box.w < tile->GetX()) || (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x)) {
					airbone = true;
					tchfloor = false;
					doubleJump = true;
					Stop = 0;
					wallAUX = 0;
					//tchCeiling = false;
					cout << "Desencostou\n";
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE) //&& (tile->GetY() /*+ 149/* +120/ < this->associated.box.y /*+ this->associated.box.h/) //&& tchCeiling
				&& this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE
				//&& !WallgrabR && !WallgrabL//&& tile->floor
				//|| this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY() + tile->GetHeight() * ONETILESQUARE)) <= this->associated.box.h / 2
				) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE +1;
				/// todo - comentar o vertical speed = 0 e mostrar pro nego o q acontece
				verticalSpeed = 0;
				tchCeiling = true;
			
			}
			// Colisao com uma parede A DIREITA
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w) && !tchCeiling //&& !tile->floor
					&& ((this->associated.box.x + this->associated.box.w <= tile->GetX() + tile->GetWidth()*ONETILESQUARE/* /4*/)
					|| this->GetCenter().Distancia(Vec2(tile->GetX(), this->GetCenter().y)) < 32)) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				WallgrabL = false;
				tchCeiling = false;
				WallgrabR = true;

				if (airbone && !tchfloor && WallgrabR) {
					wallX = tile->GetX();
					WallgrabR = true;
				}
			}
			// Coliscao com uma parede A ESQUERDA
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				&& (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)	/// todo - talvez mudar essa condicao
				&& !tchCeiling //&& !tile->floor
				) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * ONETILESQUARE;
				linearSpeed = 0;
				oppositeSpeed = 0;

				WallgrabR = false;
				tchCeiling = false;
				WallgrabL = true;
				
			}
			else {
				WallgrabL = false;
				WallgrabR = false;
				tchfloor = false;
				tchCeiling = false;
				airbone = true;
				cout << "desencostou do tile\n";
				wallAUX = 0;

				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					cout << "desencostou dessa parede <<\n";
					wallAUX = 0;
				//	if (airbone) {
						//doubleJump = true;
				//		WallgrabL = false;
				//	}
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					cout << "desencostou dessa parede >>\n";
					wallAUX = 0;
				//	if (airbone) {
						//doubleJump = true;
				//		WallgrabR = false;
				//	}
				}
				
				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					cout << "desencostou do teto ^\n";
					//for (int i = 0; i < 50; i++);
					tchCeiling = false;
				}
			}
		}
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
							 PLAYER_BULLET_DAMAGE, BULLET_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	bullet->playerBullet = true;
	bulletGO->AddComponent(bullet);

	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}

int Player::GetHP() {
	return hp;
}

