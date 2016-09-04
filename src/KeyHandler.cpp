/*
 *  KeyHandler.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "KeyHandler.h"

bool KeyHandler::isKeyDown(int keyCode) {
    return m_keysDown.count(keyCode) == 1;
}

void KeyHandler::pressKey(int keyCode) {
    m_keysDown.insert(keyCode);
}

void KeyHandler::liftKey(int keyCode) {
    m_keysDown.erase(keyCode);
}
