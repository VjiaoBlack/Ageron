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

    player = Player(K_TILE_SIZE, K_TILE_SIZE * 2, Color(1.0f, 0.0f, 0.0f, 1.0f));
    player.setXY(400 * K_SCREEN_SCALE,
                 400 * K_SCREEN_SCALE);

    map.load(renderer, K_MAP_FILE_PATH);

    /* start game button */
    startGame = Rect(200 * K_SCREEN_SCALE, 400 * K_SCREEN_SCALE,
                     300 * K_SCREEN_SCALE, 100 * K_SCREEN_SCALE);

    return success;
}

void Game::update() {
    player.update(keyHandler);

    /** TODO: add an acceleration to the renderer */
    if (renderer.xOffset + player.getX() < 300 * K_SCREEN_SCALE) {
        renderer.xOffset = 300 * K_SCREEN_SCALE - player.getX();
    } else if (renderer.xOffset + player.getX() > K_WINDOW_WIDTH - 300 * K_SCREEN_SCALE - player.getW()) {
        renderer.xOffset = K_WINDOW_WIDTH - 300 * K_SCREEN_SCALE - player.getW() - player.getX() ;
    }

    /*
        If player (TODO: NPCs) is trying to gather resources, then
        run appropriate resource-gathering formula.
     */
    if (keyHandler.isKeyDown(SDLK_DOWN)) {
        /** check what scenery object the player intersects */
        auto it = this->map.scenery.begin();

        for (; it != this->map.scenery.end(); it++) {
            /** if it intersects, break */

            /** TODO: make the 3200 map-sensitive */
            int maxXp = this->player.getX() + 32;
            while(maxXp >= 3200 * K_SCREEN_SCALE) {
                maxXp -= 3200 * K_SCREEN_SCALE;
            }
            while(maxXp < 0) {
                maxXp += 3200 * K_SCREEN_SCALE;
            }

            int minXp = this->player.getX();
            while(minXp >= 3200 * K_SCREEN_SCALE) {
                minXp -= 3200 * K_SCREEN_SCALE;
            }
            while(minXp < 0) {
                minXp += 3200 * K_SCREEN_SCALE;
            }

            /** TODO: cover cases apart from tree */
            /** note that the +- 64 is for tree */
            int maxXs = (*it)->xpos + (*it)->type->width * 32 - 64;
            int minXs = (*it)->xpos + 64;

            /** TODO: what to do if multiple overlap */
            if ((minXp >= minXs && minXp <= maxXs) ||
                (maxXp >= minXs && maxXp <= maxXs)) {

                /** TODO: add SDL_ONE_SECOND magic number */
                if ((*it)->type->name == "tree") {
                    uint32_t curTick = SDL_GetTicks();
                    if (curTick - player.lastAction > 1000) {
                        player.lastAction = curTick;
                        inventory["wood"]++;
                    }
                }
                break;
            }
        }
    }
}

void Game::draw() {
    /** Clear screen */
    SDL_SetRenderDrawColor(renderer.SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer.SDLRenderer);

    /** render map */
    map.draw(renderer);

    /** Render red filled quad */
    player.draw(renderer);

    SDL_SetRenderDrawColor(renderer.SDLRenderer, 0, 0, 0, 0xFF);

    drawResources();

    /** Update screen */
    SDL_RenderPresent(renderer.SDLRenderer);

    /** Update the surface */
    SDL_UpdateWindowSurface(renderer.SDLWindow);
}

void Game::drawMenu() {
    /** Clear screen */
    SDL_SetRenderDrawColor(renderer.SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer.SDLRenderer);

    SDL_Color black = {0, 0, 0};

    SDL_Rect titleRect = {100 * K_SCREEN_SCALE, 100 * K_SCREEN_SCALE, 0, 0};
    TTF_Font* titleFont = TTF_OpenFont("res/UbuntuMono-R.ttf", 175);
    TTF_SetFontStyle(titleFont, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
    drawText("Ageron", black, titleFont, titleRect);
    TTF_CloseFont(titleFont);
    
    TTF_Font* itemFont = TTF_OpenFont("res/UbuntuMono-R.ttf", 75);
    SDL_Rect fillRect = startGame.getSDLRect();
    drawText("play", black, itemFont, fillRect);
    
    /** Draw outline **/
    SDL_SetRenderDrawColor(renderer.SDLRenderer,
                           0xFF, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawRect(renderer.SDLRenderer, &fillRect);

    TTF_CloseFont(itemFont);

    /** Update screen */
    SDL_RenderPresent(renderer.SDLRenderer);

    /** Update the surface */
    SDL_UpdateWindowSurface(renderer.SDLWindow);
}

void Game::run() {
    /* Main loop flags */
    bool quit = false;
    bool menu = true;

    /* Event handler */
    SDL_Event e;

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

        drawMenu();

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

        draw();

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

void Game::drawText(string text, SDL_Color color, TTF_Font* font, SDL_Rect &layout) {
    const char* ctext = text.c_str();
    SDL_Surface* surface = TTF_RenderText_Solid(font, ctext, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.SDLRenderer, surface);
    TTF_SizeText(font, ctext, &layout.w, &layout.h);
    SDL_RenderCopy(renderer.SDLRenderer, texture, NULL, &layout);
}

void Game::drawResources() {
    SDL_Color white = {255, 255, 255};
    const int ybuf = (K_SCREEN_SCALE * K_TILE_SIZE / 2);
    const int startY = K_MAP_HEIGHT + K_TILE_SIZE + ybuf;
    SDL_Rect layout = {10 * K_SCREEN_SCALE, startY, 0, 0};
    for (const auto &kv : inventory) {
        string disp = kv.first + " " + to_string(kv.second);
        int old_w = layout.w;
        drawText(disp, white, sans, layout);
        layout.w = max(layout.w, old_w);
        if (layout.y > K_WINDOW_HEIGHT - (2 * layout.h) - ybuf) {
            layout.y = startY;
            layout.x += layout.w + (K_SCREEN_SCALE * 20);
        }
        else layout.y += layout.h;
    }
}
