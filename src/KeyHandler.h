/*
 *  KeyHandler.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <unordered_set>

#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

class KeyHandler {
public:
    KeyHandler()
    	: m_mouseX(0)
    	, m_mouseY(0)
    	, m_mouseXVel(0)
    	, m_mouseYVel(0) {};

    bool isKeyDown(int keyCode);

    void pressKey(int keyCode);

    void liftKey(int keyCode);

    bool isButtonDown(int buttonCode);

    void pressButton(int buttonCode);

    void liftButton(int buttonCode);

	int m_mouseX;
	int m_mouseY;

	int m_mouseXVel;
	int m_mouseYVel;

private:
    std::unordered_set<int> m_keysDown;
    std::unordered_set<char> m_buttonsDown;
};

#endif
