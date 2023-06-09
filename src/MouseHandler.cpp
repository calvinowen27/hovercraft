#include "../include/game/MouseHandler.h"
#include "../include/game/Game.h"

MouseHandler::MouseHandler()
{
    // _pGame = Game::getInstance();
    // _prevMousePos = Vector2::zero;
    // _pxPrevMousePos = Vector2Int(0, 0);
    // _mousePos = Vector2::zero;
    // _pxMousePos = Vector2Int(0, 0);
}

void MouseHandler::update()
{
    _prevButtonState = _currButtonState;
    _pxPrevMousePos = _pxMousePos;
    _currButtonState = SDL_GetMouseState(&_pxMousePos.x, &_pxMousePos.y);

    _prevMousePos = _mousePos;
    // _mousePos = _pGame->pixelToWorld(_pxMousePos);
}

bool MouseHandler::isButtonPressed(int button)
{
    return _currButtonState & SDL_BUTTON(button);
}

bool MouseHandler::wasButtonPressed(int button)
{
    return _prevButtonState & SDL_BUTTON(button);
}

bool MouseHandler::isButtonJustPressed(int button)
{
    return isButtonPressed(button) && !wasButtonPressed(button);
}

bool MouseHandler::mouseWithinRect(SDL_Rect rect)
{
    return !(_pxMousePos.x < rect.x || _pxMousePos.x > rect.x + rect.w || _pxMousePos.y < rect.y || _pxMousePos.y > rect.y + rect.h);
}