#include "../include/game/KeyboardHandler.h"
#include <iostream>

KeyboardHandler::KeyboardHandler()
{
    _keyboardState = SDL_GetKeyboardState(NULL);

    _keybinds = {
        { ACTION_MOVE_UP, SDL_SCANCODE_W },
        { ACTION_MOVE_DOWN, SDL_SCANCODE_S },
        { ACTION_MOVE_RIGHT, SDL_SCANCODE_D },
        { ACTION_MOVE_LEFT, SDL_SCANCODE_A },
        { ACTION_BOOST, SDL_SCANCODE_LSHIFT },
        { ACTION_RESET, SDL_SCANCODE_R },
        { ACTION_ZOOM_IN, SDL_SCANCODE_EQUALS },
        { ACTION_ZOOM_OUT, SDL_SCANCODE_MINUS },
        { ACTION_CLOSE, SDL_SCANCODE_ESCAPE }
    };
}

void KeyboardHandler::processInputs()
{
    SDL_Event event;
    while(_inputEvents.size())
    {
        event = _inputEvents.front();

        _inputState[event.key.keysym.scancode] = (event.type == SDL_KEYDOWN);

        _inputEvents.pop();
    }
}

bool KeyboardHandler::isPressed(SDL_Scancode scancode)
{
    return _keyboardState[scancode];
}

bool KeyboardHandler::isReleased(SDL_Scancode scancode)
{
    return !_keyboardState[scancode];
}

void KeyboardHandler::pushEvent(SDL_Event event)
{
    _inputEvents.push(event);
}

bool KeyboardHandler::getInputState(int key)
{
    return _inputState[_keybinds[key]];
}