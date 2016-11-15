/*
 *  Entity.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL2/SDL.h>

#include <math.h>

#include "KeyHandler.h"
#include "Map.h"
#include "Renderer.h"

/**
 * Color
 *
 * keeps track of (and works with) colors
 */
class Color {
public:
    Color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}

    Color() : Color(0, 0, 0, 1.0f) {}

    void setRGBA(float r, float g, float b, float a);

    float getR() { return r; }
    float getG() { return g; }
    float getB() { return b; }
    float getA() { return a; }

    int get8R() { return (int) (255.0f * r); }
    int get8G() { return (int) (255.0f * g); }
    int get8B() { return (int) (255.0f * b); }
    int get8A() { return (int) (255.0f * a); }

    Color& operator=(const Color& other) {
        if (this != &other) {
            this->r = other.r;
            this->g = other.g;
            this->b = other.b;
            this->a = other.a;
        }
        return *this;
    }

private:
    float r;
    float g;
    float b;
    float a;
};

/**
 * Rect
 *
 * A rectangle class that has basic functionalities for movement and stuff
 */
class Rect {
public:
    Rect(float x, float y, float w, float h)
        : x(x), y(y), w(w), h(h) {}

    Rect(float w, float h) : Rect(0, 0, w, h) {}

    Rect() : Rect(0, 0, 0, 1.0f) {}

    void draw(Renderer& r);

    
    SDL_Rect getSDLRect() {
        /** TODO: is this how round works? */
        return (SDL_Rect) {(int) round(x),
                           (int) round(y),
                           (int) round(w),
                           (int) round(h)};
    }

    void offsetXY(float x, float y);
    void setXY(float x, float y);
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }

    float getX() { return x; }
    float getY() { return y; }
    float getW() { return w; }
    float getH() { return h; }

    bool contains(int x, int y);
    bool contains(pair<int, int> coord) {
        return contains(coord.first, coord.second);
    }

private:
    float x;
    float y;
    float w;
    float h;

};

/**
 * Entity
 *
 * free-moving objects in the world
 */
class Entity {
public:
    Entity(int w, int h, Color c)
        : geometry(w, h)
        , xVel(0), yVel(0)
        , color(c) {}

    Entity(int w, int h) : Entity(w, h, Color(0, 0, 0, 0)) {}

    Entity() : Entity(0, 0, Color(0, 0, 0, 1.0f)) {}

    void draw(Renderer& r);

    void update(KeyHandler& keyHandler);

    void  setX(float x) { geometry.setX(x); }
    float getX()        { return geometry.getX(); }
    void  setY(float y) { geometry.setY(y); }
    float getY()        { return geometry.getY(); }

    void setXY(float x, float y);

    void setXYVel(float xv, float yv);

private:
    Rect geometry;
    Color color;

    float xVel;
    float yVel;
};

#endif
