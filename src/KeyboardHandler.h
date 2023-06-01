#include "../include/SDL2/SDL.h"

class KeyboardHandler
{
    private:
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    public:
        void handleKeyboardEvent(SDL_Event event);

        bool isPressed(SDL_Scancode scancode);

        bool isReleased(SDL_Scancode scancode);
};