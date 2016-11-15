/**
 * Game.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Game.h"

bool Game::init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize - SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        /** Create window */
        renderer.SDLWindow = SDL_CreateWindow("Ageron",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   renderer.width, renderer.height, SDL_WINDOW_SHOWN);
        if (renderer.SDLWindow == NULL) {
            printf("Window could not be created - SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            /** Create renderer for window */
            renderer.SDLRenderer = SDL_CreateRenderer(renderer.SDLWindow, -1,
                                                        SDL_RENDERER_ACCELERATED);
            if (renderer.SDLRenderer == NULL) {
                printf("Renderer could not be created - SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                /** Initialize renderer color to white */
                SDL_SetRenderDrawColor(renderer.SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                /** Initialize PNG loading */
                int imgFlags = IMG_INIT_PNG;
                if (!( IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize - SDL_image Error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }

    if (TTF_Init() != 0){
        printf("TTF_Init error\n");
        SDL_Quit();
        return 1;
    }
 
    /** this opens a font style and sets a size */
    sans = TTF_OpenFont("res/UbuntuMono-R.ttf", 24);
    numFrames = 0;
    passedTime = 0;

    player = Entity(32.0f, 64.0f, Color(1.0f, 0.0f, 0.0f, 1.0f));
    player.setXY(400, 400);

    map.load(renderer, K_MAP_FILE_PATH);

    return success;
}

void Game::update() {
    player.update(keyHandler);

    if (renderer.xOffset + player.getX() < 200) {
        renderer.xOffset += 5;
    } else if (renderer.xOffset + player.getX() > 900) {
        renderer.xOffset -= 5;
    }
}

void Game::run() {
    /* Main loop flags */
    bool quit = false;
    bool menu = true;

    /* Event handler */
    SDL_Event e;

    /* start game button */
    Rect startGame(200,400,100,100);


    /* menu */
    while (menu) {
        uint32_t start_tick = SDL_GetTicks();

        /* handle events on queue */
        while (SDL_PollEvent(&e) != 0) {
            /* user requests QUIT */
            if (e.type == SDL_QUIT) {
                quit = true;
                menu = false;
            } else if (e.type == SDL_KEYDOWN) {
                /* user presses a key */
                keyHandler.pressKey(e.key.keysym.sym);
            } else if (e.type == SDL_KEYUP) {
                keyHandler.liftKey(e.key.keysym.sym);
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                /* TODO: can we even store this in keyhandler? */
                keyHandler.pressButton(e.button.button);
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                keyHandler.liftButton(e.button.button);
            } else if (e.type == SDL_MOUSEMOTION) {
                keyHandler.mouseX = e.motion.x;
                keyHandler.mouseY = e.motion.y;
                keyHandler.mouseXVel = e.motion.xrel;
                keyHandler.mouseYVel = e.motion.yrel;
            }
        }

        /** update() block for keypresses */
        if (keyHandler.isKeyDown(SDLK_q)) {
            quit = true;
            menu = false;
        }

        if (keyHandler.isButtonDown(SDL_BUTTON_LEFT)) {
            if (startGame.contains(keyHandler.mouseX,
                                   keyHandler.mouseY)) {
                menu = false;
            }
        }


        /** Clear screen */
        SDL_SetRenderDrawColor(renderer.SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.SDLRenderer);


        SDL_SetRenderDrawColor(renderer.SDLRenderer,
                               0xFF, 0x00, 0xFF, 0xFF);


        /** round the width and height or calculate with x and y round offs? */
        SDL_Rect fillRect = startGame.getSDLRect();

        SDL_RenderDrawRect(renderer.SDLRenderer, &fillRect);

        /** Update screen */
        SDL_RenderPresent(renderer.SDLRenderer);

        /** Update the surface */
        SDL_UpdateWindowSurface(renderer.SDLWindow);

        uint32_t end_tick = SDL_GetTicks();

        int wait_ticks = 16 - (end_tick - start_tick);

        if (wait_ticks < 0) {
            wait_ticks = 0;
        }

        SDL_Delay(wait_ticks);
    }


    /** While application is running */
    while(!quit) {

        uint32_t start_tick = SDL_GetTicks();

        /** Handle events on queue */
        while (SDL_PollEvent(&e) != 0 ) {
            /** User requests quit */
            if (e.type == SDL_QUIT ) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                /** User presses a key */
                keyHandler.pressKey(e.key.keysym.sym);
            } else if (e.type == SDL_KEYUP) {
                keyHandler.liftKey(e.key.keysym.sym);
            }
        }

        if (keyHandler.isKeyDown(SDLK_q)) {
            quit = true;
        }
        update();

        /** Clear screen */
        SDL_SetRenderDrawColor(renderer.SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.SDLRenderer);

        /** render map */
        map.draw(renderer);

        /** Render red filled quad */
        player.draw(renderer);

        if (keyHandler.isKeyDown(SDLK_DOWN)) {
            /** round the width and height or calculate with x and y round offs? */
            SDL_Rect fillRect = {Tile::kTileWidth * 4, Tile::kTileWidth * 4, 
                                 Tile::kTileWidth * 2, Tile::kTileWidth * 2};

            SDL_SetRenderDrawColor(renderer.SDLRenderer, 0x00, 0x00, 0x00, 0xFF);

            /** TODO Make sure you're not drawing an invisible color! */

            SDL_RenderDrawRect(renderer.SDLRenderer, &fillRect);
        }

        SDL_SetRenderDrawColor(renderer.SDLRenderer, 0, 0, 0, 0xFF);

        drawResources();

        /** Update screen */
        SDL_RenderPresent(renderer.SDLRenderer);

        /** Update the surface */
        SDL_UpdateWindowSurface(renderer.SDLWindow);

        uint32_t end_tick = SDL_GetTicks();

        int wait_ticks = 16 - (end_tick - start_tick);

        if (wait_ticks < 0) {
            wait_ticks = 0;
        }



        passedTime += (end_tick - start_tick);
        numFrames++;

        if (passedTime >= 100) {
            /** printf("%d\n", numFrames); */
            numFrames = 0;
            passedTime = 0;
        }

        SDL_Delay(wait_ticks);
    }
}

bool Game::loadMedia() {
    /** Loading success flag */
    bool success = true;

    return success;
}

void Game::drawResources() {
    SDL_Color black = {0, 0, 0}; 

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, "pf", black); 

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer.SDLRenderer, surfaceMessage); 

    SDL_Rect Message_rect; 
    Message_rect.x = 200;  
    Message_rect.y = 200; 
    Message_rect.w = 200; 
    Message_rect.h = 200; 

    SDL_RenderCopy(renderer.SDLRenderer, Message, NULL, &Message_rect); 
}   