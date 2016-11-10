/*
 *  Game.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
// #include <SDL2/SDL_Image.h>

#include "Renderer.h"
#include "KeyHandler.h"
#include "Entity.h"
#include "Map.h"

#ifndef _GAME_HXX_
#define _GAME_HXX_

#define K_MAP_FILE_PATH "./res/maps/test_map_1.map"

class Game {
public:
    Game(int width, int height) : renderer(width, height) {}

    Game() : Game(0, 0) {}

    /* Starts up SDL and creates window
     */
    bool init();

    void run();

    bool loadMedia();

    Renderer renderer;

private:
    KeyHandler keyHandler;
    Entity player;
    Map map;

    void update();

};

#endif
