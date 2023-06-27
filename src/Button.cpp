#include "../include/game/Button.h"
#include "../include/game/MouseHandler.h"

Button::Button(std::string textureName, std::string buttonText, std::string fontName, SDL_Color textColor, Vector2 relativePos, Vector2 relativeDims, void (*actionFunc)()) : 
TextElement(buttonText, fontName, textColor, relativePos, relativeDims)
{
    _pMouseHandler = _pGame->pMouseHandler;
    _pTexture = _pContentManager->getTexture(textureName);
    _actionFunc = actionFunc;
}

void Button::update()
{
    TextElement::update();

    // std::cout << _pMouseHandler->mouseWithinRect(_drawRect) << " " << _pMouseHandler->isButtonPressed(MOUSE_LEFT) << std::endl;

    if(_pMouseHandler->mouseWithinRect(_drawRect) && _pMouseHandler->isButtonJustPressed(MOUSE_LEFT))
    {
        _actionFunc();
    }
}