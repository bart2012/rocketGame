#include "menuscene.h"
#include "gamescene.h"
MenuScene::MenuScene(){
_backgroundSprite = cocos2d::Sprite::create("startmenu/bg.png");
_backgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
}
cocos2d::Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
     short width=1080;short height=1920;
    schedule(CC_SCHEDULE_SELECTOR(MenuScene::update));
    this->addChild(_backgroundSprite);


    auto settingItem=cocos2d::MenuItemImage::create("startmenu/setting.png","startmenu/setting.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuSettingClicked,this));
    auto coinsItem=cocos2d::MenuItemImage::create("startmenu/coins.png","startmenu/coins.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuCoinsClicked,this));
    auto storeItem=cocos2d::MenuItemImage::create("startmenu/store.png","startmenu/store.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuStoreClicked,this));
    auto playItem=cocos2d::MenuItemImage::create("startmenu/buttonstart.png","startmenu/buttonstart_clicked.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuStartClicked,this));
    auto customizeItem=cocos2d::MenuItemImage::create("startmenu/buttoncustomize.png","startmenu/buttoncustomize_clicked.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuCustomizeClicked,this));

    settingItem->setPosition(cocos2d::Point(100,height-100));
    coinsItem->setPosition(cocos2d::Point(width/ 2,height-100));
    storeItem->setPosition(cocos2d::Point(width-100,height-100));
    playItem->setPosition(cocos2d::Point(width/ 2,615));
    customizeItem->setPosition(cocos2d::Point(width/ 2,320));

    auto *menu = cocos2d::Menu::create(settingItem,coinsItem,storeItem,playItem,customizeItem,NULL);
    menu->setPosition(cocos2d::Point(0,0));
    this->addChild(menu);
    return true;
}

void MenuScene::menuSettingClicked(cocos2d::Ref * ){
 CCLOG("Settings");
}
void MenuScene::menuCoinsClicked(cocos2d::Ref * ){
 CCLOG("Coins");
}
void MenuScene::menuStoreClicked(cocos2d::Ref * ){
 CCLOG("Store");
}
void MenuScene::menuStartClicked(cocos2d::Ref * ){
 auto director = cocos2d::Director::getInstance();
 cocos2d::Scene *scene = GameScene::createScene();
 director->replaceScene(scene);
}
void MenuScene::menuCustomizeClicked(cocos2d::Ref * ){
 CCLOG("Customize");
}
MenuScene::~MenuScene(){

}


