#include "../include/game/KeyboardHandler.h"

KeyboardHandler::KeyboardHandler()
{
    keyboardState = SDL_GetKeyboardState(NULL);
}

bool KeyboardHandler::isPressed(SDL_Scancode scancode)
{
    return keyboardState[scancode];
}

bool KeyboardHandler::isReleased(SDL_Scancode scancode)
{
    return !keyboardState[scancode];
}