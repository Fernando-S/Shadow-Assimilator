#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cstdio>
#include <list>
#include <cstring>

using namespace std;

void converte(int coordenada[], int tamanho, int conteudo[], int contador, char tipo[], int linha, int coluna){
	int debug, i;
	
	/*
	cout << "\nVALORES PARA CONVERSAO\n";
	cout << "\ncontador: " << contador << endl;
	
	cout << "\nlinha: " << coordenada[0] << endl;
	cout << "coluna: " << coordenada[1] << endl;
	cout << "\ntamanho: " << tamanho << endl;
	cout << "\nconteudo: ";
	for(debug = 0 ; debug < tamanho ; debug++){
		cout << conteudo[debug] << " ";
	}
	cout << endl;

	system("PAUSE");
	*/
	
	//////////////////////////////////////////////////////
	//CONVERSÃO PARA TXT
	//////////////////////////////////////////////////////	
    
	//char tipoI[10];
		
        char filename[100];
        FILE *file;
        sprintf(filename, "Tile%02d_%s.txt", contador, tipo); /* Teste-00.txt; Teste-01.txt; ...; Teste-99.txt */
        //sprintf(filename, "Tile_%s_%d.txt", tipo, contador); /* Teste-00.txt; Teste-01.txt; ...; Teste-99.txt */
        file = fopen(filename, "wt");
        
        if (file != NULL) {     

        	char sentence[100];
        	
        	if(tipo[0] == 'L'){
        		
			sprintf(sentence, "1,%d,1\n\n", tamanho);
            fputs (sentence,file);
            
            for(i = 0 ; i < tamanho ; i++){
            	if(conteudo[i] < 10){
            		sprintf(sentence, "0%d,", conteudo[i]);
            		fputs (sentence,file);
				}else{
					sprintf(sentence, "%d,", conteudo[i]);
            		fputs (sentence,file);
				}
            	
			}
                   			
			//system("PAUSE");
			}		
        	
        	if(tipo[0] == 'C'){
        	sprintf(sentence, "%d,1,1\n\n", tamanho);
            fputs (sentence,file);
            
			for(i = 0 ; i < tamanho ; i++){
            	if(conteudo[i] < 10){
            		sprintf(sentence, "0%d,\n", conteudo[i]);
            		fputs (sentence,file);
				}else{
					sprintf(sentence, "%d,\n", conteudo[i]);
            		fputs (sentence,file);
				}
            	
			} 
			
			//system("PAUSE");
			}
        	
            
    	    fclose (file);
        }		 
		else {
            perror(filename);
            exit(EXIT_FAILURE);
        }		

	//cout << strlen(filename);

	//system("PAUSE");
	
	if(contador < 100){
		for(i = strlen(filename) - 4 ; i < 20 ; i++){
			filename[i] = '\0';
		}
	}else{
		 for(i = strlen(filename) - 4 ; i < 20 ; i++){
			filename[i] = '\0';
		}
	}
	
	//////////////////////////////////////////////////////
	//CONVERSÃO PARA O CODIGO
	//////////////////////////////////////////////////////	
	
	string TileName, TileSet, colide;
	int height, width;
	
	TileName = filename;
	TileSet = "tileSet";
	height = linha - coordenada[0]; //linha
	width = coordenada[1]; //coluna
	colide = "true";
	
  	ofstream myfile;
  	myfile.open("TileCode.txt",ios::app);
  	if (myfile.is_open()){
    myfile << "auto "<< TileName <<"GO = new GameObject();\n";
    
    myfile <<  TileName <<"GO->box.x = ("<< width <<") * "<< TileSet << "->GetTileWidth() + chaoGO->box.x;\n";
    myfile <<  TileName <<"GO->box.y = (-"<< height <<") * "<< TileSet << "->GetTileHeight() + chaoGO->box.y;\n\n";
    /*
    Tile00_ColunaGO->box.x = (quantidade de quadraros pra direita o esquerda do chaoGO->box.x) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_ColunaGO->box.y = (quantidade de quadrados pra cima ou pra baixo do chaoGO->box.y) * tileSet->GetTileHeight() + chaoGO->box.y;
    */
    myfile << "auto tileMap_"<< TileName <<" = new TileMap(*" << TileName << "GO, \"./assets/map/Level0/" << TileName <<".txt\", "<< TileSet << ");\n";
    myfile << "tileMap_"<< TileName <<"->colide = "<< colide << ";\n\n";
    
    myfile <<  TileName <<"GO->box.w = tileMap_"<< TileName << "->GetWidth() * " << TileSet << "->GetTileWidth();\n";
    myfile <<  TileName <<"GO->box.h = tileMap_"<< TileName << "->GetHeight() * " << TileSet << "->GetTileHeight();\n\n";
    
    myfile <<  TileName <<"GO->AddComponent(tileMap_" << TileName << ");\n";
    myfile <<  "objectArray.emplace_back(" << TileName << "GO);\n";
    
    myfile << "\n\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////// \n\n";
    
    myfile.close();
  }
  else
    cout << "Nao foi possivel abrir o arquivo";
  	return ;
	
//	system("PAUSE");
	
}


int main(int argc, char* argv[]) {
	string s, lixo;
  	fstream file;
  	int i, j, k, l, linha, coluna, prof, teste, cont, coordenada[2], tamanho, *conteudo, contador;
  	int debug, aux, aux1, aux2;
  	bool add;
  	
	contador = 0;
  	
  	ofstream ofs;
	ofs.open("TileCode.txt", std::ofstream::out | std::ofstream::trunc); // da clear no txt
	ofs.close();
	
	file.open("TileMap_Colisao1.txt");
	

	file>>linha;
	file.ignore();
	file>>coluna;
	file.ignore();
	file>>prof;
	
//	cout << linha << endl << coluna << endl << prof << endl;
//	system("PAUSE");
	
	file.ignore();
	file.ignore();
	
	i = coluna;
	
	long int tile[501][501];
	/*
	//clear
	for(i = 0 ; i < 501 ; i++){	
		for(j = 0; j < 501 ; j++){			
			cont[i][j] = 0; 
			cout << i << endl;
		}
	}
	*/

	for(i = 0 ; i <= linha - 1 ; i++){	
		for(j = 0; j < coluna ; j++){			
			file >> tile[i][j];
			file.ignore();
		}
	}
	
	/*
	
	//debug sem posições
	for (aux1 = 0; aux1 <= linha; aux1++){ //exibicao da matriz original
    	for (aux2 = 0; aux2 < coluna; aux2++){
      	cout << tile[aux1][aux2] << " ";  		
      	}
    cout << "\n";
  	}
	
	//debug com posições
	for (i = 0; i <= linha; i++){ //exibicao da matriz original
    	for (j = 0; j < coluna; j++){
      	cout <<"[" << i << "]" << "[" << j << "]: " <<  tile[i][j] << " ";  		
      	}
    cout << "\n";
  	}
	*/
	
	
	coordenada[0] = 0;
	coordenada[1] = 0;
	tamanho = 0;
	conteudo = new int [linha];
	
	
	cout << "\n\n\nLinha: " << linha << "\nColuna: " << coluna << endl;
	
	for (i = 0; i <= linha; i++){ //exibicao da matriz original
    	for (j = 0; j < coluna; j++){
      	cout << tile[i][j] << " ";  		
      	}
    cout << "\n";
  	}
	cout << endl;
	
	//////////////////////////////////////////////
	//conversão de colunas
	///////////////////////////////////////////////
	
	char tipo[] = "Coluna";
	
	for(j = 0 ; j <= coluna ; j++){	
		
		for(i = 0; i <= linha ; i++){
			if(i==0){
				if((tile[i][j] != 0) && (tile[i + 1][j] != 0)){
					
					tamanho = 0;
					coordenada[0] = i;
					coordenada[1] = j;
					conteudo[tamanho] = tile[i][j];
					tamanho++;
					
				//	if(j == 66){
				/*
						cout << "\nNOVA BOX NO INICIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl;
						system("PAUSE");	
				*/
				//	}
					
					
					
				}	
			}else{
				if(tile[i][j] == 0){
					if(tile[i-1][j] !=0 ){
					
					//cout << "\nFIM DA BOX NO MEIO\n";
					//system("PAUSE");
					
					if(tamanho > 0){
						
						converte(coordenada, tamanho, conteudo, contador, tipo, linha, coluna);
						contador++;	
					//	cout << "\nPASSA VALOR\n";
						/*
						cout << "\nFIM DA BOX NO MEIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl << endl;
						
						
				    	for (aux = 0; aux < tamanho; aux++){
				      		cout << tile[coordenada[0] + aux][coordenada[1]] << " ";  		
				      	}
						*/

						for(aux = 0 ; aux < tamanho ; aux ++){
							tile[coordenada[0] + aux][coordenada[1]] = 0;
						}
						//system("PAUSE");
						
					}
					
					
					coordenada[0] = 0;
					coordenada[1] = 0;
					tamanho = 0;
						for(debug = 0 ; debug <= linha ; debug++){
						conteudo[debug] = 0;
						}
					
					
					}
					
				}
				if(tile[i][j] != 0){
					if(tile[i-1][j] != 0){

					conteudo[tamanho] = tile[i][j];
					tamanho++;	
					
					/*
					cout << "\nADICIONA MAIS UM\n";
					cout << "\nlinha: " << coordenada[0] << endl;
					cout << "coluna: " << coordenada[1] << endl;
					cout << "\ntamanho: " << tamanho << endl;
					cout << "\nconteudo: ";
					for(debug = 0 ; debug < tamanho ; debug++){
						cout << conteudo[debug] << " ";
					}
					cout << endl;
					system("PAUSE");
					*/
					
					}
					else if((tile[i-1][j] == 0) && (tile[i+1][j] != 0)){
					tamanho = 0;
					coordenada[0] = i;
					coordenada[1] = j;
					aux = tile[i][j];
					conteudo[tamanho] = tile[i][j];
					tamanho++;	
					
					
					//if(j == 66){
					/*
						cout << "\nNOVA BOX NO MEIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl;
						system("PAUSE");	
					*/	
					//}
					

					
					}
					else if(i == linha){
						/*
					cout << "\nFIM DA BOX NO LIMITE DA LINHA\n";
					system("PAUSE");
					*/
					if(tamanho > 0){
						converte(coordenada, tamanho, conteudo, contador, tipo, linha, coluna);
						contador++;
					//	cout << "\nPASSA VALOR\n";	
						
						for(aux = 0 ; aux < tamanho ; aux ++){
							tile[coordenada[0] + aux][coordenada[1]] = 0;
						}
					}
					//tile[i][j] = 0;
					
					
					coordenada[0] = 0;
					coordenada[1] = 0;
					tamanho = 0;
						for(debug = 0 ; debug <= linha ; debug++){
						conteudo[debug] = 0;
						}
					
					}
				}
			}
				
		}
		
		
	}
	
	//////////////////////////////////////////////////////////////////////////////////	
	
	cout << "\n\n\nLinha: " << linha << "\nColuna: " << coluna << endl;
	
	for (i = 0; i <= linha; i++){ //exibicao da matriz original
    	for (j = 0; j < coluna; j++){
      	cout << tile[i][j] << " ";  		
      	}
    cout << "\n";
  	}
	cout << endl;
	
	
	//system("PAUSE");	
	
	/////////////////////////////////////////
	//conversão de linha
	/////////////////////////////////////////
	//contador = 0;
	sprintf(tipo, "Linha");
	
	for(i = 0; i < linha ; i++){			
		for(j = 0 ; j <= coluna ; j++){
			
			if(j==0){
				if(tile[i][j] != 0){
					
					tamanho = 0;
					coordenada[0] = i;
					coordenada[1] = j;
					conteudo[tamanho] = tile[i][j];
					tamanho++;
					/*
					if(i == 17){
					
						cout << "\nNOVA BOX NO INICIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl;
						system("PAUSE");	
					
					}
					*/
				}	
			}else{
				if(tile[i][j] == 0){
					if(tile[i][j - 1] !=0 ){
					
					if(tamanho > 0){
						
					//	cout << "\nPASSA VALOR\n";
						converte(coordenada, tamanho, conteudo, contador, tipo, linha, coluna);
						contador++;	
					/*	
					if(i == 17){	
						cout << "\nFIM DA BOX NO MEIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl << endl;
						system("PAUSE");
					}
					*/	
						for(aux = 0 ; aux < tamanho ; aux ++){
							tile[coordenada[0]][coordenada[1] + aux] = 0;
						}
						
					//	system("PAUSE");
						
					}
					
					
					coordenada[0] = 0;
					coordenada[1] = 0;
					tamanho = 0;
						for(debug = 0 ; debug <= linha ; debug++){
						conteudo[debug] = 0;
						}
					
					
					}
					
				}
				if(tile[i][j] != 0){
					if(tile[i][j-1] != 0){

					conteudo[tamanho] = tile[i][j];
					tamanho++;	
					
					/*
					if(i == 17){
						if(j == 74){
							
							cout << "\nADICIONA MAIS UM\n";
							cout << "\nlinha: " << coordenada[0] << endl;
							cout << "coluna: " << coordenada[1] << endl;
							cout << "\ntamanho: " << tamanho << endl;
							cout << "\nconteudo: ";
							for(debug = 0 ; debug < tamanho ; debug++){
								cout << conteudo[debug] << " ";
							}
							cout << endl;
							
							system("PAUSE");
						}
					}
					*/
					//system("PAUSE");
					
					}
					else if(tile[i][j-1] == 0){
					tamanho = 0;
					coordenada[0] = i;
					coordenada[1] = j;
					aux = tile[i][j];
					conteudo[tamanho] = tile[i][j];
					tamanho++;	
					/*
						if(i == 17){
						cout << "\nNOVA BOX NO MEIO\n";
						cout << "\nlinha: " << coordenada[0] << endl;
						cout << "coluna: " << coordenada[1] << endl;
						cout << "\ntamanho: " << tamanho << endl;
						cout << "\nconteudo: ";
						for(debug = 0 ; debug < tamanho ; debug++){
							cout << conteudo[debug] << " ";
						}
						cout << endl;
						system("PAUSE");
						}
					*/
					
					}
					else if(j == coluna){
				
					//cout << "\nFIM DA BOX NO LIMITE DA LINHA\n";
					//system("PAUSE");
					
					if(tamanho > 0){
						converte(coordenada, tamanho, conteudo, contador, tipo, linha, coluna);
						contador++;
					//	cout << "\nPASSA VALOR\n";	
						
						for(aux = 0 ; aux < tamanho ; aux ++){
							tile[coordenada[0]][coordenada[1] + aux] = 0;
						}
					}

					coordenada[0] = 0;
					coordenada[1] = 0;
					tamanho = 0;
						for(debug = 0 ; debug <= linha ; debug++){
						conteudo[debug] = 0;
						}
					
					}
				}				
			}
		}
		
	}	
	
	cout << "\n\n\nLinha: " << linha << "\nColuna: " << coluna << endl;
	
	for (i = 0; i <= linha; i++){ //exibicao da matriz original
    	for (j = 0; j < coluna; j++){
      	cout << tile[i][j] << " ";  		
      	}
    cout << "\n";
  	}
	cout << endl;
	
	
    cout << "\n\n FIM \n\n";
    
	
  	return 0;
}
