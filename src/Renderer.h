/**
 * Renderer.h
 *
 * Victor Jiao (c) 2016
 */

#include <SDL.h>
#include <SDL_ttf.h>

class Renderer;

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Map.h"

#define K_SCREEN_SCALE 1

#define K_WINDOW_WIDTH (1280 * K_SCREEN_SCALE)
#define K_WINDOW_HEIGHT (780 * K_SCREEN_SCALE)

#define K_TILE_SIZE (32 * K_SCREEN_SCALE)

class Renderer {
public:
    Renderer(int width, int height)
        : SDLWindow(NULL)
        , SDLRenderer(NULL)
        , width(width)
        , height(height)
        , xOffset(0) {}

    Renderer() : Renderer(0, 0) {}

    int width;
    int height;

    double xOffset;

    SDL_Renderer* SDLRenderer;
    SDL_Window* SDLWindow;

    /**
     * Given an x_position, offset it so that it's the highest
     * version of x' = x + n * map_width that is <= the x pos
     * of the rightmost pixel displayed on the screen.
     */
    int displayX(int x);

    /**
     * Frees media and shuts down SDL
     */
    void close();

    SDL_Texture* loadSurface(std::string path);

    /**
     * Draws text to the screen, automatically sizing it.
     *
     * Parameters:
     * - text: Text to draw to the screen.
     * - color: Color to draw the text in.
     * - font: Font to use.
     * - layout: The X and Y are used as the origin of the text, the width and height are filled
     *           with the width and height of the text in the specified font.
     */
    void drawText(string text, SDL_Color color, TTF_Font* font, SDL_Rect &layout);
};

#endif
