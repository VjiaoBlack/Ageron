/**
 * Entity.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Entity.h"

void Color::setRGBA(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}



void Rect::draw(Renderer& r) {
    SDL_Rect fillRect = {(int) r.displayX(round(x)), (int) round(y),
                         (int) round(w), (int) round(h)};

    SDL_RenderDrawRect(r.SDLRenderer, &fillRect);
}

void Rect::offsetXY(float x, float y) {
    this->x += x;
    this->y += y;
}

void Rect::setXY(float x, float y) {
    this->x = x;
    this->y = y;
}

bool Rect::contains(int x, int y) {
    return (x >= this->x && x <= (this->x + w) &&
            y >= this->y && y <= (this->y + h));
}

void Entity::draw(Renderer& r) {
    SDL_SetRenderDrawColor(r.SDLRenderer, color.get8R(),
                                          color.get8G(),
                                          color.get8B(),
                                          color.get8A());
    geometry.draw(r);
}

void Entity::update(KeyHandler& keyHandler) {
    /** maximum down y velocity */
    if (yVel <= 10.0f) {
        yVel += 0.5f;
    }

    /** smooth sliding (to stop) */
    if (xVel < 0) {
        if (xVel < -0.3f) {
            xVel += 0.3f;
        } else {
            xVel = 0;
        }
    } else if (xVel > 0) {
        if (xVel > 0.3f) {
            xVel -= 0.3f;
        } else {
            xVel = 0;
        }
    }

    /** TODO: Add acceleration metric to start */
    if (keyHandler.isKeyDown(SDLK_LEFT)) {
        xVel = -5.0f;
    }

    if (keyHandler.isKeyDown(SDLK_RIGHT)) {
        xVel = 5.0f;
    }

    /** moves the geometry */
    geometry.offsetXY(xVel, yVel);

    if (geometry.getY() > Map::kGroundYPos - geometry.getH()) {
        geometry.setY(Map::kGroundYPos - geometry.getH());
    }
}

void Entity::setXY(float x, float y) {
    geometry.setXY(x, y);
}

void Entity::setXYVel(float xv, float yv) {
    xVel = xv;
    yVel = yv;
}
