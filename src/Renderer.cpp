/**
 * Renderer.cpp
 * 
 * Victor Jiao (c) 2016
 */

#include "Renderer.h"

void Renderer::close() {
    /** Destroy window */
    SDL_DestroyWindow(SDLWindow);
    SDLWindow = NULL;

    /** TODO: Destroy fRenderer? */

    /** Quit SDL subsystems */
    SDL_Quit();
}

int Renderer::displayX(int x) {
	/** move coordinate into screen-space. */
	x += (int) xOffset;

	while (x >= width) {
		x -= 100 * K_TILE_SIZE;
	}

	while (x <= 0 - width) {
		x += 100 * K_TILE_SIZE;
	}

	return x;
}

SDL_Texture* Renderer::loadSurface(std::string path) {
	/** The final optimized image */
	/** SDL_Surface* optimizedSurface = NULL; */

	/** Load image at specified path */
	SDL_Texture* loadedSurface = IMG_LoadTexture(this->SDLRenderer, path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// TODO: Convert surface to screen format
		// optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		// if( optimizedSurface == NULL )
		// {
		// 	printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		// }

		// Get rid of old loaded surface
		// SDL_FreeSurface( loadedSurface );
	}

	/** return optimizedSurface; */
	return loadedSurface;
}


void Renderer::drawText(string text, SDL_Color color, TTF_Font* font, SDL_Rect &layout) {
    const char* ctext = text.c_str();
    SDL_Surface* surface = TTF_RenderText_Solid(font, ctext, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(SDLRenderer, surface);
    TTF_SizeText(font, ctext, &layout.w, &layout.h);
    SDL_RenderCopy(SDLRenderer, texture, NULL, &layout);
}
