/*
 *  Map.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Map.h"

using namespace std;

Tile::Tile(int vegetationLevel, TileType type)
		: vegetationLevel(vegetationLevel),
		  type(type) { }

void Tile::draw(Renderer& r, double x) {
    // round the width and height or calculate with x and y round offs?
	SDL_Rect fillRect = {(int) round(x), Map::kGroundYPos,
	                     kTileWidth, kTileHeight};

	switch(type) {
		case kDirt:
		    SDL_SetRenderDrawColor(r.SDLRenderer, 0xBB, 0x77, 0x22, 0xFF);
			break;
		case kStone:
		    SDL_SetRenderDrawColor(r.SDLRenderer, 0x88, 0x88, 0x88, 0xFF);
			break;
		case 2:
		    SDL_SetRenderDrawColor(r.SDLRenderer, 0xCC, 0xCC, 0x00, 0xFF);
			break;
		case kWater:
		    SDL_SetRenderDrawColor(r.SDLRenderer, 0x00, 0x00, 0xCC, 0xFF);
			break;
	}

	SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
}

bool Map::load(string filename) {
	// init attributes

	initBuildingAttrs(buildingAttr);
	initSceneryAttrs(sceneryAttr);
	initJobAttrs(jobAttr);
	initMaterialAttrs(materialAttr);
	initFoodAttrs(foodAttr);
	initToolAttrs(toolAttr);

	ifstream mapFile;
	mapFile.open(filename);

	int width;
	char c, d;

	mapFile >> width;

	printf("Loading Map... size: %d\n", width);

	// get rid of new line char
	// mapFile >> c;
	for (int i = 0; i < width; i++) {
		mapFile >> d >> c;

		Tile tile = Tile(d - '0', (Tile::TileType) (c - '0'));
		tiles.push_back(tile);
	}

	// // read scenery
	string s;
	int n;
	mapFile >> s >> n;
	cout << s << " " << n << endl;
	while (n--) {
		string name;
		int xpos;

		mapFile >> name >> xpos;
		scenery.push_back(new Scenery(sceneryAttr[name], xpos * 32));
	}

	// read buildings
	mapFile >> s >> n;
	cout << s << " " << n << endl;
	while (n--) {
		string name;
		int xpos;

		mapFile >> name >> xpos;
		buildings.push_back(new Building(buildingAttr[name], xpos * 32));
	}

	// read units
	mapFile >> s >> n;
	while (n--) {
		string name;
		int xpos;
	}

	printf("Done, read %lu tiles\n", tiles.size());

	// TODO: actually do a meaningful valid map check
	return true;
}

void Map::draw(Renderer& r) {
	// // draw all the tiles
	// for (int i = 0; i < tiles.size(); i++) {
	// 	tiles[i].draw(r, r.xOffset + i * Tile::kTileWidth);
	// }

	// draw all the tiles that are visible 
	int offset = r.xOffset;

	offset = ((int) r.xOffset % (Tile::kTileWidth * tiles.size()));
	
	int x = offset;
	int i = 0;

	while(x < 0 - Tile::kTileWidth) {
		x += Tile::kTileWidth;
		i++;
	}

	while (x < K_WINDOW_WIDTH) {
		tiles[i].draw(r, x);

		x += Tile::kTileWidth;
		i++;
	}

	x = offset - Tile::kTileWidth;
	i = tiles.size() - 1;

	while (x >= 0 - Tile::kTileWidth) {
		tiles[i].draw(r, x);

		x -= Tile::kTileWidth;
		i--;
	}


	// draw buildings and stuff at offset
	for (i = 0; i < buildings.size(); i++) {
		buildings[i]->draw(r);
	}	

	for (i = 0; i < scenery.size(); i++) {
		scenery[i]->draw(r);
	}

}