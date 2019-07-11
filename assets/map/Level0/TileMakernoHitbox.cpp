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
	
	file.open("Mapa_1.3.txt");
	

	file>>linha;
	file.ignore();
	file>>coluna;
	file.ignore();
	file>>prof;
	
	file.ignore();
	file.ignore();
	
	i = coluna;
	
	long int tile[501][501];
	
	for(i = 0 ; i <= linha ; i++){	
		for(j = 0; j < coluna ; j++){			
			file >> tile[i][j];
			file.ignore();
			file.ignore();
		}
	}
	
	for (aux1 = 0; aux1 <= linha; aux1++){ //exibicao da matriz original
    	for (aux2 = 0; aux2 < coluna; aux2++){
      	cout << tile[aux1][aux2] << " ";  		
      	}
    cout << "\n";
	}
	
	ofstream myfile;
  	myfile.open("teste.txt");
  	if (myfile.is_open()){
  		
  	for (aux1 = 0; aux1 <= linha; aux1++){ //exibicao da matriz original
    	for (aux2 = 0; aux2 < coluna; aux2++){
    		if(tile[aux1][aux2] < 10){
    			myfile << "0" <<tile[aux1][aux2] << ",";
			}else{
				myfile << tile[aux1][aux2] << ",";
			}			
      	}
    myfile << "\n";
	}
    myfile.close();
  	}
	
return 0;
}
