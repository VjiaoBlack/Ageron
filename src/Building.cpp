/*
 *  Building.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Building.h"

using namespace std;

void Building::draw(Renderer& r) {

    double xOffset = ((int) r.xOffset % (Tile::kTileWidth * 100));

    if (xOffset < -1800.0) {
        xOffset += (Tile::kTileWidth * 100);
    }

    if (xOffset > 1800.0) {
        xOffset -= (Tile::kTileWidth * 100);
    }

    SDL_Rect fillRect = {(int) round(xpos + xOffset), 
                         Map::kGroundYPos - type->height * 32,
                         (int) type->width * 32, (int) type->height * 32};

    if (type->name == "tent") {
		SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
    } else if (type->name == "lean-to") {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
    } else if (type->name == "hut") {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
    } else {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0x00, 0x00, 0x00, 0xFF);
    }

    // TODO Make sure you're not drawing an invisible color!
    SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
}

