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
    KeyHandler() {};

    bool isKeyDown(int keyCode);

    void pressKey(int keyCode);

    void liftKey(int keyCode);

private:
    std::unordered_set<int> m_keysDown;

};

#endif
