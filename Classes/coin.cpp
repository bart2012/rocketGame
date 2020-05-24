#include "coin.h"
#include <ccRandom.h>
#include <string.h>
//#include "physicsbodyloader/PhysicsShapeCache.h"

extern cocos2d::Vec2 sizeScene;

Coin::Coin()
{
    _layer  = cocos2d::Layer::create();
    _coinTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/coin.png");
    _rect.setRect(0,0,156,149);
    _iterOfNumberForGenerate = 60 + cocos2d::random(0,60);
    _coinCountSprite = cocos2d::Sprite::create("PNG/coin count.png");
    _coinCountSprite->setAnchorPoint(cocos2d::Vec2(1,1));
    _coinCountSprite->setPosition(cocos2d::Vec2(sizeScene.x,sizeScene.y-100));
    _coinCountLabel = cocos2d::Label::createWithTTF("0","fonts/3953.ttf",100);
    _coinCountLabel->setPosition(cocos2d::Vec2(130,0));
    _coinCountLabel->setTextColor(cocos2d::Color4B(200,200,200,200));
    _coinCountLabel->setAnchorPoint(cocos2d::Vec2(0,0));
    _coinCountSprite->addChild(_coinCountLabel);
    _layer->addChild(_coinCountSprite);
}

void Coin::addToScene(cocos2d::Scene *scene)
{
    scene->addChild(_layer);
}

void Coin::update()
{
    generate();
    remove();
}

void Coin::generate()
{
    _numberForGenerate++;
    if(_iterOfNumberForGenerate<=_numberForGenerate)
    {
        cocos2d::Sprite *sprite = cocos2d::Sprite::createWithTexture(_coinTexture);
        cocos2d::PhysicsBody *body = cocos2d::PhysicsBody::createCircle(75);
        body->setName("coin");
        body->setContactTestBitmask(1);
        sprite->addComponent(body);
        sprite->setAnchorPoint(cocos2d::Vec2(0,0));
        sprite->setPosition(cocos2d::Vec2(cocos2d::random(0,((int)(sizeScene.x-_rect.getMaxX()))),sizeScene.y));
        _coinsArray.push_back(sprite);
        _layer->addChild(sprite);
        _iterOfNumberForGenerate = 180 + cocos2d::random(0,120);
        _numberForGenerate=0;

    }
}

void Coin::remove()
{
    for(unsigned int i=0;i<_coinsArray.size();i++)
    {
        if (_coinsArray[i]->getPosition().y<-_rect.getMaxY())
        {
            _layer->removeChild(_coinsArray[i]);
            _coinsArray.erase(_coinsArray.begin()+i);
            --i;
        }
    }
}

void Coin::remove(cocos2d::PhysicsBody *body)
{
    for (size_t i=0;i<_coinsArray.size();i++)
    {
        if(body==_coinsArray[i]->getPhysicsBody())
        {
            _layer->removeChild(_coinsArray[i]);
            _coinsArray.erase(_coinsArray.begin()+i);
            _countCoin++;
            _coinCountLabel->setString(std::to_string(_countCoin));
            break;
        }
    }
}

void Coin::deleteAll()
{
    for (size_t i=0;i<_coinsArray.size();i++)
        _layer->removeChild(_coinsArray[i]);
    _coinsArray.clear();
}

int Coin::countCoin() const
{
    return _countCoin;
}

void Coin::setCountCoin(int countCoin)
{
    _countCoin = countCoin;
    _coinCountLabel->setString(std::to_string(_countCoin));
}

void Coin::pause()
{
    for (size_t i=0;i<_coinsArray.size();i++)
    _coinsArray[i]->getPhysicsBody()->setDynamic(false);
}

void Coin::resume()
{
    for (size_t i=0;i<_coinsArray.size();i++)
    _coinsArray[i]->getPhysicsBody()->setDynamic(true);
}

