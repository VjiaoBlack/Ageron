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
        : m_SDLWindow(NULL)
        , m_SDLRenderer(NULL)
        , m_width(width)
        , m_height(height)
        , m_xOffset(0) {}

    Renderer() : Renderer(0, 0) {}

    int m_width;
    int m_height;

    double m_xOffset;

    SDL_Renderer* m_SDLRenderer;
    SDL_Window* m_SDLWindow;

    /* Frees media and shuts down SDL
     */
    void close();
};

#endif
