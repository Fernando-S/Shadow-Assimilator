
#include "Player.h"
#include "Game.h"
#include "Sound.h"

#define MAX_SPEED 400
#define SPEED_STEP 50
#define PLAYER_SPEED 400
#define PLAYER_JUMP 600

using namespace std;

Player* Player::player = nullptr;


Player::Player(GameObject& associated) : Component(associated) {
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
	sprite = new Sprite(associated, "./assets/img/Protagonista/sprite_prot_idle(63x128).png", 12, 0.1);

	// Carrega som nulo para a personagem
	playerSFX = new Sound(associated);

	associated.AddComponent(playerSFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	//	associated.angleDeg = angle * 180 / PI;
}

Player::~Player() {
	player = nullptr;
}

void Player::Start() {
}


void Player::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;
	double accelSpeedGain = PLAYER_ACCELERATION * dt;

	if (inputManager.KeyPress(ZERO_KEY)) {
		hp = 0;
		damaged = true;
	}


	if (hp <= 0) {

		/////////////////////////////////////////
		//		GRAVIDADE
		////////////////////////////////////////
		if (airbone) {
			Ground = 0;
		}

		contadorW1 = verticalSpeed;

		if (verticalSpeed < -800) {
			verticalSpeed = -800;
		}

		if ((BuzzL >= 2) && (verticalSpeed > -800)) {

			//cout << "\n\n\n\n\nVOCE EH UM BRINQUEDO\n\n\n\n\n";

			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
			Stop = 0;
			if (verticalSpeed < 0) {
				if (Fall < 10) {
					Fall++;
				}
			}
			tchfloor = false;
			airbone = true;
		}

		if (verticalSpeed > -800 && airbone) {

			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
			Stop = 0;
			if (verticalSpeed < 0) {
				if (Fall < 10) {
					Fall++;
				}
			}
			tchfloor = false;
			airbone = true;
		}

		contadorW2 = verticalSpeed;

		if ((contadorW2 == contadorW1) && (verticalSpeed != 0) || (verticalSpeed >= 600)) {
			BuzzL++;
		}

		if (((BuzzL >= 1) && (contadorW2 != contadorW1)) || verticalSpeed == -800) {
			BuzzL = 0;
		}


		associated.box += speedV * verticalSpeed*dt;


		DeathTimer.Update(dt);

		if (!dead) {
			DeathTimer.Restart();
			Camera::Unfollow();				// Camera para de segui-los
			verticalSpeed = 0;

			if (facingR) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_morte.png", 21, 0.1, 2.1);
				associated.AddComponent(sprite);
			}
			else if (facingL) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_morte_inv.png", 21, 0.1, 2.1);
				associated.AddComponent(sprite);
				associated.box.x -= 80;
			}
			dead = true;
		}
		else {
			///////////////////////////////
			//		SFX DE MORTE		//
			/////////////////////////////
			if ((DeathTimer.Get() > 1.0) && !deathSound) {
				
				if (playerSFX->IsPlaying()) {
					playerSFX->Stop();
				}
				associated.RemoveComponent(playerSFX);
				playerSFX = new Sound(associated, "./assets/audio/SFX/MortePrincipal(Assim.).wav");
				associated.AddComponent(playerSFX);
				playerSFX->Play();
				deathSound = true;
			}


			
			if (DeathTimer.Get() > 2.1) {
				/// todo - descobrir o porque disso para melhorar som de morte
				cout << "Nem entra aqui. A personagem esta sendo deleta antes em outro lugar\n";
				// Deleta a Personagem se o hp dela acabou
				associated.RequestDelete();
			}
		}
	}
	else {
		double accelSpeedGain = PLAYER_ACCELERATION * dt;
		WallJumpTimer.Update(dt);
		ShootCooldownTimer.Update(dt);
		DashCooldownTimer.Update(dt);
		DJTimer.Update(dt);


		//////////////////////////////////////////
		//		TERMINO DO WALL JUMP
		//////////////////////////////////////////
		//if (WallJump && (WallJumpTimer.Get() > 0.3)) {
		//	WallJump = false;
			//linearSpeed = 0;
			//verticalSpeed = 0;
		//}
		/*
		else if (WallJump && (WallJumpTimer.Get() < 0.3)) {
			doubleJump = false;
		}*/

		/////////////////////////////////////////
		//		GRAVIDADE
		////////////////////////////////////////
		if (airbone) {
			Ground = 0;
		}


		contadorW1 = verticalSpeed;

		if (verticalSpeed < -800) {
			verticalSpeed = -800;
		}

		if ((BuzzL >= 2) && (verticalSpeed > -800)) {

			////cout << "\n\n\n\n\nVOCE E UM BRINQUEDO\n\n\n\n\n";

			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
			Stop = 0;
			if (verticalSpeed < 0) {
				if (Fall < 10) {
					Fall++;
				}
			}
			tchfloor = false;
			airbone = true;
		}

		if (verticalSpeed > -800 && airbone) {

			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
			Stop = 0;
			if (verticalSpeed < 0) {
				if (Fall < 10) {
					Fall++;
				}
			}
			tchfloor = false;
			airbone = true;
		}

		contadorW2 = verticalSpeed;

		if ((contadorW2 == contadorW1) && (verticalSpeed != 0) || (verticalSpeed >= 600)) {
			BuzzL++;
		}
		if (((BuzzL >= 1) && (contadorW2 != contadorW1)) || verticalSpeed == -800) {
			BuzzL = 0;
		}


		//////////////////////////////
		//		SPAWN DE TESTE		//
		/////////////////////////////
		if (inputManager.KeyRelease(SPACE_KEY)) {
			associated.box.x = 604;
			associated.box.y = 100;
			airbone = true;
			tchfloor = false;
			verticalSpeed = -800;
		}


		///////////////////////////
		//		DOUBLE JUMP		//
		/////////////////////////
		if (airbone && !inputManager.IsKeyDown(W_KEY) && (Ground == 0) && (DJ == 1) && (wallAUX == 0)) {
			doubleJump = true; // setar para 0 quando encostar no chão
		}

		if (doubleJump && airbone && inputManager.IsKeyDown(W_KEY) && (wallAUX == 0) && DJTimer.Get() > 0.3) {
			Fall = 0;
			Ground = 0;
			verticalSpeed = PLAYER_JUMP * 0.7;
			doubleJump = false;
			foguete = true;
			DJ++;
		}
		

		///////////////////////////
		//		WALL SLIDE		//
		/////////////////////////

		// Wall Slide A DIREITA
		if (airbone && !tchfloor && WallgrabR) {
			if (wallAUX < 0) {
				wallAUX = 0;
			}
			if (wallAUX < 10) {
				wallAUX++;
			}

			if (inputManager.IsKeyDown(D_KEY) && (linearSpeed != 0)) {
				WallgrabR = false;		// QUEDA
				wallAUX = 0;
			}

			if (inputManager.IsKeyDown(D_KEY) && (wallAUX > 0)) {
				verticalSpeed = -30;		// QUEDA

			}
			Fall = 0;
			Ground = 0;
			Jump = 0;
		}
		// Wall Slide A ESQUERDA
		else if (airbone && !tchfloor && WallgrabL) {
			if (wallAUX > 0) {
				wallAUX = 0;
			}
			if (wallAUX > -10) {
				wallAUX--;
			}

			if (inputManager.IsKeyDown(A_KEY) && ((linearSpeed != 0) || (linearSpeed != (-0)))) {
				WallgrabL = false;		// QUEDA
				wallAUX = 0;
			}

			if (inputManager.IsKeyDown(A_KEY) && (wallAUX < 0)) {
				verticalSpeed = -30;		// QUEDA
				linearSpeed -= accelSpeedGain;
			}

			Fall = 0;
			Ground = 0;
			Jump = 0;
		}

		///////////////////////////
		//		WALL JUMP		//
		/////////////////////////
		//NA PAREDE DA DIREITA
		if (WallgrabR && inputManager.IsKeyDown(D_KEY) && inputManager.IsKeyDown(W_KEY) && (wallAUX > 0) && (WallJumpTimer.Get() > 0.18)) {
			DJTimer.Restart();
			verticalSpeed += 500;
			speedH = { 1, 0 };
			oppositeSpeed += 250;
			wallAUX = 0;
			Jump++;
		}

		//NA PAREDE DA ESQUERDA
		if (WallgrabL && inputManager.IsKeyDown(A_KEY) && inputManager.IsKeyDown(W_KEY) && (wallAUX < 0) && (WallJumpTimer.Get() > 0.18)) {
			DJTimer.Restart();
			verticalSpeed += 500;
			speedH = { -1, 0 };
			oppositeSpeed += 250;
			associated.box += speedH * linearSpeed*dt;
			wallAUX = 0;
			Jump++;
		}

		if (Jump == 2) {
			WallJumpTimer.Restart();
		}


		///////////////////////
		//		JUMP		//
		/////////////////////
		if (airbone) {
			Ground = 0;
			SetJump = false;

		}

		if (inputManager.IsKeyDown(W_KEY) && tchfloor && !airbone && (Jump == 0)) {
			//this->associated.box.y -= 10;
			verticalSpeed = PLAYER_JUMP;
			tchfloor = false;
			SetJump = true;
			airbone = true;
			Jump++;
			Ground = 0;
			DJTimer.Restart();
		}
		else
			///////////////////////////////////////////
			//		CORRIDA PARA A ESQUERDA			//
			/////////////////////////////////////////
			if (inputManager.IsKeyDown(A_KEY)) {

				WallgrabR = false;

				if (linearSpeed == 0)
					oppositeSpeed = 0;

				if (Getspeed1 == false) {
					oppositeSpeed = linearSpeed;
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
			}
		///////////////////////////////////////
		//		CORRIDA PARA A DIREITA		//
		/////////////////////////////////////
			else if (inputManager.IsKeyDown(D_KEY)) {
				speedH = { 1, 0 };

				if (Getspeed2 == false) {
					oppositeSpeed = linearSpeed;
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
			Setrun = false;
			Setidle = true;

			if (runningSound) {
				if (playerSFX->IsPlaying()) {
					playerSFX->Stop();
				}
			}

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


		///////////////////////////////////////////////////////////////////////////////
		//									SPRITES									//
		/////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////
		//		Idle para a direita		//
		/////////////////////////////////
		if ((Stop == 1) && (Run >= 0) && (wallAUX == 0) && (Ground > 0)/* && !pouso*/) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/sprite_prot_idle(63x128).png", 12, 0.1);

			facingR = true;
			facingL = false;

			if (Ground <= 2) {
				//associated.box.x += 35;
			}
			else {
				associated.box.x += associated.box.w / 2;
			}

			/// todo - isso arruma a posicao quando colide com algo a direita, mas andar a direita fica estranho
			// arruma a posicao para o sprite do personagem idle aparecer do pe mais a frente apos a corrida
			//associated.box.x += associated.box.w;//121;

			associated.AddComponent(sprite);
		}


		///////////////////////////////////////
		//		Idle para a esquerda		//
		/////////////////////////////////////
		if ((Stop == 1) && (Run < 0) && (wallAUX == 0) && (Ground > 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/sprite_prot_idle_invertida.png", 12, 0.1);
			facingR = false;
			facingL = true;


			associated.AddComponent(sprite);

			if (Ground <= 2) {
				//	associated.box.x += 35;
			}
			else {
				associated.box.x += associated.box.w / 2;
			}

		}


		///////////////////////////////////////
		//		Corrida para a direita		//
		/////////////////////////////////////
		if ((((Run == 1) && (Ground > 0)) || ((Ground == 1) && (Run > 0) && (inputManager.IsKeyDown(D_KEY)))) && (Fall <= 1) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/sprite_prot_corrida(142x128).png", 12, 0.08);
			associated.AddComponent(sprite);
			facingR = true;
			facingL = false;
			Run++;
		}


		///////////////////////////////////////
		//		Corrida para a esquerda		//
		/////////////////////////////////////
		if ((((Run == -1) && (Ground > 0)) || ((Ground == 1) && (Run < 0) && (inputManager.IsKeyDown(A_KEY)))) && (Fall <= 1) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/sprite_prot_corrida_invertida.png", 12, 0.08);
			associated.AddComponent(sprite);
			facingR = false;
			facingL = true;
			Run--;
		}


		///////////////////////////////////
		//		Pulo para a direita		//
		/////////////////////////////////
		if ((((Run >= 0) && (Jump == 1)) || ((Jump > 1) && (Run == 1))) && (Fall == 0) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_pulo.png", 8, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 10;
			facingR = true;
			facingL = false;

			if (Jump == 1) {
				if ((DJ == 0) && (wallAUX == 0)) {
					DJ++;
				}
				Jump++;
			}

		}


		///////////////////////////////////////
		//		Pulo para a esquerda		//
		/////////////////////////////////////
		if ((((Run < 0) && (Jump == 1)) || ((Jump > 1) && (Run == -1))) && (Fall == 0) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_pulo_inv.png", 8, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 10;
			facingR = false;
			facingL = true;
		}
		if (Jump == 1) {
			if ((DJ == 0) && (wallAUX == 0)) {
				DJ++;
			}
			Jump++;
		}


		///////////////////////////////////////////
		//		Pulo Duplo para a direita		//
		/////////////////////////////////////////
		if ((((Run >= 0) && (DJ == 2)) || ((Jump > 1) && (DJ >= 2) && (Run == 1))) && (Fall == 0) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_puloduplo.png", 4, 0.1);
			associated.AddComponent(sprite);
			facingR = true;
			facingL = false;
			DJ++;
		}


		///////////////////////////////////////////
		//		Pulo Duplo para a esquerda		//
		/////////////////////////////////////////
		if ((((Run < 0) && (DJ == 2)) || ((Jump > 1) && (DJ >= 2) && (Run == -1))) && (Fall == 0) && (wallAUX == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_puloduplo_inv.png", 4, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 10;
			facingR = false;
			facingL = true;
			DJ++;
		}


		///////////////////////////////////
		//		WallSlide A DIREITA		//
		/////////////////////////////////
		if ((wallAUX == 1) && (Ground == 0) && (Run > 0)) {

			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_desliza_inv.png", 8, 0.1);
			associated.AddComponent(sprite);
			associated.box.x += 70;
			facingR = false;
			facingL = true;
		}


		///////////////////////////////////////
		//		WallSlide A ESQUERDA		//
		/////////////////////////////////////
		if ((wallAUX == -1) && (Ground == 0) && (Run < 0)) {

			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Protagonista/prot_desliza.png", 8, 0.1);
			associated.AddComponent(sprite);
			facingR = true;
			facingL = false;
		}


		///////////////////////
		//		QUEDAS 		//
		/////////////////////
		if (Ground == 0) {

			// PRA DIREITA
			if ((((Fall == 1) && (Run >= 0)) || ((Fall > 0) && (Run == 1))) && (wallAUX == 0)) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_queda.png", 6, 0.1);
				associated.AddComponent(sprite);
				associated.box.x += 20;
				facingR = true;
				facingL = false;
			}

			// QUEDA PRA ESQUERDA
			if ((((Fall == 1) && (Run < 0)) || ((Fall > 0) && (Run == -1))) && (wallAUX == 0)) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_queda_inv.png", 6, 0.1);
				associated.AddComponent(sprite);
				associated.box.x += 20;
				facingR = false;
				facingL = true;
			}
		}


		/// TODO - NEGRAO, FAZ ISSO FUNCIONAR DO TEU JEITO MAGICO PFVR 
		///////////////////////
		//		POUSO		//
		/////////////////////
		if (pouso) {

			cout << "ENTRA NO POUSO\n";

			// PARA A DIREITA
			//if ((((Fall == 1) && (Run >= 0)) || ((Fall > 0) && (Run == 1))) && (wallAUX == 0)) {
			if (facingR) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_pouso.png", 3, 0.1);
				associated.AddComponent(sprite);
				//associated.box.x -= 1;
				facingR = true;
				facingL = false;
			}

			// PARA A ESQUERDA
			//if ((((Fall == 1) && (Run < 0)) || ((Fall > 0) && (Run == -1))) && (wallAUX == 0)) {
			if (facingL) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Protagonista/prot_pouso_inv.png", 3, 0.1);
				associated.AddComponent(sprite);
				associated.box.x -= 5;
				facingR = false;
				facingL = true;
			}
		}


		///////////////////////////////////////
		//		TIRO DA PROTAGONISTA		//
		/////////////////////////////////////
		if (inputManager.IsKeyDown(J_KEY) && ShootCooldownTimer.Get() > 1.8) {
			if (facingR)
				Shoot(GetCenter());
			else if (facingL)
				Shoot(Vec2(-1 * GetCenter().x, GetCenter().y));
			ShootCooldownTimer.Restart();
		}

		///////////////////////
		//		DASH		//
		/////////////////////
		// DIREITA
		if (inputManager.IsKeyDown(E_KEY) && DashCooldownTimer.Get() > 1.8) {
			speedH = { 1, 0 };
			linearSpeed += 1000;
			associated.box += speedH * linearSpeed*dt;
			DashCooldownTimer.Restart();
		}
		
		// ESQUERDA
		if (inputManager.IsKeyDown(Q_KEY) && DashCooldownTimer.Get() > 1.8) {
			speedH = { -1, 0 };
			linearSpeed += 1000;
			associated.box += speedH * linearSpeed*dt;
			DashCooldownTimer.Restart();
		}

		///////////////////////////////////
		//        ATAQUE BASICO			//
		/////////////////////////////////
		if (inputManager.KeyPress(K_KEY)) {
			isAtacking = true;
		}
		else
			isAtacking = false;

		///////////////////////////////////////////////////////////////////////////////
		//							EFEITOS SONOROS									//
		/////////////////////////////////////////////////////////////////////////////

		///////////////////////////
		//		SFX DE PULO		//
		/////////////////////////
		if (SetJump) {
			if (playerSFX->IsPlaying()) {
				playerSFX->Stop();
			}
			associated.RemoveComponent(playerSFX);
			playerSFX = new Sound(associated, "./assets/audio/SFX/PuloPrincipal(Assim.)1.wav");
			associated.AddComponent(playerSFX);
			playerSFX->Play();
			runningSound = false;
		}
		///////////////////////////////
		//		SFX DE CORRIDA		//
		/////////////////////////////
		else if (Setrun && tchfloor) {
			if (!runningSound) {
				if (playerSFX->IsPlaying()) {
					playerSFX->Stop();
				}
				associated.RemoveComponent(playerSFX);
				playerSFX = new Sound(associated, "./assets/audio/SFX/CorridaNormal(Assim.)1.wav");
				associated.AddComponent(playerSFX);
				runningSound = true;
			}
			else {
				if (!playerSFX->IsPlaying()) {
					playerSFX->Play();
				}
			}
		}
		///////////////////////////////
		//		SFX DE WALLSLIDE	//
		/////////////////////////////
		else if (airbone && !tchfloor && (WallgrabL || WallgrabR)) {
			if (!wallSlideSound) {
				if (playerSFX->IsPlaying()) {
					playerSFX->Stop();
				}
				associated.RemoveComponent(playerSFX);
				playerSFX = new Sound(associated, "./assets/audio/SFX/ArrastarPrincipal(Assim.)2.wav");
				associated.AddComponent(playerSFX);
				wallSlideSound = true;
			}
			else {
				if (!playerSFX->IsPlaying()) {
					playerSFX->Play();
				}
			}
		}
		///////////////////////////////
		//		SFX DE POUSO		//
		/////////////////////////////
		else if (/*ultrapassou*/ pouso && tchfloor && !airbone) {
			if (playerSFX->IsPlaying()) {
				playerSFX->Stop();
			}
			associated.RemoveComponent(playerSFX);
			//playerSFX = new Sound(associated, "./assets/audio/SFX/PousoPrincipal(Assim.)1.wav");
			playerSFX = new Sound(associated, "./assets/audio/SFX/Pouso2.1(Assim.).wav");
			associated.AddComponent(playerSFX);
			playerSFX->Play();
			pouso = false;
		}
		///////////////////////////////////
		//		SFX DE PULO DUPLO		//
		/////////////////////////////////
		else if (foguete) {
			if (playerSFX->IsPlaying()) {
				playerSFX->Stop();
			}
			associated.RemoveComponent(playerSFX);
			playerSFX = new Sound(associated, "./assets/audio/SFX/Foguete2.1(Assim.).wav");
			associated.AddComponent(playerSFX);
			playerSFX->Play();
			foguete = false;
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
	auto laser = (Laser*)other.GetComponent("Laser");
	auto tile = (TileMap*)other.GetComponent("TileMap");
	auto go = (GameObject*)other.GetComponent("GameObject");

	// Prosfere dano ao jogador se o tiro for inimigo
	if (laser && laser->robotLaser) {
		hp -= laser->GetDamage();
		damaged = true;
	}


	if (tile) {
		if (tile->colide) {

			// Colisao com chaos
			if ( (this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149*//* + 90*/ /* + 120*/)
				|| (this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY())) <= this->associated.box.h / 2)	) {
				
				if (this->associated.box.y + this->associated.box.h > tile->GetY()) {
					ultrapassou = true;
				}
				if (!airbone && tchfloor && !SetJump) {
					verticalSpeed = 0;
					this->associated.box.y = tile->GetY() - this->associated.box.h;
					ultrapassou = false;
					if (Ground <= 2)
						pouso = true;
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
					ultrapassou = false;
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE)
				&& this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE + 1;
				/// todo - comentar o vertical speed = 0 e mostrar pro nego o q acontece
				verticalSpeed = 0;
				tchCeiling = true;
				ultrapassou = false;

			}
			// Colisao com uma parede A DIREITA
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w) && !tchCeiling
				&& ((this->associated.box.x + this->associated.box.w <= tile->GetX() + tile->GetWidth()*ONETILESQUARE)
					|| this->GetCenter().Distancia(Vec2(tile->GetX(), this->GetCenter().y)) < 32)) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				WallgrabL = false;
				tchCeiling = false;
				WallgrabR = true;
				ultrapassou = false;

				if (airbone && !tchfloor && WallgrabR) {
					wallX = tile->GetX();
					WallgrabR = true;
				}
			}
			// Coliscao com uma parede A ESQUERDA
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				&& (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)	/// todo - talvez mudar essa condicao
				&& !tchCeiling
				) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * ONETILESQUARE;
				linearSpeed = 0;
				oppositeSpeed = 0;

				WallgrabR = false;
				tchCeiling = false;
				WallgrabL = true;
				ultrapassou = false;

			}
			else {
				WallgrabL = false;
				WallgrabR = false;
				tchfloor = false;
				tchCeiling = false;
				airbone = true;
				wallAUX = 0;
				ultrapassou = false;

				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					wallAUX = 0;
					WallgrabL = false;
					if (playerSFX->IsPlaying()) {
						playerSFX->Stop();
					}
					wallSlideSound = false;
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					WallgrabR = false;
					if (airbone) {
						associated.box.x -= 15;
					}
					wallAUX = 0;
					ultrapassou = false;
					if (playerSFX->IsPlaying()) {
						playerSFX->Stop();
					}
					wallSlideSound = false;
				}

				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					tchCeiling = false;
					ultrapassou = false;
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
	auto laserGO = new GameObject();
	laserGO->box = associated.box.Center();

	auto laser = new Laser(*laserGO, target.InclinacaoDaDiferenca(associated.box.Center()), LASER_SPEED,
		PLAYER_LASER_DAMAGE, LASER_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	laser->playerLaser = true;
	auto laserSound = new Sound(*laserGO, "./assets/audio/SFX/LaserInimigo(Assim.)1.wav");
	laserGO->AddComponent(laserSound);
	/// todo - Parar playerSFX nao fez a menor diferenca
	if (playerSFX->IsPlaying()) {
		playerSFX->Stop();
	}
	laserSound->Play();
	laserGO->AddComponent(laser);

	Game::GetInstance().GetCurrentState().AddObject(laserGO);
}

int Player::GetHP() {
	return hp;
}