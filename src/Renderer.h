/*
 *  Renderer.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
// #include <SDL2/SDL_Image.h>

#ifndef _RENDERER_H_
#define _RENDERER_H_

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

    /* Frees media and shuts down SDL
     */
    void close();
};

#endif
