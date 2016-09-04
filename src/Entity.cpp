/*
 *  Entity.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "Entity.h"

void Color::setRGBA(float r, float g, float b, float a) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

void Rect::draw(Renderer& r) {
    // round the width and height or calculate with m_x and m_y round offs?
    SDL_Rect fillRect = {(int) round(m_x), (int) round(m_y),
                         (int) round(m_w), (int) round(m_h)};

    // TODO Make sure you're not drawing an invisible color!

    SDL_RenderDrawRect(r.m_SDLRenderer, &fillRect);
}

void Rect::offsetXY(float x, float y) {
    m_x += x;
    m_y += y;
}

void Rect::setXY(float x, float y) {
    m_x = x;
    m_y = y;
}

void Entity::draw(Renderer& r) {
    SDL_SetRenderDrawColor(r.m_SDLRenderer, m_color.get8R(),
                                            m_color.get8G(),
                                            m_color.get8B(),
                                            m_color.get8A());

    m_geometry.draw(r);
}

void Entity::update(KeyHandler& keyHandler) {
    if (m_yVel <= 10.0f) {
        m_yVel += 0.5f;
    }

    if (keyHandler.isKeyDown(SDLK_UP)) {
        m_yVel = -7.0f;
    }

    if (m_xVel < 0) {
        if (m_xVel < -0.3f) {
            m_xVel += 0.3f;
        } else {
            m_xVel = 0;
        }
    } else if (m_xVel > 0) {
        if (m_xVel > 0.3f) {
            m_xVel -= 0.3f;
        } else {
            m_xVel = 0;
        }
    }

    if (keyHandler.isKeyDown(SDLK_LEFT)) {
        m_xVel = -3.0f;
    }

    if (keyHandler.isKeyDown(SDLK_RIGHT)) {
        m_xVel = 3.0f;
    }

    m_geometry.offsetXY(m_xVel, m_yVel);

    if (m_geometry.getY() > 760) {
        m_geometry.setY(760.0f);
    }
}

void Entity::setXY(float x, float y) {
    m_geometry.setXY(x, y);
}

void Entity::setXYVel(float xv, float yv) {
    m_xVel = xv;
    m_yVel = yv;
}
