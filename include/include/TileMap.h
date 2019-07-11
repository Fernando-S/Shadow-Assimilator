#pragma once

#ifndef TILEMAP_H
#define TILEMAP_H

#include <fstream>
#include <iostream>
#include "TileSet.h" 
#include "GameObject.h"

#include "Collider.h"

#define PARALLAX 0.5
#define ONETILESQUARE 64				// tamanho de 1 tile

class TileMap : public Component{
public:
		TileMap(GameObject& associated, std::string file, TileSet *tileSet);
		void Load(std::string file);
		void SetTileSet(TileSet* tileSet);
		int& At(int x, int y, int z = 0);
		void Render() override;
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
		int GetWidth();
		int GetHeight();
		int GetDepth();
		void Update(float dt) override;
		bool Is(std::string type) override;
		void NotifyCollision(GameObject& other) override;
		int GetY();
		int GetX();
		Rect GetBox();

		bool floor = false, colide = false;
		Collider *collider;

private:
		std::vector<int> tileMatrix;
		TileSet* tileSet;
		int mapWidth;
		int mapHeight;
		int mapDepth;

};

#endif	//TILEMAP_H