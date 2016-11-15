/**
 * Building.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Building.h"

using namespace std;

void Building::draw(Renderer& r) {
    SDL_Rect fillRect = {(int) r.displayX(xpos), 
                         Map::kGroundYPos - type->height * 32,
                         (int) type->width * 32, (int) type->height * 32};

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
    } else {
        SDL_RenderCopy(r.SDLRenderer, this->type->texture, NULL, &fillRect);
    }

    SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
}

