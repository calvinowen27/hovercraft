#ifndef UI_MANAGER_INCLUDE
#define UI_MANAGER_INCLUDE

#define WHITE SDL_Color{255, 255, 255, 255}
#define BLACK SDL_Color{0, 0, 0, 255}
#define GRAY SDL_Color{127, 127, 127, 255}
#define RED SDL_Color{255, 0, 0, 255}
#define GREEN SDL_Color{0, 255, 0, 255}
#define BLUE SDL_Color{0, 0, 255, 255}

#include <vector>
#include "UIElement.h"
#include "TextElement.h"

class UIManager
{
    private:
        static UIManager *_pInstance;
        Game *_pGame;
        Player *_pPlayer;
        std::vector<UIElement *> _uiElements;

        TextElement *_pFPScounter;
        TextElement *_pUPScounter;
        TextElement *_pPosDisplay;
        TextElement *_pVelDisplay;
        TextElement *_pAccDisplay;

    public:
        UIManager();
        static UIManager* getInstance();
        void init();
        void update();
        void draw(SDL_Renderer *pRenderer);
        void addElement(UIElement *pEl);
};

#endif