#include "player.h"
#include "physicsbodyloader/PhysicsShapeCache.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

extern cocos2d::Vec2 sizeScene;

Player::Player()
{
    _sprite = cocos2d::Sprite::create("Rockets/Bullet/Red.png");
    //_sprite->setAnchorPoint(cocos2d::Vec2(0,0));
    _sprite->setPosition(cocos2d::Vec2(540, 400));
    PhysicsShapeCache::getInstance()->addShapesWithFile("physicsBody/rocket.plist");
    _physicsBody = PhysicsShapeCache::getInstance()->createBodyWithName("rocket");
    _physicsBody->setDynamic(true);
    _physicsBody->setMass(0);
    _physicsBody->setGravityEnable(false);
    //_physicsBody->setCategoryBitmask(1);
    //_physicsBody->setCollisionBitmask(2);
    _physicsBody->setContactTestBitmask(1);
    _physicsBody->setName(name);
    _sprite->addComponent(_physicsBody);
    _rotateTo0Angul = cocos2d::RotateTo::create(0.24, 0);
    _rotateTo0Angul->retain();
    _rotateTo0Angul->update(0.01);

}

Player::~Player()
{
    _rotateTo0Angul->release();
}

void Player::addToScene(cocos2d::Scene *scene) { scene->addChild(_sprite); }
void Player::moveLeft()
{
    moveMutex.lock();
    _physicsBody->setAngularVelocity(_angularSpeed);
    moveMutex.unlock();
    for (int i = 0; i < 5; i++)
    {
        if (!moveMutex.try_lock())
            return;
        _physicsBody->setVelocity(cocos2d::Vec2(_physicsBody->getVelocity().x - _speed, 0));
        moveMutex.unlock();
        usleep(50000);
    }
    moveMutex.lock();
    _physicsBody->setAngularVelocity(0);
    moveMutex.unlock();
}
void Player::moveRight()
{
    moveMutex.lock();
    _physicsBody->setAngularVelocity(-_angularSpeed);
    moveMutex.unlock();
    for (int i = 0; i < 5; i++)
    {
        if (!moveMutex.try_lock())
            return;
        _physicsBody->setVelocity(cocos2d::Vec2(_physicsBody->getVelocity().x + _speed, 0));
        moveMutex.unlock();
        usleep(50000);
    }
    moveMutex.lock();
    _physicsBody->setAngularVelocity(0);
    moveMutex.unlock();
}

void Player::moveEnd()
{

    CCLOG("stop start");
    moveMutex.lock();
    //CCLOG("stop start2");
    _physicsBody->setAngularVelocity(0);
    CCLOG("stop start3");
    //auto a  = _rotateTo0Angul->clone();
    //a->retain();
        _sprite->runAction(_rotateTo0Angul);
    for (int i = 0; i < 3; i++)
    {
        usleep(100000);
        CCLOG("stop start5");
        _physicsBody->setVelocity(cocos2d::Vec2(_physicsBody->getVelocity().x / 1.5, 0));
        CCLOG("stop start6");
    }
    CCLOG("stop end2");
    CCLOG("stop end");
    _rotateTo0Angul->retain();
    _physicsBody->setVelocity(cocos2d::Vec2(0, 0));
    moveMutex.unlock();
}

