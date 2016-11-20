/**
 * Building.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Building.h"

using namespace std;

void Building::draw(Renderer& r) {
    SDL_Rect fillRect = {(int) r.displayX(xpos), 
                         K_MAP_HEIGHT - type->height * K_TILE_SIZE,
                         (int) type->width * K_TILE_SIZE,
                         (int) type->height * K_TILE_SIZE};

    // in case the textures aren't loaded, use colored rects
    if (!this->type->texture) {
        if (type->name == "tent") {
    		SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
        } else if (type->name == "lean-to") {
        	SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
        } else if (type->name == "hut") {
        	SDL_SetRenderDrawColor(r.SDLRenderer, 0xDD, 0xDD, 0x77, 0xFF);
        } else {
        	SDL_SetRenderDrawColor(r.SDLRenderer, 0x00, 0x00, 0x00, 0xFF);
        }
        SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
    } else {
        SDL_RenderCopy(r.SDLRenderer, this->type->texture, NULL, &fillRect);
    }
}

