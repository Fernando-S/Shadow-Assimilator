#include "Robot.h"
#include "Game.h"

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
	sprite = new Sprite(associated, "./assets/img/vilao_idle.png", 10, 0.09);

	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));


	runningSound = new Sound(associated, "./assets/audio/SFX/CorridaNormal(Assim.)1.wav");
	//runningSound = new Music("./assets/audio/SFX/CorridaNormal(Assim.)1.wav");
	//runningSound = new Sound(associated, "./assets/audio/SFX/Passo_Unico.wav");
	//associated.AddComponent(runningSound);
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
	/*
	auto runningSound = new Sound(associated, "./assets/audio/SFX/CorridaNormal(Assim.)1.wav");
	if(!associated.GetComponent("runningSound"))
		associated.AddComponent(runningSound);
		*/

	if (hp <= 0) {
		// Deleta os Penguins se o hp deles acabou
		associated.RequestDelete();
		//pcannon.lock()->RequestDelete();
	//	Camera::Unfollow();				// Camera para de segui-los

		// Carrega a animacao e som de explosao da morte do Alien
		auto explosionGO = new GameObject();
		auto explosionSound = new Sound(*explosionGO, "./assets/audio/SFX/boom.wav");
		explosionGO->AddComponent(new Sprite(*explosionGO, "./assets/img/aliendeath.png", 4, 0.15, 1.2));
		explosionGO->AddComponent(explosionSound);
		explosionSound->Play();
		explosionGO->box.PlaceCenter(associated.box.Center());
		Game::GetInstance().GetCurrentState().AddObject(explosionGO);

	}
	else {
		double accelSpeedGain = ROBOT_ACCELERATION * dt;

		cooldownTimer.Update(dt);
		changeSideTimer.Update(dt);
		
		// aplica gravidade funcional a todo momento
		if (verticalSpeed > -800 && airbone) {
			verticalSpeed -= accelSpeedGain * 0.9;	//QUEDA
		}

		if (inputManager.KeyRelease(SPACE_KEY)) {
			associated.box.x = 704;
			associated.box.y = 100;
			airbone = true;
			tchfloor = false;
			verticalSpeed = -800;
		}
		
		///////////////////////////////////////////////////////////
		//		IA do Robo espera um tempo parado e muda de lado
		//////////////////////////////////////////////////////////
		if (idleR && changeSideTimer.Get() > 2) {
			moveEsquerda = true;
			idleR = false;
			moveDireita = false;
			//cout << "CORRE PARA A ESQUERDA\n";
		}
		else if (idleL && changeSideTimer.Get() > 2) {
			moveDireita = true;
			idleL = false;
			moveEsquerda = false;
			//cout << "CORRE PARA A DIREITA\n";
		}

		// Tentativa de IA apenas quando esta no chao
		if (!airbone && tchfloor) {

			// Comeca a andar
			if (!moveDireita && !moveEsquerda && !idleL && !idleR)
				moveEsquerda = true;

			if (associated.box.x < initialX - /*250*/ 10 * ONETILESQUARE) {
				if (!idleL && !moveDireita) {
					changeSideTimer.Restart();
					moveDireita = false;
					moveEsquerda = false;
					idleL = true;
				}
				//cout << "LIMITE A ESQUERDA\n";
			}
			else if (associated.box.x > initialX + /*250*/ 10 * ONETILESQUARE) {
				if (!idleR && !moveEsquerda) {
					changeSideTimer.Restart();
					moveDireita = false;
					moveEsquerda = false;
					idleR = true;
				}
				//cout << "LIMITE A DIREITA\n";
			}
		}

		/*
		if (inputManager.IsKeyDown(I_KEY) && tchfloor && !airbone) {

			verticalSpeed = ROBOT_JUMP;

			tchfloor = false;
			airbone = true;
			doubleJump = false;
		}
		else */
			if (/*inputManager.IsKeyDown(J_KEY) ||*/ moveEsquerda) {

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
			else if (/*inputManager.IsKeyDown(L_KEY) ||*/ moveDireita) {
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
		
		double atrictSpeedLoss = ROBOT_ATRICT * dt;
		
		if (/*!inputManager.IsKeyDown(J_KEY) ||*/ !moveEsquerda)
			Getspeed1 = false;

		if (/*!inputManager.IsKeyDown(L_KEY) ||*/ !moveDireita)
			Getspeed2 = false;
		

		if ((idleL && !moveDireita) || (idleR && !moveDireita)/*!inputManager.IsKeyDown(J_KEY) && !inputManager.IsKeyDown(L_KEY)*/) {

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
			sprite = new Sprite(associated, "./assets/img/vilao_idle.png", 10, 0.09);
			//if (Player::player->GetCenter().Distancia(this->GetCenter()) < 3 * ONETILESQUARE)
			if(runningSound->IsPlaying())
				runningSound->Stop();
			associated.AddComponent(sprite);

			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Idle para a esquerda
		if (Setidle && !Setrun && (Stop == 2) && (Run < 0)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/vilao_idle_inv.png", 10, 0.09);
			//if (Player::player->GetCenter().Distancia(this->GetCenter()) < 3 * ONETILESQUARE)
			if (runningSound->IsPlaying())
				runningSound->Stop();
			associated.AddComponent(sprite);
			//cout << "\nTROCA, CORRE > PARA\n\n";
		}

		// Corrida para a direita
		if (!Setidle && Setrun && (Run == 1)) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/vilao_corrida.png", 10, 0.09);
			//auto runningSound = new Sound(associated, "./assets/audio/SFX/CorridaNormal(Assim.)1");
			//associated.AddComponent(runningSound);
			if(!runningSound->IsPlaying())
			//if(Player::player->GetCenter().Distancia(this->GetCenter()) < 3 * ONETILESQUARE)
				runningSound->Play();
			associated.AddComponent(sprite);


			//cout << "\nTROCA, PARA > CORRE DIREITA\n\n";
		}

		// Corrida para a esquerda
		if (!Setidle && Setrun && (Run == -1)) {
			associated.RemoveComponent(sprite);
			//sprite = new Sprite(associated, "./assets/img/walk2_1.png", 6, 0.1);
			sprite = new Sprite(associated, "./assets/img/vilao_corrida_inv.png", 10, 0.09);
			if (!runningSound->IsPlaying())
			//if (Player::player->GetCenter().Distancia(this->GetCenter()) < 3 * ONETILESQUARE)
				runningSound->Play();
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

		//if (inputManager.IsKeyDown(NUMPAD_ONE_KEY)) {
		/// todo - fazer uma condicao parecida ou ate mesmo igual para tocar o som de corrida apenas quando esta proximo do jogador
		if (Player::player && (Player::player->GetCenter().Distancia(this->GetCenter()) < 800) && cooldownTimer.Get() > 1.8
			&& (Player::player->GetCenter().y > this->associated.box.y - ONETILESQUARE * 3)
			&& (Player::player->GetCenter().y < this->associated.box.y + this->associated.box.h + ONETILESQUARE * 3) ) {
			Shoot(Vec2(Player::player->GetCenter().x, this->GetCenter().y));
			cooldownTimer.Restart();
		}
		//}
		

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
	auto laser = (Laser*)other.GetComponent("Laser");
	auto tile = (TileMap*)other.GetComponent("TileMap");
	auto player1 = (Player*)other.GetComponent("Player");


	// Prosfere dano ao robo se o tiro for do jogador
	if (laser && laser->playerLaser) {
		//std::cout << "Vida do Robo: " << hp << std::endl;
		hp -= laser->GetDamage();
	}
	else if (player1 && Player::player->isAtacking) {
		//cout << "Deu dano no robo\n";
		hp -= 2;		// Prosfere dano ao robo se ele sofrer um ataque melee do jogador
	}

	if (tile) {
		if (tile->colide) {

			//////////////////////
			//		FORMA 1
			//////////////////////
			/*
			// Colisao com o chao
			if (this->associated.box.y + this->associated.box.h <= tile->GetY() + 120) {
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
				}
			}
			// Colisao com tetos
			/*
			else if ((associated.box.y < tile->GetY() + 80) && (tile->GetY() + 80 <= this->associated.box.y + this->associated.box.h)/* && tchCeiling/) {
				this->associated.box.y = tile->GetY() + 80;
				verticalSpeed = 0;
				tchCeiling = true;
			}
			*6
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE)
	   				  && this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE;
				/// todo - comentar o vertical speed = 0 e mostrar pro nego o q acontece
				verticalSpeed = 0;
				tchCeiling = true;
			}
			// Colisao com uma parede A DIREITA
			/*
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w)
				&& (this->associated.box.x + this->associated.box.w <= tile->GetX() + 90)) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				tchCeiling = false;
			}
			/
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w) && !tchCeiling
				&& (this->associated.box.x + this->associated.box.w <= tile->GetX() + ONETILESQUARE)) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				//WallgrabL = false;
				tchCeiling = false;
				/*
				// Wall Slide A DIREITA
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;		// QUEDA
					wallX = tile->GetX();
					WallgrabR = true;
				}
				/
			}
			// Coliscao com uma parede A ESQUERDA
			/*
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * 80)
				&& ((tile->GetX() + tile->GetWidth() * 80 - 80) <= associated.box.x)) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * 80;
				linearSpeed = 0;
				oppositeSpeed = 0;
				tchCeiling = false;
			}
			/
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				&& (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)
				&& !tchCeiling) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * ONETILESQUARE;
				linearSpeed = 0;
				oppositeSpeed = 0;

				//WallgrabR = false;
				tchCeiling = false;

				// Wall Slide A ESQUERDA
				/*
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;//QUEDA
					WallgrabL = true;
				}
				/
			}
			/// todo - checar se isso ainda funciona
			// Momento que sai da colisao com o chao para impedir pulo aereo
			else
			{
				
				airbone = true;
				tchfloor = false;
			}
			*/



			//////////////////////
			//		FORMA 2
			//////////////////////
			/*
			if ( (this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149//* + 90/ + 120)) {
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
					//cout << "Desencostou\n";
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE) 
				&& this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE;
				verticalSpeed = 0;
				tchCeiling = true;
			}
			// Colisao com uma parede A DIREITA
			else if ((tile->GetX() <= this->associated.box.x + this->associated.box.w) && !tchCeiling
					  && ((this->associated.box.x + this->associated.box.w <= tile->GetX() + tile->GetWidth()*ONETILESQUARE)
					  || this->GetCenter().Distancia(Vec2(tile->GetX(), this->GetCenter().y)) < 32)	) {
				this->associated.box.x = tile->GetX() - this->associated.box.w;
				linearSpeed = 0;
				oppositeSpeed = 0;
				//WallgrabL = false;
				tchCeiling = false;

				// Wall Slide A DIREITA
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;		// QUEDA
				//	wallX = tile->GetX();
				//	WallgrabR = true;
				}
			}
			// Coliscao com uma parede A ESQUERDA
			else if ((associated.box.x <= tile->GetX() + tile->GetWidth() * ONETILESQUARE)
				&& (tile->GetX() + tile->GetWidth() * ONETILESQUARE - ONETILESQUARE <= associated.box.x)
				&& !tchCeiling) {
				this->associated.box.x = tile->GetX() + tile->GetWidth() * ONETILESQUARE;
				linearSpeed = 0;
				oppositeSpeed = 0;

				//WallgrabR = false;
				tchCeiling = false;

				// Wall Slide A ESQUERDA
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;	// QUEDA
				//	WallgrabL = true;
				}
			}
			else {
				//WallgrabL = false;
				//WallgrabR = false;
				tchfloor = false;
				tchCeiling = false;
				airbone = true;
				//cout << "desencostou do tile\n";

				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					//cout << "desencostou dessa parede <<\n";
					if (airbone)
						doubleJump = true;
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					//cout << "desencostou dessa parede >>\n";
					if (airbone)
						doubleJump = true;
				}

				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					//cout << "desencostou do teto ^\n";
					//for (int i = 0; i < 50; i++);
					tchCeiling = false;
				}
			}
			*/



			//////////////////////
			//		FORMA 3
			//////////////////////
			if ( (this->associated.box.y + this->associated.box.h <= tile->GetY() /*+ 149*//* + 90*/ /* + 120*/)
				 || this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY())) <= this->associated.box.h / 2
				) {
				if (!airbone && tchfloor/* && !SetJump*/) {
					verticalSpeed = 0;
					this->associated.box.y = tile->GetY() - this->associated.box.h;
					/*if (facingR) {
						/*associated.RemoveComponent(sprite);
						sprite = new Sprite(associated, "./assets/img/sprite_prot_idle(63x128).png", 12, 0.1);
						associated.AddComponent(sprite);
					}
					else if (facingL) {
						associated.RemoveComponent(sprite);
						sprite = new Sprite(associated, "./assets/img/sprite_prot_idle_invertida.png", 12, 0.1);
						associated.AddComponent(sprite);
					}
						*/
				}
				//WallgrabL = false;
				//WallgrabR = false;
				tchfloor = true;
				airbone = false;
				Jump = 0;
				doubleJump = false;
				tchCeiling = false;

				// Checa se esta saindo de uma plataforma
				if ((this->associated.box.x + this->associated.box.w < tile->GetX()) || (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x)) {
					airbone = true;
					tchfloor = false;
					doubleJump = true;
					//tchCeiling = false;
					//cout << "Desencostou\n";
				}
			}
			// Colisao com tetos
			else if ((this->associated.box.y < tile->GetY() + tile->GetHeight() * ONETILESQUARE) 
				&& this->associated.box.y + this->associated.box.h / 4 > tile->GetY() + tile->GetHeight() * ONETILESQUARE
				//&& !WallgrabR && !WallgrabL//&& tile->floor
				//|| this->GetCenter().Distancia(Vec2(this->GetCenter().x, tile->GetY() + tile->GetHeight() * ONETILESQUARE)) <= this->associated.box.h / 2
				) {
				this->associated.box.y = tile->GetY() + tile->GetHeight() * ONETILESQUARE + 1;
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
				//WallgrabL = false;
				tchCeiling = false;

				// Wall Slide A DIREITA
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;		// QUEDA
					//wallX = tile->GetX();
					//WallgrabR = true;
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

				//WallgrabR = false;
				tchCeiling = false;

				// Wall Slide A ESQUERDA
				if (airbone && !tchfloor) {
					verticalSpeed /= 2;	// QUEDA
					//WallgrabL = true;
				}
			}
			else {
				//WallgrabL = false;
				//WallgrabR = false;
				tchfloor = false;
				tchCeiling = false;
				airbone = true;
				//cout << "desencostou do tile\n";

				// Checa se esta desencostando da parede A ESQUERDA
				if (tile->GetX() + tile->GetWidth() * ONETILESQUARE < this->associated.box.x) {
					//cout << "desencostou dessa parede <<\n";
					//	if (airbone) {
							//doubleJump = true;
					//		WallgrabL = false;
					//	}
				}

				// Checa se esta desencostando da parede A DIREITA
				if (this->associated.box.x + this->associated.box.w < tile->GetX()) {
					//cout << "desencostou dessa parede >>\n";
					//	if (airbone) {
							//doubleJump = true;
					//		WallgrabR = false;
					//	}
				}

				// Checa se esta desencostando do teto
				if (this->associated.box.y > tile->GetY() + ONETILESQUARE) {
					//cout << "desencostou do teto ^\n";
					//for (int i = 0; i < 50; i++);
					tchCeiling = false;
				}
			}
		}
	}
}


Vec2 Robot::GetCenter() {
	return associated.box.Center();
}


void Robot::Shoot(Vec2 target) {
	// Carrega um Tiro do Robo
	auto laserGO = new GameObject();
	laserGO->box = associated.box.Center();		// faz o tiro sair do centro do robô
	laserGO->box.y = associated.box.y + 25;		// faz ele sair do olho

	auto laser = new Laser(*laserGO, target.InclinacaoDaDiferenca(associated.box.Center()), LASER_SPEED,
		                     ROBOT_LASER_DAMAGE, LASER_MAX_DISTANCE, "./assets/img/minionBullet2.png", 3, 0.1);
	laser->robotLaser = true;
	auto laserSound = new Sound(*laserGO, "./assets/audio/SFX/LaserInimigo(Assim.)1.wav");
	laserGO->AddComponent(laserSound);
	laserSound->Play();
	laserGO->AddComponent(laser);

	Game::GetInstance().GetCurrentState().AddObject(laserGO);
}