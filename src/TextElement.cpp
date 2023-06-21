#include "../include/game/TextElement.h"

TextElement::TextElement(std::string text, std::string fontName, SDL_Color color, Vector2 relativePos, Vector2 relativeDims) : UIElement("blueblock.png", relativePos, relativeDims)
{
    _color = color;
    setFont(fontName);
    setText(text);
}

TextElement::~TextElement()
{
    SDL_DestroyTexture(_texture);
    SDL_FreeSurface(_surface);
}

void TextElement::draw(SDL_Renderer *pRenderer)
{
    UIElement::draw(pRenderer);

    SDL_RenderCopy(pRenderer, _texture, NULL, &_drawRect);
}

void TextElement::update()
{

}

void TextElement::setText(std::string newText)
{
    _text = newText;

    if(_texture != nullptr) SDL_DestroyTexture(_texture);

    _surface = TTF_RenderText_Solid(_pFont, _text.c_str(), _color);
    _texture = SDL_CreateTextureFromSurface(_pGame->pRenderer, _surface);
    SDL_FreeSurface(_surface);
}

std::string TextElement::getText()
{
    return _text;
}

void TextElement::setFont(std::string fontName)
{
    _pFont = _pContentManager->getFont(fontName);
}