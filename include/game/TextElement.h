#ifndef TEXT_ELEMENT_INCLUDE
#define TEXT_ELEMENT_INCLUDE

#include "UIElement.h"
#include "../SDL2/SDL_ttf.h"

class TextElement : public UIElement
{
    private:
        std::string _text;
        TTF_Font *_pFont;

        SDL_Surface *_surface = nullptr;
        SDL_Texture *_texture = nullptr;
        SDL_Color _color;

    public:
        TextElement(std::string text, std::string fontName, SDL_Color color, Vector2 relativePos, Vector2 relativeDims);
        ~TextElement();
        void draw(SDL_Renderer *pRenderer) override;
        void update() override;
        void setText(std::string newText);
        std::string getText();
        void setFont(std::string fontName);
};

#endif