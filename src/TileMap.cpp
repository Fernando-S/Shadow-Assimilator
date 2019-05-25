#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet *tileSet) : Component(associated) {
	// seta as dimensoes com falore
	mapWidth = -1;
	mapHeight = -1;
	mapDepth = -1;
	Load(file);
	SetTileSet(tileSet);
}

void TileMap::Load(std::string file) {
	int tileIndex, i;
	char virgula;
	std::ifstream tileMapFile;
	std::string linha;

	// abre o arquivo com o tileMap sai do programa mostrando uma msg de erro caso o arquivo seja vazio
	tileMapFile.open("./assets/map/tileMap.txt");
	if (!tileMapFile.is_open()) {
		std::cerr << " ERROR: tileMap.txt couldn't be opened!" << std::endl;
		exit(1);
	}

	tileMapFile >> linha;
	sscanf_s(linha.c_str(), "%d,%d,%d,", &mapHeight, &mapWidth, &mapDepth);						//.c_str() pois const char* nao funciona

	// se o mapa nao tem dimensoes, exibe uma msg de erro e sai do programa
	if ( (mapWidth < 0) || (mapHeight < 0) || (mapDepth < 0)) {
		std::cerr << " ERROR: mapHeight, mapWidth or mapDepth couldn't be read" << std::endl;
		tileMapFile.close();
		exit(1);
	}

	// monta o mapa
	for (i = 0; i < mapWidth*mapHeight*mapDepth; i++) {
		tileMapFile >> tileIndex;
		tileMapFile >> virgula;
		tileMatrix.push_back(tileIndex - 1);
	}

	// fecha o arquivo com o tileMap depois de carrega-lo
	tileMapFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	if (x >= mapWidth || y >= mapHeight || z >= mapDepth) {
		std::cerr <<  " Position for tilemap not valid!" << std::endl;
		exit(1);
	}
	return tileMatrix[z*mapWidth*mapHeight + y * mapWidth + x];
}

void TileMap::Render() {
	int i;

	for (i = 0; i < mapDepth; i++) {
		RenderLayer(i, (int)associated.box.x, (int)associated.box.y);	// chama o render de cada layer
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int x, y;

	for (x = 0; x < mapWidth; x++) {
		for (y = 0; y < mapHeight; y++) {
//			tileSet->RenderTile((unsigned)At(x, y, layer), x*tileSet->GetTileWidth(), y*tileSet->GetTileHeight()); // renderiza cada tile com efeito de parrallax
			tileSet->RenderTile((unsigned)At(x, y, layer), x*tileSet->GetTileWidth() - cameraX - PARALLAX * layer*cameraX, y*tileSet->GetTileHeight() - cameraY - PARALLAX * layer*cameraY);
		}
	}
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {
	if (type == "TileMap")
		return true;
	else
		return false;
}