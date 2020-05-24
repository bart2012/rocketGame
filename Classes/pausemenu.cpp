#include "pausemenu.h"
#include "gamescene.h"
#include <AudioEngine.h>

extern cocos2d::Vec2 sizeScene;

PauseMenu::PauseMenu(void *gameScene):_gameScene(gameScene)
{
    _layer = cocos2d::Layer::create();
    _layer->setAnchorPoint(cocos2d::Vec2(0,0));
    _background = cocos2d::Sprite::create("endMenu/background.png");
    _background->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2));
    _layer->addChild(_background);
    _continue = cocos2d::ui::Button::create("PNG/continueButton.png");
    _continue->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){        AudioEngine::play2d("click.mp3");
((GameScene*)_gameScene)->continueGame();});
    //_restart->setAnchorPoint(cocos2d::Vec2(0,0));
    _continue->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2));
    _layer->addChild(_continue);
    _mainMenu = cocos2d::ui::Button::create("endMenu/buttonMainMenu.png");
    _mainMenu->setPosition(cocos2d::Vec2(sizeScene.x/2,sizeScene.y/2-250));
    _mainMenu->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        AudioEngine::play2d("click.mp3");

        delete this;
        //зміна сцени
    });
    _label = cocos2d::Label::createWithTTF("Pause","fonts/3953.ttf",120);
    _label->setTextColor(cocos2d::Color4B(200,200,200,200));

    _label->setPosition(sizeScene.x/2,sizeScene.y/2+250);
    _layer->addChild(_label);

    _layer->addChild(_mainMenu);
    _layer->retain();

    //_layer->setPosition(sizeScene.x,0);
}

void PauseMenu::show()
{
    ((GameScene*)_gameScene)->addChild(_layer);
    //_layer->runAction(cocos2d::MoveTo::create(0.3,cocos2d::Vec2(0,0)));
}

PauseMenu::~PauseMenu()
{
    ((GameScene*)_gameScene)->removeChild(_layer);
}
