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

    bool isKeyDown(int key_code);

    void pressKey(int key_code);

    void liftKey(int key_code);

private:
    std::unordered_set<int> fKeysDown;

};

#endif
