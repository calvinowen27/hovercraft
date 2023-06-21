#ifndef UI_MANAGER_INCLUDE
#define UI_MANAGER_INCLUDE

#include <vector>
#include "UIElement.h"
#include "TextElement.h"

class UIManager
{
    private:
        static UIManager *_pInstance;
        Game *_pGame;
        std::vector<UIElement *> _uiElements;

        TextElement *_pFPScounter;
        TextElement *_pUPScounter;

        SDL_Color _white{255, 255, 255, 255};
        SDL_Color _black{0, 0, 0, 255};

    public:
        UIManager();
        static UIManager* getInstance();
        void init();
        void update();
        void draw(SDL_Renderer *pRenderer);
        void addElement(UIElement *pEl);
};

#endif