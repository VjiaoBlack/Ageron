/*
 *  Renderer.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#ifndef _RENDERER_H_
#define _RENDERER_H_

class Renderer {
public:
    Renderer()
        : fSDLWindow(NULL)
        , fSDLRenderer(NULL)
        , fWidth(0)
        , fHeight(0) {}

    Renderer(int width, int height)
        : fSDLWindow(NULL)
        , fSDLRenderer(NULL)
        , fWidth(width)
        , fHeight(height)  {}

    int fWidth;
    int fHeight;

    SDL_Renderer* fSDLRenderer;
    SDL_Window* fSDLWindow;

    /* Frees media and shuts down SDL
     */
    void close();
};

#endif
