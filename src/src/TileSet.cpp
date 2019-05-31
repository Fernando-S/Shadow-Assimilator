#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const char* file) : tileSet(*new GameObject(), file) {		// mudei para const char*

	if (!tileSet.IsOpen()) {								// sai do programa e exibe uma msg de erro se nao conseguir abrir o sprite
		std::cerr << "TileSet couldn't open the sprite! ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
	else {										// seta as dimensoes e o numero de colunas e linhas se conseguir abrir o sprite
		this->tileHeight = tileHeight;
		this->tileWidth = tileWidth;
		columns = tileSet.GetWidth()/tileWidth;
		rows = tileSet.GetHeight()/tileHeight;
	}
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	// checa se o index eh valido e sai do programa apos exibir uma msg de erro se nao for
	if (0 <= index <= (unsigned)rows*columns) {
		tileSet.SetClip((index%columns)*tileWidth, (index/columns)*tileHeight, tileHeight, tileHeight);
	}
	else {
		std::cerr << " ERROR: index for tile invalid! " << std::endl;
		exit(1);
	}

	tileSet.Render((int)x, (int)y);
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}