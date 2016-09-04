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
        m_renderer.m_SDLWindow = SDL_CreateWindow("Ageron",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   m_renderer.m_width, m_renderer.m_height, SDL_WINDOW_SHOWN);
        if (m_renderer.m_SDLWindow == NULL) {
            printf("Window could not be created - SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create m_renderer for window
            m_renderer.m_SDLRenderer = SDL_CreateRenderer(m_renderer.m_SDLWindow, -1,
                                                        SDL_RENDERER_ACCELERATED);
            if (m_renderer.m_SDLRenderer == NULL) {
                printf("Renderer could not be created - SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                // Initialize m_renderer color to white
                SDL_SetRenderDrawColor(m_renderer.m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

    m_player = Entity(20.0f, 20.0f, Color(1.0f, 0.0f, 0.0f, 1.0f));

    return success;
}

void Game::update() {
    m_player.update(m_keyHandler);
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
                m_keyHandler.pressKey(e.key.keysym.sym);
            } else if (e.type == SDL_KEYUP) {
                m_keyHandler.liftKey(e.key.keysym.sym);
            }
        }

        if (m_keyHandler.isKeyDown(SDLK_q)) {
            quit = true;
        }
        update();

        // Clear screen
        SDL_SetRenderDrawColor(m_renderer.m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_renderer.m_SDLRenderer);

        // Render red filled quad
        m_player.draw(m_renderer);

        // Update screen
        SDL_RenderPresent(m_renderer.m_SDLRenderer);

        // Update the surface
        SDL_UpdateWindowSurface(m_renderer.m_SDLWindow);

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
