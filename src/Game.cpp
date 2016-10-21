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
                // int imgFlags = IMG_INIT_PNG;
                // if (!( IMG_Init(imgFlags) & imgFlags)) {
                //     printf("SDL_image could not initialize - SDL_image Error: %s\n",
                //            IMG_GetError());
                //     success = false;
                // }
            }
        }
    }

    m_player = Entity(32.0f, 64.0f, Color(1.0f, 0.0f, 0.0f, 1.0f));
    m_player.setXY(400, 400);

    m_map.load(K_MAP_FILE_PATH);

    return success;
}

void Game::update() {
    m_player.update(m_keyHandler);

    if (m_renderer.m_xOffset + m_player.getX() < 200) {
        m_renderer.m_xOffset += 5;
    } else if (m_renderer.m_xOffset + m_player.getX() > 900) {
        m_renderer.m_xOffset -= 5;
    }
}

void Game::run() {
    // Main loop flags
    bool quit = false;
    bool menu = true;

    // Event handler
    SDL_Event e;

    // start game button
    Rect startGame(200,400,100,100);


    // menu
    while (menu) {
        uint32_t start_tick = SDL_GetTicks();

        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // user requests QUIT
            if (e.type == SDL_QUIT) {
                quit = true;
                menu = false;
            } else if (e.type == SDL_KEYDOWN) {
                // user presses a key
                m_keyHandler.pressKey(e.key.keysym.sym);
            } else if (e.type == SDL_KEYUP) {
                m_keyHandler.liftKey(e.key.keysym.sym);
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // TODO: can we even store this in keyhandler?
                m_keyHandler.pressButton(e.button.button);
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                m_keyHandler.liftButton(e.button.button);
            } else if (e.type == SDL_MOUSEMOTION) {
                m_keyHandler.m_mouseX = e.motion.x;
                m_keyHandler.m_mouseY = e.motion.y;
                m_keyHandler.m_mouseXVel = e.motion.xrel;
                m_keyHandler.m_mouseYVel = e.motion.yrel;
            }
        }

        // update() block for keypresses
        if (m_keyHandler.isKeyDown(SDLK_q)) {
            quit = true;
            menu = false;
        }

        if (m_keyHandler.isButtonDown(SDL_BUTTON_LEFT)) {
            if (startGame.contains(m_keyHandler.m_mouseX,
                                   m_keyHandler.m_mouseY)) {
                menu = false;
            }
        }


        // Clear screen
        SDL_SetRenderDrawColor(m_renderer.m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(m_renderer.m_SDLRenderer);


        SDL_SetRenderDrawColor(m_renderer.m_SDLRenderer,
                               0xFF, 0x00, 0xFF, 0xFF);


        // round the width and height or calculate with m_x and m_y round offs?
        SDL_Rect fillRect = startGame.getSDLRect();

        SDL_RenderDrawRect(m_renderer.m_SDLRenderer, &fillRect);

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

        // render map
        m_map.draw(m_renderer);

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
