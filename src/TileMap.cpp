#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet *tileSet) : Component(associated) {
	// seta as dimensoes com falore
	mapWidth = -1;
	mapHeight = -1;
	mapDepth = -1;
	Load(file);
	SetTileSet(tileSet);
	
	//associated.AddComponent(new Collider(associated));
	
	collider = new Collider(associated);
	associated.AddComponent(collider);
}

void TileMap::Load(std::string file) {
	int tileIndex, i;
	char virgula;
	std::ifstream tileMapFile;
	std::string linha;

	// abre o arquivo com o tileMap sai do programa mostrando uma msg de erro caso o arquivo seja vazio
	tileMapFile.open(file);
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
		RenderLayer(i, (int)this->associated.box.x - Camera::pos.x, (int)this->associated.box.y - Camera::pos.y);	// chama o render de cada layer
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int x, y;

	for (x = 0; x < mapWidth; x++) { 
		for (y = 0; y < mapHeight; y++) {
		// sem PARALLAX para 2D chapado
			tileSet->RenderTile((unsigned)At(x, y, layer), cameraX + x * tileSet->GetTileWidth(), cameraY + y * tileSet->GetTileHeight());
		
		// - PARALLAX para perspectiva esquerda acima
			// Dinamico
			//tileSet->RenderTile((unsigned)At(x, y, layer), cameraX + x*tileSet->GetTileWidth() - PARALLAX * layer*cameraX, cameraY +  y*tileSet->GetTileHeight() - PARALLAX * layer*cameraY);
			// Fixo
			//tileSet->RenderTile((unsigned)At(x, y, layer), cameraX + x * tileSet->GetTileWidth() - PARALLAX * layer, cameraY + y * tileSet->GetTileHeight() - PARALLAX * layer);
		// + PARALLAX para perspectiva direita abaixo
			// Dinamico
			//tileSet->RenderTile((unsigned)At(x, y, layer), cameraX + x*tileSet->GetTileWidth() + PARALLAX * layer*cameraX, cameraY +  y*tileSet->GetTileHeight() + PARALLAX * layer*cameraY);
			// Fixo
			//tileSet->RenderTile((unsigned)At(x, y, layer), cameraX + x*tileSet->GetTileWidth() + PARALLAX * layer, cameraY +  y*tileSet->GetTileHeight() + PARALLAX * layer);
			
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

int TileMap::GetY() {
	return (int)this->associated.box.y;
}

int TileMap::GetX() {
	return (int)this->associated.box.x;
}

Rect TileMap::GetBox() {
	return this->associated.box;
}

void TileMap::NotifyCollision(GameObject& other) {
	auto tile = (TileMap*)other.GetComponent("TileMap");

	// Checa se tem um tile colidindo horizontalmente com outro
	if (tile && ((tile->GetX() <= this->associated.box.x + this->associated.box.w)
				|| (this->associated.box.x <= tile->GetX() + tile->GetWidth()*ONETILESQUARE))) {
		this->floor = true;
	}
}