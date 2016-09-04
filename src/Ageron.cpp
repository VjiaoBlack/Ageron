/*
 *  Ageron.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include <stdio.h>
#include <string>

#include "Game.h"

int main(int argc, char* args[]) {
    // Start up SDL and create window

    Game game(1280, 780);
    if (!game.init()) {
        printf( "Failed to initialize!\n" );
    } else {
        // Load media
        if (!game.loadMedia()) {
            printf( "Failed to load media!\n" );
        } else {
            game.run();
        }
    }

    // Free resources and close SDL
    game.m_renderer.close();

    return 0;
}
