/*
 *  Game.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Game.h"

bool Game::init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize - SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        fRenderer.fSDLWindow = SDL_CreateWindow("Ageron",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   fRenderer.fWidth, fRenderer.fHeight, SDL_WINDOW_SHOWN);
        if (fRenderer.fSDLWindow == NULL) {
            printf("Window could not be created - SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create fRenderer for window
            fRenderer.fSDLRenderer = SDL_CreateRenderer(fRenderer.fSDLWindow, -1,
                                                        SDL_RENDERER_ACCELERATED);
            if (fRenderer.fSDLRenderer == NULL) {
                printf("Renderer could not be created - SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                // Initialize fRenderer color to white
                SDL_SetRenderDrawColor(fRenderer.fSDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!( IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize - SDL_image Error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }

    fPlayerX = 0.0f;
    fPlayerY = 0.0f;

    fPlayerXVel = 0.0f;
    fPlayerYVel = 0.0f;

    return success;
}

void Game::update() {
    if (fPlayerYVel <= 10.0f) {
        fPlayerYVel += 0.5f;
    }

    if (fKeyHandler.isKeyDown(SDLK_UP)) {
        fPlayerYVel = -7.0f;
    }

    if (fPlayerXVel < 0) {
        if (fPlayerXVel < -0.3f) {
            fPlayerXVel += 0.3f;
        } else {
            fPlayerXVel = 0;
        }
    } else if (fPlayerXVel > 0) {
        if (fPlayerXVel > 0.3f) {
            fPlayerXVel -= 0.3f;
        } else {
            fPlayerXVel = 0;
        }
    }


    if (fKeyHandler.isKeyDown(SDLK_LEFT)) {
        fPlayerXVel = -3.0f;
    }

    if (fKeyHandler.isKeyDown(SDLK_RIGHT)) {
        fPlayerXVel = 3.0f;
    }

    fPlayerX += fPlayerXVel;

    if (fPlayerY + fPlayerYVel <= 760) {
        fPlayerY += fPlayerYVel;
    } else {
        fPlayerY = 760.0f;
    }
}

void Game::run() {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // While application is running
    while(!quit) {

    uint32_t start_tick = SDL_GetTicks();




        // Handle events on queue
        while (SDL_PollEvent(&e) != 0 ) {
            // User requests quit
            if (e.type == SDL_QUIT ) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                // User presses a key
                fKeyHandler.pressKey(e.key.keysym.sym);
            } else if (e.type == SDL_KEYUP) {
                fKeyHandler.liftKey(e.key.keysym.sym);
            }
        }

        update();

        // Clear screen
        SDL_SetRenderDrawColor(fRenderer.fSDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(fRenderer.fSDLRenderer);

        // Render red filled quad
        SDL_Rect fillRect = {(int)fPlayerX, (int)fPlayerY, 20, 20};
        SDL_SetRenderDrawColor(fRenderer.fSDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(fRenderer.fSDLRenderer, &fillRect);

        // Update screen
        SDL_RenderPresent(fRenderer.fSDLRenderer);

        // Update the surface
        SDL_UpdateWindowSurface(fRenderer.fSDLWindow);

        // usleep(0);

        uint32_t end_tick = SDL_GetTicks();

        int wait_ticks = 16 - (end_tick - start_tick);

        if (wait_ticks < 0) {
            wait_ticks = 0;
        }

        SDL_Delay(wait_ticks);
    }
}

bool Game::loadMedia() {
    // Loading success flag
    bool success = true;

    return success;
}
