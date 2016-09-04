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
#include "Entity.h"

#ifndef _GAME_HXX_
#define _GAME_HXX_

class Game {
public:
    Game(int width, int height) : m_renderer(width, height) {}

    Game() : Game(0, 0) {}

    /* Starts up SDL and creates window
     */
    bool init();

    void run();

    bool loadMedia();

    Renderer m_renderer;

private:
    KeyHandler m_keyHandler;

    void update();

    Entity m_player;
};

#endif
