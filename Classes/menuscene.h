#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <cocos2d.h>

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

    void menuSettingClicked(cocos2d::Ref *);
    void menuCoinsClicked(cocos2d::Ref *);
    void menuStoreClicked(cocos2d::Ref *);
    void menuStartClicked(cocos2d::Ref *);
    void menuCustomizeClicked(cocos2d::Ref *);
};


#endif // MENUSCENE_H
