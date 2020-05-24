#include "booster.h"
#include <ccRandom.h>
#include "gamescene.h"
extern cocos2d::Vec2 sizeScene;

Booster::Booster(void *gameScene):_gameScene(gameScene)
{

}

void Booster::spawn()
{
    _sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    _sprite->setPosition(cocos2d::Vec2(cocos2d::random<int>(0,sizeScene.x-_sprite->getTextureRect().getMaxX()),sizeScene.y));
}

cocos2d::Sprite *Booster::sprite() const
{
    return _sprite;
}

void Booster::start()
{

    _sprite->removeAllComponents();
    _physicsBody = nullptr;
    _sprite->setPosition(cocos2d::Vec2(50,70));
    _sprite->setScale(2);
    sleep(4);
    for (double i=1;i<=5;i+=0.5)
    {
        _sprite->setVisible(!_sprite->isVisible());
        usleep(500000-50000*(int)i);

    }
    ((GameScene*)_gameScene)->removeChild(_sprite);
}

void Booster::pause()
{
    if (_physicsBody!=nullptr)
        _sprite->getPhysicsBody()->setDynamic(false);
}

void Booster::resume()
{
    if (_physicsBody!=nullptr)
        _sprite->getPhysicsBody()->setDynamic(true);
}


Booster::~Booster()
{

}
