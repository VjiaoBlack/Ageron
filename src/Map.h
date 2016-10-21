/*
 *  Map.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
// #include <SDL2/SDL_Image.h>

#include <vector>
#include <string>

#include <iostream>
#include <fstream>

#include "Renderer.h"
#include "KeyHandler.h"

using namespace std;

#ifndef _MAP_H_
#define _MAP_H_

class Tile {
public:
	static const int k_TileWidth = 32;
	static const int k_TileHeight = 32;

	enum TileType {
		k_Dirt,
		k_Stone,
		k_Sand,
		k_Water,

		k_NumTypes
	};

	Tile(int vegetationLevel, TileType type);
	Tile() : Tile(0, k_Dirt) { };

	int  getVegetationLevel() { return m_vegetationLevel; }
	void setVegetationLevel(int vl) { m_vegetationLevel = vl; }

	void draw(Renderer& r, double x);

private:
	// level of short vegetation at this tile - grass, etc
	// 		0 - 7
	int m_vegetationLevel;

	// base type
	TileType m_type;
};


class Map {
public:
    Map() { };

   	static const int k_GroundYPos = 600;

    bool load(string filename);

    void draw(Renderer& r);

private:
	vector<Tile> m_tiles;

};

#endif