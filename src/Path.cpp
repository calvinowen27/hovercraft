#include "../include/game/Path.h"

Path::Path(std::vector<Vector2> points)
{
    _pGame = Game::getInstance();
    _points = points;
    _pGame->paths.push_back(this);
}

void Path::draw(SDL_Renderer *pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
    Vector2Int prevPoint = _pGame->worldToPixel(_points[0]);
    Vector2Int currPoint;
    for(int i = 1; i < _points.size(); i++)
    {
        currPoint = _pGame->worldToPixel(_points[i]);
        SDL_RenderDrawLine(pRenderer, prevPoint.x+1, prevPoint.y+1, currPoint.x+1, currPoint.y+1);
        SDL_RenderDrawLine(pRenderer, prevPoint.x, prevPoint.y, currPoint.x, currPoint.y);
        SDL_RenderDrawLine(pRenderer, prevPoint.x-1, prevPoint.y-1, currPoint.x-1, currPoint.y-1);
        prevPoint = currPoint;
    }
}

void Path::addPoint(Vector2 &newPoint)
{
    _points.push_back(newPoint);
}

int Path::removePoint(Vector2 point)
{
    for(int i = 0; i < _points.size(); i++)
    {
        if(_points[i] == point)
        {
            _points.erase(_points.begin()+i);
            return 0;
        }
    }

    return 1;
}

Vector2 Path::pathSnap(Player *pPlayer, float time)
{
    Vector2 prevPoint = _points[0];
    Vector2 currPoint;
    float slope;
    Vector2 playerPos = pPlayer->getPos();
    Vector2 nextPos = playerPos + pPlayer->getVelocity() * time;
    Vector2 playerDims = pPlayer->getDims();
    float checkY;
    for(int i = 1; i < _points.size(); i++)
    {
        currPoint = _points[i];
        slope = (currPoint.y - prevPoint.y) / (currPoint.x - prevPoint.x);
        checkY = slope*(nextPos.x - prevPoint.x) + prevPoint.y;

        if(nextPos.y <= checkY && nextPos.y + playerDims.y > checkY &&
            nextPos.x < currPoint.x && nextPos.x + playerDims.x > prevPoint.x &&
            playerPos.y + playerDims.y >= checkY)
            {
                nextPos.y = checkY;
                break;
            }

        prevPoint = currPoint;
    }

    return nextPos;
}