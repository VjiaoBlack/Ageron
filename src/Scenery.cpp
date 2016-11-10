/*
 *  Scenery.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Scenery.h"

using namespace std;

void Scenery::draw(Renderer& r) {
    
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

    if (type->name == "tree") {
		SDL_SetRenderDrawColor(r.SDLRenderer, 0x00, 0xFF, 0x00, 0xFF);
    } else if (type->name == "berry_bush") {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
    } else if (type->name == "flower") {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0xAA, 0xAA, 0xFF, 0xFF);
    } else {
    	SDL_SetRenderDrawColor(r.SDLRenderer, 0x00, 0x00, 0x00, 0xFF);
    }

    // TODO Make sure you're not drawing an invisible color!
    SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
}

