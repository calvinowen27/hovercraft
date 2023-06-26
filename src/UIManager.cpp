#include "../include/game/UIManager.h"
#include "../include/game/Player.h"
#include "cmath"

UIManager* UIManager::_pInstance = nullptr;

UIManager::UIManager()
{
    _pGame = Game::getInstance();
    // _pPlayer = _pGame->pPlayer;
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
    _pFPScounter = new TextElement("FPS: ", "arial.ttf", WHITE, Vector2::zero, Vector2(0.1, 0.025));
    _pUPScounter = new TextElement("UPS: ", "arial.ttf", WHITE, Vector2(0, 0.026), Vector2(0.1, 0.025));
    _pPosDisplay = new TextElement("Position: ", "arial.ttf", WHITE, Vector2(0.7, 0), Vector2(0.3, 0.025));
    _pVelDisplay = new TextElement("Velocity: ", "arial.ttf", WHITE, Vector2(0.7, 0.026), Vector2(0.3, 0.025));
    _pAccDisplay = new TextElement("Acceleration: ", "arial.ttf", WHITE, Vector2(0.7, 0.052), Vector2(0.3, 0.025));
}

void UIManager::update()
{
    _pFPScounter->setText("FPS: " + std::to_string(_pGame->getFPS()));
    _pUPScounter->setText("UPS: " + std::to_string(_pGame->getUPS()));
    _pPosDisplay->setText("Position: " + _pGame->pPlayer->getPos().round(3).to_string());
    _pVelDisplay->setText("Velocity: " + _pGame->pPlayer->getVelocity().round(3).to_string());
    _pAccDisplay->setText("Acceleration: " + _pGame->pPlayer->getAcceleration().round(3).to_string());
    
    // std::cout << _pGame->pPlayer->getAcceleration() << std::endl;

    // el.update()
    for(UIElement *el : _uiElements)
    {
        el->update();
    }
}

void UIManager::draw(SDL_Renderer *pRenderer)
{
    // el.draw();
    for(UIElement *el : _uiElements)
    {
        el->draw(pRenderer);
    }
}

void UIManager::addElement(UIElement *pEl)
{
    _uiElements.push_back(pEl);
}