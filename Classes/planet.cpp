#include "planet.h"
#include <thread>
#include <ccRandom.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
extern cocos2d::Vec2 sizeScene;

Planet::Planet(int *complexity):_complexity(complexity)
{
    _layer = cocos2d::Layer::create();
    _planetArray.reserve(6);
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet1.png"));
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet2.png"));
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet3.png"));
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet4.png"));
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet5.png"));
    _planetArray.push_back(cocos2d::Sprite::create("Planets/planet6.png"));
    for(int i=0;i<6;i++)
    {
        _planetArray[i]->setAnchorPoint(cocos2d::Vec2(0,0));
        _planetArray[i]->retain();
        _planetArray[i]->setPositionY(-1);
    }
}

void Planet::addToScene(cocos2d::Scene *scene)
{
    scene->addChild(_layer);
    start();
}

void Planet::start()
{
    std::thread spawnPlanetThread([&]{
        while(true)
        {
            //if(*_complexity==-1)
            //    break;
            int randomIndex;
            while (true) {
            randomIndex = cocos2d::random(0,5);
            if (_planetArray[randomIndex]->getPositionY()+_planetArray[randomIndex]->getTextureRect().getMaxY()*_planetArray[randomIndex]->getScale()<=0)
                break;
            }
            _planetArray[randomIndex]->setScale(cocos2d::random<double>(0.5,2));
            _planetArray[randomIndex]->setOpacity(cocos2d::random(200,256));
            _planetArray[randomIndex]->setPosition(cocos2d::Vec2(cocos2d::random<int>(0,sizeScene.x-_planetArray[randomIndex]->getTextureRect().getMaxX()),sizeScene.y));
            _layer->addChild(_planetArray[randomIndex]);
            _planetArray[randomIndex]->runAction(cocos2d::Sequence::create(cocos2d::MoveTo::create(6+cocos2d::random(0,4)-(*_complexity)*0.1,cocos2d::Vec2(_planetArray[randomIndex]->getPositionX(),-_planetArray[randomIndex]->getTextureRect().getMaxY()*_planetArray[randomIndex]->getScale())),cocos2d::CallFunc::create([this,randomIndex](){_layer->removeChild(_planetArray[randomIndex]);_planetArray[randomIndex]->retain();}),nullptr));
            sleep(4+rand()%2-(*_complexity*0.1));
        }
    });
    spawnPlanetThread.detach();
}

Planet::~Planet()
{
    for(size_t i=0;i<_planetArray.size();i++)
        _planetArray[i]->release();
}

