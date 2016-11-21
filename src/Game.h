/**
 * Game.h
 *
 * Victor Jiao (c) 2016
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <map>
#include <string>

#include "Entity.h"
#include "KeyHandler.h"
#include "Map.h"
#include "Renderer.h"

#ifndef _GAME_HXX_
#define _GAME_HXX_

#define K_MAP_FILE_PATH "./res/maps/test_map_1.map"

using namespace std;

/**
 * Game
 *
 * Holds information about the running of the game
 */
class Game {
public:
    Game(int width, int height) : renderer(width, height) {}

    Game() : Game(0, 0) {}

    /**
     * Starts up SDL and creates window
     */
    bool init();

    void run();
    void draw();
    void drawMenu();

    bool loadMedia();

    Renderer renderer;

private:
    KeyHandler keyHandler;
    Player player;
    Map map;
    TTF_Font* sans;

    int numFrames; 
    int passedTime;

    Rect startGame;

    std::map<string, int> inventory;

    void update();

    void drawResources();
    void drawText(string text, SDL_Color color, TTF_Font* font, int x, int y, int* w, int* h);
};

#endif
