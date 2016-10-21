/*
 *  Map.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Map.h"

using namespace std;

Tile::Tile(int vegetationLevel, TileType type)
		: m_vegetationLevel(vegetationLevel),
		  m_type(type) { }

void Tile::draw(Renderer& r, double x) {
    // round the width and height or calculate with m_x and m_y round offs?
	SDL_Rect fillRect = {(int) round(x), Map::k_GroundYPos,
	                     k_TileWidth, k_TileHeight};

	switch(m_type) {
		case k_Dirt:
		    SDL_SetRenderDrawColor(r.m_SDLRenderer, 0xBB, 0x77, 0x22, 0xFF);
			break;
		case k_Stone:
		    SDL_SetRenderDrawColor(r.m_SDLRenderer, 0x88, 0x88, 0x88, 0xFF);
			break;
		case 2:
		    SDL_SetRenderDrawColor(r.m_SDLRenderer, 0xCC, 0xCC, 0x00, 0xFF);
			break;
		case k_Water:
		    SDL_SetRenderDrawColor(r.m_SDLRenderer, 0x00, 0x00, 0xCC, 0xFF);
			break;
	}

	SDL_RenderDrawRect(r.m_SDLRenderer, &fillRect);
}

bool Map::load(string filename) {
	ifstream mapFile;
	mapFile.open(filename);

	int width;
	char c, d;

	mapFile >> width;

	printf("Loading Map... size: %d\n", width);

	// get rid of new line char
	mapFile >> c;
	for (int i = 0; i < width; i++) {
		mapFile >> c >> d;

		Tile tile = Tile(d - '0', (Tile::TileType) (c - '0'));
		m_tiles.push_back(tile);
	}

	printf("Done, read %lu tiles\n", m_tiles.size());

	// TODO: actually do a meaningful valid map check
	return true;
}

void Map::draw(Renderer& r) {
	// // draw all the tiles
	// for (int i = 0; i < m_tiles.size(); i++) {
	// 	m_tiles[i].draw(r, r.m_xOffset + i * Tile::k_TileWidth);
	// }

	// draw all the tiles that are visible 
	int offset = r.m_xOffset;

	offset = ((int) r.m_xOffset % (Tile::k_TileWidth * m_tiles.size()));
	
	int x = offset;
	int i = 0;

	while(x < 0 - Tile::k_TileWidth) {
		x += Tile::k_TileWidth;
		i++;
	}

	while (x < K_WINDOW_WIDTH) {
		m_tiles[i].draw(r, x);

		x += Tile::k_TileWidth;
		i++;
	}

	x = offset - Tile::k_TileWidth;
	i = m_tiles.size() - 1;

	while (x >= 0 - Tile::k_TileWidth) {
		m_tiles[i].draw(r, x);

		x -= Tile::k_TileWidth;
		i--;
	}
}