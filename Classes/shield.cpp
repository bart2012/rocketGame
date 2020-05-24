#include "shield.h"
#include "gamescene.h"

Shield::Shield(void *gameScene): Booster(gameScene)
{
    _physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(113,133));
    _sprite = cocos2d::Sprite::create("bonus icon/protect.png");
    _sprite->addComponent(_physicsBody);
    _physicsBody->setName("booster");
    _physicsBody->setContactTestBitmask(1);
    spawn();
    ((GameScene*)_gameScene)->addChild(_sprite);

}

void Shield::start()
{
    //_protectRocket = cocos2d::Sprite::create("PNG/protect.png");
    ((GameScene*)_gameScene)->setProtect(true);
    //((GameScene*)_gameScene)->player()._sprite->addChild(_protectRocket);
    Booster::start();
    //((GameScene*)_gameScene)->player()._sprite->removeChild(_protectRocket,true);

}

Shield::~Shield()
{
    ((GameScene*)_gameScene)->setProtect(false);
}
