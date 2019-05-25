#pragma once

#ifndef TILESET_H
#define TILESET_H

#include <iostream>
#include "Sprite.h"

class TileSet{
public:
		TileSet(int tileWidth, int tileHeight, const char* file);		// mudei para const char*
		void RenderTile(unsigned index, float x, float y);
		int GetTileWidth();
		int GetTileHeight();

private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;

};

#endif	//TILESET_H