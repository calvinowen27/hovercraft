#include "../include/game/UIElement.h"
#include "../include/game/UIManager.h"

UIElement::UIElement(std::string textureName, Vector2 relativePos, Vector2 relativeDims)
{
    _pUIManager = UIManager::getInstance();
    _pGame = Game::getInstance();
    _pContentManager = _pGame->pContentManager;

    _pTexture = _pContentManager->getTexture(textureName);

    _relativePos = relativePos;
    _relativeDims = relativeDims;
    _pxPos = (Vector2Int)(_relativePos * Vector2(_pGame->winWidth, _pGame->winHeight));
    _pxDims = (Vector2Int)(_relativeDims * Vector2(_pGame->winWidth, _pGame->winHeight));

    _drawRect = SDL_Rect{_pxPos.x, _pxPos.y, _pxDims.x, _pxDims.y};

    // _pGame->uiElements.push_back(this);
    _pUIManager->addElement(this);
    // std::cout << (_pUIManager == _pGame->pUIManager) << std::endl;
}

void UIElement::update()
{

}

void UIElement::draw(SDL_Renderer *pRenderer)
{
    SDL_RenderCopy(pRenderer, _pTexture, NULL, &_drawRect);
}
