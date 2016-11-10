/*
 *  Map.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <SDL2/SDL.h>
// #include <SDL2/SDL_Image.h>

#include <vector>
#include <string>

#include <iostream>
#include <fstream>

using namespace std;


#include "Renderer.h"
#include "KeyHandler.h"
#include "Scenery.h"
#include "Building.h"

class Tile {
public:
	static const int kTileWidth = 32;
	static const int kTileHeight = 32;

	enum TileType {
		kDirt,
		kStone,
		kSand,
		kWater,

		kNumTypes
	};

	Tile(int vegetationLevel, TileType type);
	Tile() : Tile(0, kDirt) { };

	int  getVegetationLevel() { return vegetationLevel; }
	void setVegetationLevel(int vl) { vegetationLevel = vl; }

	void draw(Renderer& r, double x);

private:
	// level of short vegetation at this tile - grass, etc
	// 		0 - 7
	int vegetationLevel;

	// base type
	TileType type;
};


class Map {
public:
    Map() { };

   	static const int kGroundYPos = 600;

    bool load(string filename);

    void draw(Renderer& r);

private:
	vector<Tile> tiles;

	vector<Building*> buildings;
	vector<Scenery*> scenery;

	map<string, BuildingAttr*> buildingAttr;
	map<string, SceneryAttr*> sceneryAttr;
	map<string, JobAttr*> jobAttr;
	map<string, MaterialAttr*> materialAttr;
	map<string, FoodAttr*> foodAttr;
	map<string, ToolAttr*> toolAttr;
};

#endif