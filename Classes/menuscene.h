#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "topbarbuttons.h"
#include "gamescene.h"
#include "customizescene.h"
#include "Rockets/rocketbase.h"
class MenuScene: public cocos2d::Scene
{
public:
    MenuScene();
    ~MenuScene();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuScene);
    RocketBase *_rocket;

private:
    cocos2d::Sprite *_backgroundSprite;
    cocos2d::Node *_settingsMenu;
    cocos2d::Menu *menu;
    //cocos2d::Label *_countCoinLabel;
    void menuSettingClicked(cocos2d::Ref *);    
    void menuStartClicked(cocos2d::Ref *);
    void menuCustomizeClicked(cocos2d::Ref *musicCheckboxClicked);
    void backButtonClicked(cocos2d::Ref *);
    static void musicCheckboxClicked(cocos2d::ui::CheckBox::Ref*, cocos2d::ui::CheckBox::EventType);
    static void soundCheckboxCliced(cocos2d::ui::CheckBox::Ref*, cocos2d::ui::CheckBox::EventType);
};


#endif // MENUSCENE_H
