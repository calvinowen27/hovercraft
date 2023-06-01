#include "KeyboardHandler.h"
#include <iostream>

bool KeyboardHandler::isPressed(SDL_Scancode scancode)
{
    return keyboardState[scancode];
}

bool KeyboardHandler::isReleased(SDL_Scancode scancode)
{
    return !keyboardState[scancode];
}