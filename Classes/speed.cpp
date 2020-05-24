#include "speed.h"
#include "gamescene.h"

SpeedUp::SpeedUp(void *gameScene): Booster(gameScene)
{
    _physicsBody = cocos2d::PhysicsBody::createCircle(48);
    _sprite = cocos2d::Sprite::create("bonus icon/speed.png");
    _sprite->addComponent(_physicsBody);
    _physicsBody->setName("booster");
    _physicsBody->setContactTestBitmask(1);
    spawn();
    ((GameScene*)_gameScene)->addChild(_sprite);
}

void SpeedUp::start()
{
    ((GameScene*)_gameScene)->setSpeedMultiplier(2);
    Booster::start();
}

SpeedUp::~SpeedUp()
{
    ((GameScene*)_gameScene)->setSpeedMultiplier(1);
}
