#ifndef MOUSE_HANDLER_INCLUDE
#define MOUSE_HANDLER_INCLUDE

#include "../SDL2/SDL.h"
#include "Vector2.h"

class Game;

enum MOUSE_BUTTONS {
    MOUSE_LEFT = 1,
    MOUSE_MIDDLE = 2,
    MOUSE_RIGHT = 3
};

class MouseHandler
{
    private:
        Game *_pGame;
        Uint32 _currButtonState;
        Uint32 _prevButtonState;
        Vector2Int _pxMousePos;
        Vector2Int _pxPrevMousePos;
        Vector2 _mousePos;
        Vector2 _prevMousePos;

    public:
        MouseHandler();
        void update();
        bool isButtonPressed(int button);
        bool wasButtonPressed(int button);
        bool isButtonJustPressed(int button);
        bool mouseWithinRect(SDL_Rect rect);
        inline Vector2 getMousePos() { return _mousePos; }
        inline Vector2 getMousePrevPos() { return _prevMousePos; }
        inline Vector2Int getMousePxPos() { return _pxMousePos; }
        inline Vector2Int getMousePrevPxPos() { return _pxPrevMousePos; }
};

#endif