/**
 * Map.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Map.h"

using namespace std;

Tile::Tile(int vegetationLevel, TileType type)
		: vegetationLevel(vegetationLevel),
		  type(type) { }

void Tile::draw(Renderer& r, double x) {
    /** TODO: round the width and height or calculate with x and y round offs? */
	SDL_Rect fillRect = {(int) round(x), K_MAP_HEIGHT,
	                     K_TILE_SIZE, K_TILE_SIZE};

	/** catch case just in case there's no tileset */
	if (Tile::tileset[this->type] == NULL) {
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
	} else {
		SDL_RenderCopy(r.SDLRenderer, tileset[this->type], NULL, &fillRect);
	}
}

vector <SDL_Texture*> Tile::tileset;

void Tile::init(Renderer& r) {
	Tile::tileset.resize(Tile::TileType::kNumTypes);
	for (int i = 0; i < Tile::TileType::kNumTypes; i++) {
		Tile::tileset[i] = NULL;
	}

	Tile::tileset[Tile::TileType::kDirt]  = r.loadSurface("res/tileset/dirt.png");
	Tile::tileset[Tile::TileType::kStone] = r.loadSurface("res/tileset/gravel.png");
	Tile::tileset[Tile::TileType::kSand]  = r.loadSurface("res/tileset/sand.png");
	Tile::tileset[Tile::TileType::kWater] = r.loadSurface("res/tileset/water.png");
}

bool Map::load(Renderer& r, string filename) {
	initBuildingAttrs(r, buildingAttr);
	initSceneryAttrs(r, sceneryAttr);
	initJobAttrs(r, jobAttr);
	initMaterialAttrs(r, materialAttr);
	initFoodAttrs(r, foodAttr);
	initToolAttrs(r, toolAttr);
	initFormulas(formulas);


	Tile::init(r);


	ifstream mapFile;
	mapFile.open(filename);

	int width;
	char c, d;

	mapFile >> width;

	printf("Loading Map... size: %d\n", width);

	for (int i = 0; i < width; i++) {
		mapFile >> d >> c;

		Tile tile = Tile(d - '0', (Tile::TileType) (c - '0'));
		tiles.push_back(tile);
	}

	/** read scenery */
	string s;
	int n;
	mapFile >> s >> n;
	cout << s << " " << n << endl;
	while (n--) {
		string name;
		int xpos;

		mapFile >> name >> xpos;
		scenery.push_back(new Scenery(sceneryAttr[name], xpos * K_TILE_SIZE));
	}

	/** read buildings */
	mapFile >> s >> n;
	cout << s << " " << n << endl;
	while (n--) {
		string name;
		int xpos;

		mapFile >> name >> xpos;
		buildings.push_back(new Building(buildingAttr[name], xpos * K_TILE_SIZE));
	}

	/** read units */
	mapFile >> s >> n;
	while (n--) {
		string name;
		int xpos;
	}

	printf("Done, read %lu tiles\n", tiles.size());

	/** TODO: actually do a meaningful valid map check */
	return true;
}

void Map::draw(Renderer& r) {
	/** draw sky */
	SDL_Rect skyRect = {0, 0,
	                     K_WINDOW_WIDTH, K_MAP_HEIGHT};

    SDL_SetRenderDrawColor(r.SDLRenderer, 0xCC, 0xEE, 0xFF, 0xFF);
	SDL_RenderFillRect(r.SDLRenderer, &skyRect);

	/** draw all the tiles */
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].draw(r, r.displayX(i * K_TILE_SIZE));
	}

	/** draw space under tiles */
	SDL_Rect fillRect = {0, K_MAP_HEIGHT + K_TILE_SIZE,
	                     K_WINDOW_WIDTH, K_WINDOW_HEIGHT - (K_MAP_HEIGHT + K_TILE_SIZE)};

    SDL_SetRenderDrawColor(r.SDLRenderer, 0x33, 0x22, 0x0A, 0xFF);
	SDL_RenderFillRect(r.SDLRenderer, &fillRect);
	
	/** draw buildings and stuff at offset */
	for (int i = 0; i < scenery.size(); i++) {
		scenery[i]->draw(r);
	}

	for (int i = 0; i < buildings.size(); i++) {
		buildings[i]->draw(r);
	}	
}
