#include "doublescore.h"
#include "gamescene.h"

DoubleScore::DoubleScore(void *gameScene): Booster(gameScene)
{
    _physicsBody = cocos2d::PhysicsBody::createCircle(48);
    //physicsBody->setDynamic(false);
    _sprite = cocos2d::Sprite::create("bonus icon/x2.png");
    _sprite->addComponent(_physicsBody);
    _physicsBody->setName("booster");
    _physicsBody->setContactTestBitmask(1);
    spawn();
    ((GameScene*)_gameScene)->addChild(_sprite);
}

void DoubleScore::start()
{
    ((GameScene*)_gameScene)->setScoreMultiplier(2);
    Booster::start();
}

DoubleScore::~DoubleScore()
{
    ((GameScene*)_gameScene)->setScoreMultiplier(1);
}
