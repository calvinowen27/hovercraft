#include "../include/game/TextElement.h"

TextElement::TextElement(std::string text, std::string fontName, SDL_Color color, Vector2 relativePos, Vector2 relativeDims) : UIElement("ui_text_back.png", relativePos, relativeDims)
{
    _pxTextWidth = _pxDims.x;
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

    SDL_RenderCopy(pRenderer, _texture, NULL, &_textRect);

    SDL_SetRenderDrawColor(pRenderer, 50, 50, 50, 142);
    SDL_RenderDrawRect(pRenderer, &_drawRect);
}

void TextElement::update()
{
    UIElement::update();

    _pxTextWidth = ((float)_textDims.x/(float)_textDims.y)*_relativeDims.y*0.9*_pGame->winWidth;
    _textRect = _drawRect;
    if(_pxTextWidth > _drawRect.w) 
    {
        _pxTextWidth = _drawRect.w;
        _textRect.h = ((float)_textDims.x/(float)_textDims.y)*_relativeDims.x*_pGame->winHeight;
    }

    _textRect.w = _pxTextWidth;
}

void TextElement::setText(std::string newText)
{
    // measure dims
    TTF_SizeUTF8(_pFont, newText.c_str(), &_textDims.x, &_textDims.y);

    _pxTextWidth = ((float)_textDims.x/(float)_textDims.y)*_relativeDims.y*0.9*_pGame->winWidth;
    _textRect = _drawRect;
    if(_pxTextWidth > _drawRect.w) 
    {
        _pxTextWidth = _drawRect.w;
        _textRect.h = ((float)_textDims.x/(float)_textDims.y)*_relativeDims.x*_pGame->winHeight;
    }

    _textRect.w = _pxTextWidth;

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