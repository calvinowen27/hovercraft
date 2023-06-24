#include "../include/game/UIManager.h"
#include "../include/game/Player.h"

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
    _pFPScounter = new TextElement("FPS: ", "arial.ttf", _white, Vector2::zero, Vector2(0.1, 0.025));
    _pUPScounter = new TextElement("UPS: ", "arial.ttf", _white, Vector2(0, 0.026), Vector2(0.1, 0.025));
    _pPosDisplay = new TextElement("Position: ", "arial.ttf", _white, Vector2(0.7, 0), Vector2(0.3, 0.025));
    _pVelDisplay = new TextElement("Velocity: ", "arial.ttf", _white, Vector2(0.7, 0.026), Vector2(0.3, 0.025));
    _pAccDisplay = new TextElement("Acceleration: ", "arial.ttf", _white, Vector2(0.7, 0.052), Vector2(0.3, 0.025));
}

void UIManager::update()
{
    _pFPScounter->setText("FPS: " + std::to_string(_pGame->getFPS()));
    _pUPScounter->setText("UPS: " + std::to_string(_pGame->getUPS()));
    _pPosDisplay->setText("Position: " + _pGame->pPlayer->getPos().to_string());
    _pVelDisplay->setText("Velocity: " + _pGame->pPlayer->getVelocity().to_string());
    _pAccDisplay->setText("Acceleration: " + _pGame->pPlayer->getAcceleration().to_string());

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