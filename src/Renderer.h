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
        : m_SDLWindow(NULL)
        , m_SDLRenderer(NULL)
        , m_width(0)
        , m_height(0) {}

    Renderer(int width, int height)
        : m_SDLWindow(NULL)
        , m_SDLRenderer(NULL)
        , m_width(width)
        , m_height(height) {}

    int m_width;
    int m_height;

    SDL_Renderer* m_SDLRenderer;
    SDL_Window* m_SDLWindow;

    /* Frees media and shuts down SDL
     */
    void close();
};

#endif
