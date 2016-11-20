/**
 * Map.h
 *
 * Victor Jiao (c) 2016
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Building.h"
#include "Data.h"
#include "Formula.h"
#include "KeyHandler.h"
#include "Renderer.h"
#include "Scenery.h"

class BuildingAttr;
class SceneryAttr;
class JobAttr;
class MaterialAttr;
class FoodAttr;
class ToolAttr;
class Formula;

#define K_MAP_HEIGHT (600 * K_SCREEN_SCALE)

/**
 * Tile
 *
 * holds data for map tiles
 */
class Tile {
public:
	enum TileType {
		kDirt,
		kStone,
		kSand,
		kWater,

		kNumTypes
	};

	Tile(int vegetationLevel, TileType type);
	Tile() : Tile(0, kDirt) { };

	static void init(Renderer& r);

	int  getVegetationLevel() { return vegetationLevel; }
	void setVegetationLevel(int vl) { vegetationLevel = vl; }

	void draw(Renderer& r, double x);

	static vector<SDL_Texture*> tileset;

private:
	/**
	 * level of short vegetation at this tile - grass, etc
	 * 0 - 7
	 */
	int vegetationLevel;

	/** base type */
	TileType type;
};

/**
 * Map
 *
 * holds the data for game maps
 * also holds data for default game attributes
 */
class Map {
public:
    Map() { };

    bool load(Renderer& r, string filename);

    void draw(Renderer& r);

	vector<Tile> tiles;

	vector<Building*> buildings;
	vector<Scenery*> scenery;

	map<string, BuildingAttr*> buildingAttr;
	map<string, SceneryAttr*> sceneryAttr;
	map<string, JobAttr*> jobAttr;
	map<string, MaterialAttr*> materialAttr;
	map<string, FoodAttr*> foodAttr;
	map<string, ToolAttr*> toolAttr;

	map<string, Formula> formulas;

};

#endif