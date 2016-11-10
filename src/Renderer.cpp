/*
 *  Renderer.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Renderer.h"

void Renderer::close() {
    // Destroy window
    SDL_DestroyWindow(SDLWindow);
    SDLWindow = NULL;

    // TODO: Destroy fRenderer?

    // Quit SDL subsystems
    SDL_Quit();
}
