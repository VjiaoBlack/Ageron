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

void Player::draw(Renderer& r) {
    SDL_SetRenderDrawColor(r.SDLRenderer, color.get8R(),
                                          color.get8G(),
                                          color.get8B(),
                                          color.get8A());
    geometry.draw(r);
}

void Player::update(KeyHandler& keyHandler) {
    /** maximum down y velocity */
    if (yVel <= 10.0f) {
        yVel += 0.5f;
    }

    /** Acceleration */
    if (keyHandler.isKeyDown(SDLK_LEFT)) {
        if (xVel >= -4.0f * K_SCREEN_SCALE) {
            xVel -= 0.4f * K_SCREEN_SCALE;
        } 
        /** slow down faster if trying to switch directoin */
        if (xVel >= 0.0f) {
            xVel -= 0.4f * K_SCREEN_SCALE;
        }
    } else if (keyHandler.isKeyDown(SDLK_RIGHT)) {
        if (xVel <= 4.0f * K_SCREEN_SCALE) {
            xVel += 0.4f * K_SCREEN_SCALE;
        }
        if (xVel <= 0.0f) {
            xVel += 0.4f * K_SCREEN_SCALE;
        }
    } else {
        if (xVel > 0.4f * K_SCREEN_SCALE) {
            xVel -= 0.4f * K_SCREEN_SCALE;
        } else if (xVel < -0.4f * K_SCREEN_SCALE) {
            xVel += 0.4f * K_SCREEN_SCALE;
        } else {
            xVel = 0.0f;
        }
    }

    /** moves the geometry */
    geometry.offsetXY(xVel, yVel);

    if (geometry.getY() > K_MAP_HEIGHT - geometry.getH()) {
        geometry.setY(K_MAP_HEIGHT - geometry.getH());
    }
}

void Player::setXY(float x, float y) {
    geometry.setXY(x, y);
}

void Player::setXYVel(float xv, float yv) {
    xVel = xv;
    yVel = yv;
}
