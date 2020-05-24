#include "meteorites.h"
#include<ccRandom.h>
extern cocos2d::Vec2 sizeScene;
Meteorites::Meteorites()
{
    _layer  = cocos2d::Layer::create();
    _meteoriteTexture = new cocos2d::Texture2D* [2];
    _meteoriteTexture[0] = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/barrier1.png");
    _meteoriteTexture[1] = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/barrier2.png");
    PhysicsShapeCache::getInstance()->addShapesWithFile("physicsBody/b1.plist");
    PhysicsShapeCache::getInstance()->addShapesWithFile("physicsBody/b2.plist");
}

void Meteorites::update()
{
    generate();
    remove();
}
void Meteorites::addToScene(cocos2d::Scene *scene)
{
    scene->addChild(_layer);
}

void Meteorites::generate()
{
    _iterOfNumberForGenerate++;
    if(_iterOfNumberForGenerate>=_numberForGenerate)
    {
        cocos2d::PhysicsBody *physicsBody= cocos2d::PhysicsBody::create();
        cocos2d::Sprite *sprite = cocos2d::Sprite::create();
        if(random(0,1))
        {
        physicsBody = PhysicsShapeCache::getInstance()->createBodyWithName("barrier1");
        physicsBody->setDynamic(true);
        physicsBody->setMass(1);
        sprite->setTexture(_meteoriteTexture[0]);
        sprite->setTextureRect(cocos2d::Rect(0,0,267,205));
        sprite->setAnchorPoint(cocos2d::Vec2(0,0));
        sprite->addComponent(physicsBody);
        sprite->setPosition(cocos2d::Vec2(cocos2d::random(0,((int)sizeScene.x-267)),sizeScene.y));
        physicsBody->setContactTestBitmask(1);
        physicsBody->setName(name);
        }
        else
        {
            physicsBody = PhysicsShapeCache::getInstance()->createBodyWithName("barrier2");
            physicsBody->setDynamic(true);
            physicsBody->setMass(1);
            sprite->setTexture(_meteoriteTexture[1]);
            sprite->setTextureRect(cocos2d::Rect(0,0,201,200));
            sprite->setAnchorPoint(cocos2d::Vec2(0,0));
            sprite->addComponent(physicsBody);
            sprite->setPosition(cocos2d::Vec2(cocos2d::random(0,((int)sizeScene.x-267)),sizeScene.y));
            physicsBody->setContactTestBitmask(1);
            physicsBody->setName(name);
        }
        _layer->addChild(sprite);
        _meteoritesVector.push_back(sprite);
        _iterOfNumberForGenerate=0;
    }
}


void Meteorites::remove()
{
    for(unsigned int i=0;i<_meteoritesVector.size();i++)
    {
        if (_meteoritesVector[i]->getPosition().y<-205)
        {
            _layer->removeChild(_meteoritesVector[i]);
            _meteoritesVector.erase(_meteoritesVector.begin()+i);
            --i;
        }
    }
}

void Meteorites::deleteAll()
{
     for (size_t i=0;i<_meteoritesVector.size();i++)
         _layer->removeChild(_meteoritesVector[i]);
    _meteoritesVector.clear();
}


void Meteorites::remove(cocos2d::PhysicsBody *body)
{
    for (size_t i=0;i<_meteoritesVector.size();i++)
    {
        if(body==_meteoritesVector[i]->getPhysicsBody())
        {
            _layer->removeChild(_meteoritesVector[i]);
            _meteoritesVector.erase(_meteoritesVector.begin()+i);
            break;
        }
    }
}

void Meteorites::pause()
{
    for (size_t i=0;i<_meteoritesVector.size();i++)
    _meteoritesVector[i]->getPhysicsBody()->setDynamic(false);
}

void Meteorites::resume()
{
    for (size_t i=0;i<_meteoritesVector.size();i++)
    _meteoritesVector[i]->getPhysicsBody()->setDynamic(true);
}

Meteorites::~Meteorites()
{
    delete [] _meteoriteTexture;
}


