/*
 *  KeyHandler.cpp
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


bool KeyHandler::isButtonDown(int buttonCode) {
	return m_buttonsDown.count(buttonCode) == 1;
}

void KeyHandler::pressButton(int buttonCode) {	
	m_buttonsDown.insert(buttonCode);
}

void KeyHandler::liftButton(int buttonCode) {
	m_buttonsDown.erase(buttonCode);
}
