#include "../include/game/UIManager.h"

UIManager* UIManager::_pInstance = nullptr;

UIManager::UIManager()
{
    _pGame = Game::getInstance();
}

UIManager* UIManager::getInstance()
{
    if(_pInstance == nullptr)
    {
        _pInstance = new UIManager();
    }

    return _pInstance;
}

void UIManager::init()
{
    // std::cout << "initializing ui" << std::endl;
    _pFPScounter = new TextElement("FPS: ", "arial.ttf", _white, Vector2::zero, Vector2(0.1, 0.025));
    _pUPScounter = new TextElement("UPS: ", "arial.ttf", _white, Vector2(0, 0.026), Vector2(0.1, 0.025));
}

void UIManager::update()
{
    _pFPScounter->setText("FPS: " + std::to_string(_pGame->getFPS()));
    _pUPScounter->setText("UPS: " + std::to_string(_pGame->getUPS()));
}

void UIManager::draw(SDL_Renderer *pRenderer)
{
    // std::cout << "drawing ui" << std::endl;
    // el.draw();
    for(UIElement *el : _uiElements)
    {
        // std::cout << "drawing element" << std::endl;
        el->update();
        el->draw(pRenderer);
    }
}

void UIManager::addElement(UIElement *pEl)
{
    _uiElements.push_back(pEl);
    // std::cout << "Adding element" << std::endl;
}