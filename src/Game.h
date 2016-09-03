/*
 *  Game.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include "Renderer.h"
#include "KeyHandler.h"

#ifndef _GAME_HXX_
#define _GAME_HXX_

class Game {
public:
    Game()
        : fRenderer(0, 0)
        , fPlayerX(0)
        , fPlayerY(0) {}

    Game(int width, int height)
        : fRenderer(width, height)
        , fPlayerX(0)
        , fPlayerY(0) {}

    /* Starts up SDL and creates window
     */
    bool init();

    void run();

    bool loadMedia();

    Renderer fRenderer;

private:
    KeyHandler fKeyHandler;

    void update();

    float fPlayerX;
    float fPlayerY;

    float fPlayerYVel;
    float fPlayerXVel;
};

#endif
