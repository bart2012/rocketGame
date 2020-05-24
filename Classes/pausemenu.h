#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <cocos2d.h>
#include <cocos/ui/CocosGUI.h>

class PauseMenu
{
public:
    PauseMenu(void *gameScene);
    ~PauseMenu();
    void show();
private:
    cocos2d::Sprite *_background;
    cocos2d::Layer *_layer;
    cocos2d::ui::Button *_continue;
    cocos2d::ui::Button *_mainMenu;
    cocos2d::Label *_label;
    void *_gameScene;
};

#endif // PAUSEMENU_H
