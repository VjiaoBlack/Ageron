/*
 *  KeyHandler.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "KeyHandler.h"

bool KeyHandler::isKeyDown(int key_code) {
    return fKeysDown.count(key_code) == 1;
}

void KeyHandler::pressKey(int key_code) {
    fKeysDown.insert(key_code);
}

void KeyHandler::liftKey(int key_code) {
    fKeysDown.erase(key_code);
}
