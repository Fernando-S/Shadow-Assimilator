#include "CoatGuy.h"
#include "Game.h"
#include "Sound.h"


using namespace std;

CoatGuy* CoatGuy::coatGuy = nullptr;


CoatGuy::CoatGuy(GameObject& associated) : Component(associated) {
	coatGuy = this;
	speedH = { 1, 0 };
	speedV = { 0, -1 };
	linearSpeed = 0;
	oppositeSpeed = 0;
	FinishHimEneable = 0;
	hp = COATGUY_INITIAL_HP;

	// Carrega o sprite do coatGuy idle
	sprite = new Sprite(associated, "./assets/img/Vilao/vilao_idle.png", 10, 0.09);

	// Carrega som nulo para o coatGuy
	coatGuySFX = new Sound(associated);

	associated.AddComponent(coatGuySFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

CoatGuy::~CoatGuy() {
	coatGuy = nullptr;
}

void CoatGuy::Start() {
	initialX = associated.box.x;
	initialY = associated.box.y;
}


void CoatGuy::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double accelSpeedGain = COATGUY_ACCELERATION * dt;

	if (inputManager.KeyPress(NUMPAD_EIGHT_KEY) || inputManager.KeyPress(EIGHT_KEY)) {
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
			falsehp = 1;
			FinishHimTimer.Update(dt);
			DeathTimer.Restart();
			/// todo - comentar esse verticalSpeed com o Nego e ver o que ele acha melhor
			verticalSpeed = 0;

			if (facingR && !FinishHimEneable && !StartLoop && !kill) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_morte1.png", 18, 0.1);
				associated.AddComponent(sprite);
				FinishHimEneable = true;
				StartLoop = false;
				FinishHimTimer.Restart();
			}
			else if (facingL && !FinishHimEneable && !StartLoop && !kill) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_morte1_inv.png", 18, 0.1);
				associated.AddComponent(sprite);
				associated.box.x -= 80;
				FinishHimEneable = true;
				StartLoop = false;
				FinishHimTimer.Restart();
			}
			//dead = true;

			if ((FinishHimTimer.Get() > 1.8) && (FinishHimEneable == true) && (StartLoop == false) && (kill == false)) {// eh feito o primeiro ciclo do loop
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_morte2.png", 10, 0.1);
				associated.AddComponent(sprite);
				StartLoop = true;
			}

			if ((FinishHimEneable == true) && (StartLoop == true)) { //
				FinishHimTimer.Restart();
				FinishHimEneable = false;
			}

			if ((FinishHimTimer.Get() > 1) && (kill == false) && (StartLoop == true)) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_morte2.png", 10, 0.1);
				associated.AddComponent(sprite);
				FinishHimTimer.Restart();
			}

			if (kill == true) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_morte3.png", 1, 0.1);
				associated.AddComponent(sprite);
			}
			

		}
		else {
			///////////////////////////////
			//		SFX DE MORTE		//
			/////////////////////////////

			if (!deathSound && coatGuySFX->IsPlaying()) {
				coatGuySFX->Stop();
			}

			if ((DeathTimer.Get() > 1.0) && !deathSound) {
				associated.RemoveComponent(coatGuySFX);
				coatGuySFX = new Sound(associated, "./assets/audio/SFX/MortePrincipal(Assim.).wav");
				associated.AddComponent(coatGuySFX);
				coatGuySFX->Play();
				deathSound = true;
			}



			if (DeathTimer.Get() > 2.1) {
				/// todo - descobrir o porque disso para melhorar som de morte
				cout << "Nem entra aqui. O CoatGuy esta sendo deletado antes em outro lugar\n";
				// Deleta a Personagem se o hp dela acabou
				associated.RequestDelete();
			}
		}
	}
	else {
		double accelSpeedGain = COATGUY_ACCELERATION * dt;
		FinishHimTimer.Update(dt);
		ATKTimer.Update(dt);

		if (Player::player->GetCenter().Distancia(this->GetCenter()) < 10 * ONETILESQUARE) {
			if (Player::player->GetCenter().x > this->GetCenter().x) {

				moveEsquerda = false;
				moveDireita = true;
			}
			else {
				moveDireita = false;
				moveEsquerda = true;
			}


		}


		if (associated.box.x < initialX - 35 * ONETILESQUARE) {

				moveDireita = true;
				moveEsquerda = false;

		}
		else if (associated.box.x > initialX +  2 * ONETILESQUARE) {
			moveDireita = false;
			moveEsquerda = true;
		}


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


		///////////////////////
		//		JUMP		//
		/////////////////////
		if (airbone) {
			Ground = 0;
			SetJump = false;
		}
		if (ATKTimer.Get() > 1 + dt) {
			if (inputManager.IsKeyDown(UP_ARROW_KEY) && tchfloor && !airbone && (Jump == 0)) {
				verticalSpeed = COATGUY_JUMP;
				tchfloor = false;
				SetJump = true;
				airbone = true;
				Jump++;
				Ground = 0;
			}
			else
				///////////////////////////////////////////
				//		CORRIDA PARA A ESQUERDA			//
				/////////////////////////////////////////
				if (inputManager.IsKeyDown(LEFT_ARROW_KEY) || moveEsquerda) {

					WallgrabR = false;

					if (linearSpeed == 0)
						oppositeSpeed = 0;

					if (Getspeed1 == false) {
						oppositeSpeed = linearSpeed;
						Getspeed1 = true;
						Setrun = true;
						Run = 0;
						Stop = 0;
						facingL = true;
						facingR = false;
					}

					if (Run > -10)
						Run--;

					speedH = { -1, 0 };
					if ((oppositeSpeed > -COATGUY_SPEED) && !WallgrabL) {

						oppositeSpeed -= accelSpeedGain;
						linearSpeed = -oppositeSpeed;

					}
					else
						linearSpeed = -oppositeSpeed;
				}
				///////////////////////////////////////
				//		CORRIDA PARA A DIREITA		//
				/////////////////////////////////////
				else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY) || moveDireita) {
					speedH = { 1, 0 };

					if (Getspeed2 == false) {
						oppositeSpeed = linearSpeed;
						Getspeed2 = true;

						Run = 0;
						Stop = 0;
						Setrun = true;
						facingL = false;
						facingR = true;

					}

					if (Run < 10)
						Run++;

					if (linearSpeed < COATGUY_SPEED + 50) {

						if (oppositeSpeed >= 0) {
							oppositeSpeed -= accelSpeedGain;
							linearSpeed = -oppositeSpeed;
						}
						else
							linearSpeed += accelSpeedGain;

					}
				}
		}
		double atrictSpeedLoss = COATGUY_ATRICT * dt;

		if (!inputManager.IsKeyDown(LEFT_ARROW_KEY) && !moveEsquerda)
			Getspeed1 = false;

		if (!inputManager.IsKeyDown(RIGHT_ARROW_KEY) && !moveDireita)
			Getspeed2 = false;

		if (!inputManager.IsKeyDown(LEFT_ARROW_KEY) && !inputManager.IsKeyDown(RIGHT_ARROW_KEY) && !moveEsquerda && !moveDireita) {

			if (linearSpeed > 40)
				linearSpeed -= accelSpeedGain * 1.5;

			if (linearSpeed < -40)
				linearSpeed += accelSpeedGain * 1.5;

			if ((linearSpeed <= 40) && (linearSpeed >= -40))
				linearSpeed = 0;
			Setrun = false;

			if (runningSound) {
				if (coatGuySFX->IsPlaying()) {
					coatGuySFX->Stop();
				}
				runningSound = false;
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


		///////////////////////////////////////
		//		Idle para a direita			//
		/////////////////////////////////////
		if (((Stop == 1) && (Run >= 0) && (Ground > 0)) || ((Run >= 0) && (Atk0 == true))) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_idle.png", 10, 0.09);

			facingR = true;
			facingL = false;

			if ((Ground > 2) && (Atk0 == false)) {
				associated.box.x += associated.box.w / 2;
			}

			if (Atk0 == true) {
				Atk0 = false;
			}


			associated.AddComponent(sprite);
		}


		///////////////////////////////////////
		//		Idle para a esquerda		//
		/////////////////////////////////////
		if (((Stop == 1) && (Run < 0) && (Ground > 0)) || ((Run < 0) && (Atk0 == true))) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_idle_inv.png", 10, 0.09);
			facingR = false;
			facingL = true;


			associated.AddComponent(sprite);

			if ((Ground > 2) && (Atk0 == false)) {
				associated.box.x += associated.box.w / 2;
			}

			if (Atk0 == true) {
				Atk0 = false;
			}

		}


		///////////////////////////////////////
		//		Corrida para a direita		//
		/////////////////////////////////////
		if ((((Run == 1) && (Ground > 0)) || ((Ground == 1) && (Run > 0) && (inputManager.IsKeyDown(RIGHT_ARROW_KEY) || moveDireita))) && (Fall <= 1) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_corrida.png", 10, 0.09);
			associated.AddComponent(sprite);
			facingR = true;
			facingL = false;
			Run++;

		}


		///////////////////////////////////////
		//		Corrida para a esquerda		//
		/////////////////////////////////////
		if ( ( ( (Run == -1) && (Ground > 0)) || ((Ground == 1) && (Run < 0) && inputManager.IsKeyDown(LEFT_ARROW_KEY || moveEsquerda))) && (Fall <= 1) && (Jump == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_corrida_inv.png", 10, 0.09);
			associated.AddComponent(sprite);
			facingR = false;
			facingL = true;
			Run--;

		}


		///////////////////////////////////
		//		Pulo para a direita		//
		/////////////////////////////////
		if ((((Run >= 0) && (Jump == 1)) || ((Jump > 1) && (Run == 1))) && (Fall == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_pulo.png", 4, 0.15);
			associated.AddComponent(sprite);
			associated.box.x -= 10;
			facingR = true;
			facingL = false;

			if (Jump == 1) {
				Jump++;
			}

		}


		///////////////////////////////////////
		//		Pulo para a esquerda		//
		/////////////////////////////////////
		if ((((Run < 0) && (Jump == 1)) || ((Jump > 1) && (Run == -1))) && (Fall == 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_pulo_inv.png", 4, 0.15);
			associated.AddComponent(sprite);
			associated.box.x -= 10;
			facingR = false;
			facingL = true;

		}
		if (Jump == 1) {
			Jump++;
		}

		///////////////////////
		//		QUEDA		//
		/////////////////////
		if (Ground == 0) {

			// QUEDA PRA DIREITA
			if ((((Fall == 1) && (Run >= 0)) || ((Fall > 0) && (Run == 1)))) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_queda.png", 4, 0.15);
				associated.AddComponent(sprite);
				associated.box.x += 20;
				facingR = true;
				facingL = false;

			}

			// QUEDA PRA ESQUERDA
			if ((((Fall == 1) && (Run < 0)) || ((Fall > 0) && (Run == -1)))) {
				associated.RemoveComponent(sprite);
				sprite = new Sprite(associated, "./assets/img/Vilao/vilao_queda_inv.png", 4, 0.15);
				associated.AddComponent(sprite);
				associated.box.x += 20;
				facingR = false;
				facingL = true;

			}
		}


		///////////////////////////////////
		//        ATAQUE BASICO			//
		/////////////////////////////////
		if ((/*inputManager.KeyPress(K_KEY) ||*/ (Player::player->GetCenter().Distancia(this->GetCenter()) < 3 * ONETILESQUARE)) && (ATKTimer.Get() > 1.0)) {
			isAtacking = true;
			moveDireita = false;
			moveEsquerda = false;
			Atk1 = 0;
			Atk0 = false;
			Atk1++;
			ATKTimer.Restart();
		}
		if ((Atk1 == 1) && (Run >= 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_atk1.png", 5, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 20;
			Atk1++;
			Atk0 = false;
		}

		if ((Atk1 == 1) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_atk1_inv.png", 5, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 20;
			Atk1++;
			Atk0 = false;
		}

		if ((ATKTimer.Get() > 0.5) && (ATKTimer.Get() < 0.5 + dt) && (Atk1 == 2)) {
			Atk1++;
		}
		if ((Atk1 == 3) && (Run >= 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_atk2.png", 5, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 20;
			Atk1++;
		}

		if ((Atk1 == 3) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Vilao/vilao_atk2_inv.png", 5, 0.1);
			associated.AddComponent(sprite);
			associated.box.x -= 20;
			Atk1++;
		}

		if ((ATKTimer.Get() > 1.0) && (Atk1 == 4)) {
			Atk1 = 0;
			Atk0 = true;
		}
		else {
			isAtacking = false;
		}


		///////////////////////////////////////////////////////////////////////////////
		//							EFEITOS SONOROS									//
		/////////////////////////////////////////////////////////////////////////////

		///////////////////////////
		//		SFX DE PULO		//
		/////////////////////////
		if (SetJump) {
			if (coatGuySFX->IsPlaying()) {
				coatGuySFX->Stop();
			}
			associated.RemoveComponent(coatGuySFX);
			coatGuySFX = new Sound(associated, "./assets/audio/SFX/PuloPrincipal(Assim.)1.wav");
			associated.AddComponent(coatGuySFX);
			coatGuySFX->Play();
			runningSound = false;
		}
		///////////////////////////////
		//		SFX DE CORRIDA		//
		/////////////////////////////
		else if (Setrun && tchfloor) {
			if (!runningSound) {
				if (coatGuySFX->IsPlaying()) {
					coatGuySFX->Stop();
				}
				associated.RemoveComponent(coatGuySFX);
				coatGuySFX = new Sound(associated, "./assets/audio/SFX/CorridaNormal(Assim.)1.wav");
				associated.AddComponent(coatGuySFX);
				runningSound = true;
			}
			else {
				if (!coatGuySFX->IsPlaying()) {
					coatGuySFX->Play();
				}
			}
		}
		///////////////////////////////
		//		SFX DE WALLSLIDE	//
		/////////////////////////////
		else if (airbone && !tchfloor && (WallgrabL || WallgrabR)) {
			if (!wallSlideSound) {
				if (coatGuySFX->IsPlaying()) {
					coatGuySFX->Stop();
				}
				associated.RemoveComponent(coatGuySFX);
				coatGuySFX = new Sound(associated, "./assets/audio/SFX/ArrastarPrincipal(Assim.)2.wav");
				associated.AddComponent(coatGuySFX);
				wallSlideSound = true;
			}
			else {
				if (!coatGuySFX->IsPlaying()) {
					coatGuySFX->Play();
				}
			}
		}

		///////////////////////////////////
		//		SFX DE PULO DUPLO		//
		/////////////////////////////////
		else if (foguete) {
			if (coatGuySFX->IsPlaying()) {
				coatGuySFX->Stop();
			}
			associated.RemoveComponent(coatGuySFX);
			coatGuySFX = new Sound(associated, "./assets/audio/SFX/Foguete2.1(Assim.).wav");
			associated.AddComponent(coatGuySFX);
			coatGuySFX->Play();
			foguete = false;
		}
	}

}


void CoatGuy::Render() {

}

bool CoatGuy::Is(std::string type) {
	if (type == "CoatGuy")
		return true;
	else
		return false;
}

void CoatGuy::NotifyCollision(GameObject& other) {
	auto laser = (Laser*)other.GetComponent("Laser");
	auto tile = (TileMap*)other.GetComponent("TileMap");
	auto player1 = (Player*)other.GetComponent("Player");


	// Prosfere dano ao CoatGuy se o tiro for do jogador
	if (laser && laser->playerLaser) {
		hp -= laser->GetDamage();
		falsehp--;
		damaged = true;
		gotHit = true;
	}
	else if (player1 && Player::player->isAtacking) {
		hp -= 6;		// Prosfere dano ao robo se ele sofrer um ataque melee do jogador
		falsehp--;
		damaged = true;
		gotHit = true;

	}

	if (falsehp < 1 && !FinishHimEneable && StartLoop) {
		kill = true;
	}

	if (tile) {
		if (tile->colide) {

			// Colisao com chaos
			if ((this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149*//* + 90*/ /* + 120*/)
				|| (this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY())) <= this->associated.box.h / 2)) {

				if (!airbone && tchfloor && !SetJump) {
					verticalSpeed = 0;
					this->associated.box.y = tile->GetY() - this->associated.box.h;
				}
				WallgrabL = false;
				WallgrabR = false;
				tchfloor = true;
				airbone = false;
				tchCeiling = false;
				if (Ground < 10) {
					Ground++;
				}


				Jump = 0;
				Fall = 0;

				// Checa se esta saindo de uma plataforma
				if ((this->associated.box.x + this->associated.box.w < tile->GetX()) || (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x)) {
					airbone = true;
					tchfloor = false;
					Stop = 0;
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE)
				&& this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE + 1;
				verticalSpeed = 0;
				tchCeiling = true;

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

				if (airbone && !tchfloor && WallgrabR) {
					WallgrabR = true;
				}
			}
			// Coliscao com uma parede A ESQUERDA
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				&& (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)
				&& !tchCeiling) {
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

				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					WallgrabL = false;
					if (coatGuySFX->IsPlaying()) {
						coatGuySFX->Stop();
					}
					wallSlideSound = false;
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					WallgrabR = false;
					if (airbone) {
						associated.box.x -= 15;
					}
					if (coatGuySFX->IsPlaying()) {
						coatGuySFX->Stop();
					}
					wallSlideSound = false;
				}

				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					tchCeiling = false;
				}
			}
		}
	}
}

Vec2 CoatGuy::GetCenter() {
	return associated.box.Center();
}

void CoatGuy::Shoot(Vec2 target) {
	// Carrega um Tiro do Robo
	auto laserGO = new GameObject();
	laserGO->box = associated.box.Center();

	auto laser = new Laser(*laserGO, target.InclinacaoDaDiferenca(associated.box.Center()), LASER_SPEED,
		COATGUY_LASER_DAMAGE, LASER_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	laser->coatGuyLaser = true;
	auto laserSound = new Sound(*laserGO, "./assets/audio/SFX/LaserInimigo(Assim.)1.wav");
	laserGO->AddComponent(laserSound);
	/// todo - Parar coatGuySFX nao fez a menor diferenca
	if (coatGuySFX->IsPlaying()) {
		coatGuySFX->Stop();
	}
	laserSound->Play();
	laserGO->AddComponent(laser);

	Game::GetInstance().GetCurrentState().AddObject(laserGO);
}

int CoatGuy::GetHP() {
	return hp;
}