#ifndef BUTTON_INCLUDE
#define BUTTON_INCLUDE

#include "TextElement.h"

class MouseHandler;

class Button : public TextElement
{
    private:
        MouseHandler *_pMouseHandler;
        void (*_actionFunc)();

    public:
        Button(std::string textureName, std::string buttonText, std::string fontName, SDL_Color textColor, Vector2 relativePos, Vector2 relativeDims, void (*actionFunc)());
        void update() override;
};

#endif