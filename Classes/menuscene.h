#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <cocos2d.h>
#include "ui/CocosGUI.h"
class MenuScene: public cocos2d::Scene
{
public:
    MenuScene();
    ~MenuScene();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuScene);
private:
    cocos2d::Sprite *_backgroundSprite;
    cocos2d::Node *_settingsMenu;
    cocos2d::Menu *menu;

    void menuSettingClicked(cocos2d::Ref *);
    void menuCoinsClicked(cocos2d::Ref *);
    void menuStoreClicked(cocos2d::Ref *);
    void menuStartClicked(cocos2d::Ref *);
    void menuCustomizeClicked(cocos2d::Ref *musicCheckboxClicked);
    void backButtonClicked(cocos2d::Ref *);
    static void musicCheckboxClicked(cocos2d::ui::CheckBox::Ref*, cocos2d::ui::CheckBox::EventType);
    static void soundCheckboxCliced(cocos2d::ui::CheckBox::Ref*, cocos2d::ui::CheckBox::EventType);
};


#endif // MENUSCENE_H
