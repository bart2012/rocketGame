#include "losemenu.h"
#include "gamescene.h"
#include <AudioEngine.h>
#include "menuscene.h"
extern cocos2d::Vec2 sizeScene;
extern MenuScene *mainMenu;

LoseMenu::LoseMenu(void *gameScene):_gameScene(gameScene)
{
    _layer = cocos2d::Layer::create();
    _layer->setAnchorPoint(cocos2d::Vec2(0,0));
    _background = cocos2d::Sprite::create("endMenu/background.png");
    _background->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2));
    _layer->addChild(_background);
    _youLose = cocos2d::Sprite::create("endMenu/YouLose.png");
    //_youLose->setAnchorPoint(cocos2d::Vec2(0,0));
    _youLose->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2+300));
    _layer->addChild(_youLose);
    _restart = cocos2d::ui::Button::create("endMenu/buttonRestart.png");\
    _restart->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){((GameScene*)_gameScene)->restartGame();        AudioEngine::play2d("click.mp3");});
    //_restart->setAnchorPoint(cocos2d::Vec2(0,0));
    _restart->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2));
    _layer->addChild(_restart);
    _mainMenu = cocos2d::ui::Button::create("endMenu/buttonMainMenu.png");
    _mainMenu->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2-250));
    _mainMenu->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        AudioEngine::play2d("Sound/click.mp3");
        cocos2d::Scene *scene = MenuScene::createScene();
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInT::create(1,scene ));

        delete this;
        //зміна сцени
    });
    _layer->addChild(_mainMenu);
    _layer->retain();
    //_layer->setPosition(sizeScene.x,0);
}

void LoseMenu::show()
{
    ((GameScene*)_gameScene)->addChild(_layer);
    //_layer->runAction(cocos2d::MoveTo::create(0.3,cocos2d::Vec2(0,0)));
}

LoseMenu::~LoseMenu()
{
    ((GameScene*)_gameScene)->removeChild(_layer);
}
