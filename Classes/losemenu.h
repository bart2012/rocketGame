#ifndef LOSEMENU_H
#define LOSEMENU_H

#include <cocos2d.h>
#include <cocos/ui/CocosGUI.h>

class LoseMenu
{
public:
    LoseMenu(void *gameScene);
    ~LoseMenu();
    void show();
private:
    cocos2d::Sprite *_background;
    cocos2d::Sprite * _youLose;
    cocos2d::Layer *_layer;
    cocos2d::ui::Button *_restart;
    cocos2d::ui::Button *_mainMenu;
    void *_gameScene;
};

#endif // LOSEMENU_H
