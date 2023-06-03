#ifndef KEYBOARD_INCLUDE
#define KEYBOARD_INCLUDE

#include "../SDL2/SDL.h"

class KeyboardHandler
{
    private:
        const Uint8 *keyboardState;

    public:
        KeyboardHandler();
        void handleKeyboardEvent(SDL_Event event);
        bool isPressed(SDL_Scancode scancode);
        bool isReleased(SDL_Scancode scancode);
};

#endif