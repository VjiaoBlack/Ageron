/**
 * KeyHandler.h
 *
 * Victor Jiao (c) 2016
 */

#include <unordered_set>

#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

/**
 * KeyHandler
 *
 * This handles all interactions between the SDL Keyboard, Mouse, and the user.
 */
class KeyHandler {
public:
    KeyHandler()
    	: mouseX(0)
    	, mouseY(0)
    	, mouseXVel(0)
    	, mouseYVel(0) {};

    bool isKeyDown(int keyCode);

    void pressKey(int keyCode);

    void liftKey(int keyCode);

    bool isButtonDown(int buttonCode);

    void pressButton(int buttonCode);

    void liftButton(int buttonCode);

	int mouseX;
	int mouseY;

	int mouseXVel;
	int mouseYVel;

private:
    std::unordered_set<int> keysDown;
    std::unordered_set<char> buttonsDown;
};

#endif
