/**
 * Ageron.cpp
 *
 * Victor Jiao (c) 2016
 */

#include <SDL2/SDL.h>

#include <stdio.h>
#include <string>

#include "Game.h"
#include "Renderer.h"

int main(int argc, char* args[]) {
    // Start up SDL and create window

    Game game(K_WINDOW_WIDTH, K_WINDOW_HEIGHT);
    if (!game.init()) {
        printf( "Failed to initialize!\n" );
    } else {
        // Load media, maps, etc.
        if (!game.loadMedia()) {
            printf( "Failed to load media!\n" );
        } else {
            game.run();
        }
    }

    // Free resources and close SDL
    game.renderer.close();

    return 0;
}
