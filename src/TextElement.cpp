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

    // std::cout << "drawing text" << std::endl;
    // std::cout << _textRect << std::endl;
    // std::cout << _pxPos << " " << _pxDims << std::endl << std::endl;
}

void TextElement::update()
{

}

void TextElement::setText(std::string newText)
{
    // measure dims
    // keep width, height = (dims.x / dims.y) * desired height
    int w, h;

    TTF_SizeUTF8(_pFont, newText.c_str(), &w, &h);

    _pxTextWidth = ((float)w/(float)h)*_relativeDims.y*0.9*_pGame->winWidth;
    // _drawRect.w = _pxDims.x;
    // _drawRect.h = _pxDims.y;
    // std::cout << _pxDims << std::endl;
    _textRect = _drawRect;
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