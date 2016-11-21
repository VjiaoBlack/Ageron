/**
 * Menu.h
 *
 * Victor Jiao, Will Field-Thompson (c) 2016
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <map>
#include <string>

#include "Renderer.h"
#include "Entity.h"

#ifndef _MENU_HXX_
#define _MENU_HXX_

using namespace std;

/**
 * Menu
 *
 * Draws the main menu.
 */
class Menu {
public:
    class MenuItem {
    public:
        string title;
        SDL_Rect frame;
        void draw(Renderer &renderer, SDL_Color color, TTF_Font *font, SDL_Rect layout);
        MenuItem(string text) {
            title = text;
            frame = {0, 0, 0, 0};
        };
    };
    
    Menu(SDL_Rect bounds, TTF_Font *itemFont, vector<MenuItem> contents) {
        frame = bounds;
        font = itemFont;
        items = contents;
    };

    void draw(Renderer &renderer);
    void updateMouseHover(int x, int y);
    MenuItem checkClicked(int x, int y);

    SDL_Color textColor = {255, 255, 255};
    SDL_Color highlightColor = {255, 100, 0};

private:
    SDL_Rect frame;
    TTF_Font *font;
    vector<MenuItem> items;
};

#endif
