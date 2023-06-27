#ifndef KEYBOARD_INCLUDE
#define KEYBOARD_INCLUDE

#include "../SDL2/SDL.h"
#include <queue>
#include <map>

enum ACTIONS {
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_RIGHT,
    ACTION_MOVE_LEFT,
    ACTION_BOOST,
    ACTION_RESET,
    ACTION_ZOOM_IN,
    ACTION_ZOOM_OUT,
    ACTION_CLOSE
};

class KeyboardHandler
{
    private:
        const Uint8 *_keyboardState;
        std::queue<SDL_Event> _inputEvents;
        std::map<int, SDL_Scancode> _keybinds;
        std::map<SDL_Scancode, bool> _inputState;

    public:
        KeyboardHandler();
        void processInputs();
        bool isPressed(SDL_Scancode scancode);
        bool isReleased(SDL_Scancode scancode);
        void pushEvent(SDL_Event event);
        bool getInputState(int key);
};

#endif