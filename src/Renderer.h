/**
 * Renderer.h
 *
 * Victor Jiao (c) 2016
 */

#include <SDL2/SDL.h>

class Renderer;

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Map.h"

#define K_WINDOW_WIDTH 1280
#define K_WINDOW_HEIGHT 780

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

};

#endif
