/*###################################################################################
# Universidade de Brasilia															#
#	Trabalho final da disciplina de Introducao ao Desenvolvimento de Jogos			#
#																					#
#	       Alunos 										Matriculas	 				#
#								Programadores										#
#	Fernando Sobral N�brega								15/0034911					#																					
#	Pedro Augusto de Sousa Negr�o						17/0153789					#
#																					#
#								Artistas											#
#	Camila Bontempo Sidersky							15/0120753					#
#	Ralison Mar�al Resende 								17/0154858					#
#	Paty/Tayna																		#
#																					#
#								Musicos												#
#	Enzo Aprile Lopes Velloso							16/0118999					#
#	Filipe Campos Nunes de Souza						13/0147532					#
#	Marina Morena Riz�rio do Prado						14/002791					#
#																					#
#	OS: Windows 10 Pro																#
#	IDE: Visual Studio 2017															#
###################################################################################*/


#include "Game.h"
#include "TitleState.h"

int main(int argc, char* argv[]) {
	Game::GetInstance().Push(new TitleState);			// Seta o primeiro estado de jogo como sendo TitleState
	Game::GetInstance().Run();							// Comeca a rodar o jogo
	return 0;
}