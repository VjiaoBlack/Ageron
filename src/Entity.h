/*
 *  Entity.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <SDL2/SDL.h>
// #include <SDL2/SDL_Image.h>

#include <math.h>

#include "Renderer.h"
#include "KeyHandler.h"
#include "Map.h"


#ifndef _ENTITY_H_
#define _ENTITY_H_

class Color {
public:
    Color(float r, float g, float b, float a)
        : m_r(r), m_g(g), m_b(b), m_a(a) {}

    Color() : Color(0, 0, 0, 1.0f) {}

    void setRGBA(float r, float g, float b, float a);

    float getR() { return m_r; }
    float getG() { return m_g; }
    float getB() { return m_b; }
    float getA() { return m_a; }

    int get8R() { return (int) (255.0f * m_r); }
    int get8G() { return (int) (255.0f * m_g); }
    int get8B() { return (int) (255.0f * m_b); }
    int get8A() { return (int) (255.0f * m_a); }

    Color& operator=(const Color& other) {
        if (this != &other) {
            this->m_r = other.m_r;
            this->m_g = other.m_g;
            this->m_b = other.m_b;
            this->m_a = other.m_a;
        }
        return *this;
    }

private:
    float m_r;
    float m_g;
    float m_b;
    float m_a;
};

class Rect {
public:
    Rect(float x, float y, float w, float h)
        : m_x(x), m_y(y), m_w(w), m_h(h) {}

    Rect(float w, float h) : Rect(0, 0, w, h) {}

    Rect() : Rect(0, 0, 0, 1.0f) {}

    void draw(Renderer& r);

    SDL_Rect getSDLRect() {
        // TODO: is this how round works?
        return (SDL_Rect) {(int) round(m_x),
                           (int) round(m_y),
                           (int) round(m_w),
                           (int) round(m_h)};
    }

    void offsetXY(float x, float y);
    void setXY(float x, float y);
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    float getX() { return m_x; }
    float getY() { return m_y; }
    float getW() { return m_w; }
    float getH() { return m_h; }

    bool contains(int x, int y);
    bool contains(pair<int, int> coord) {
        return contains(coord.first, coord.second);
    }

private:
    float m_x;
    float m_y;
    float m_w;
    float m_h;

};

class Entity {
public:
    Entity(int w, int h, Color c)
        : m_geometry(w, h)
        , m_xVel(0), m_yVel(0)
        , m_color(c) {}

    Entity(int w, int h) : Entity(w, h, Color(0, 0, 0, 0)) {}

    Entity() : Entity(0, 0, Color(0, 0, 0, 1.0f)) {}

    void draw(Renderer& r);

    void update(KeyHandler& keyHandler);

    void setX(float x) { m_geometry.setX(x); }
    float getX() { return m_geometry.getX(); }
    void setY(float y) { m_geometry.setY(y); }
    float getY() { return m_geometry.getY(); }

    void setXY(float x, float y);

    void setXYVel(float xv, float yv);

private:
    Rect m_geometry;
    Color m_color;

    float m_xVel;
    float m_yVel;
};

#endif
