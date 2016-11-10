/*
 *  KeyHandler.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include "KeyHandler.h"

bool KeyHandler::isKeyDown(int keyCode) {
    return keysDown.count(keyCode) == 1;
}

void KeyHandler::pressKey(int keyCode) {
    keysDown.insert(keyCode);
}

void KeyHandler::liftKey(int keyCode) {
    keysDown.erase(keyCode);
}


bool KeyHandler::isButtonDown(int buttonCode) {
	return buttonsDown.count(buttonCode) == 1;
}

void KeyHandler::pressButton(int buttonCode) {	
	buttonsDown.insert(buttonCode);
}

void KeyHandler::liftButton(int buttonCode) {
	buttonsDown.erase(buttonCode);
}
