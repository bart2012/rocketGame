#include "background.h"
#include <random>
#include <ctime>
#include <cmath>
#define PI 3.14159265
Background::Background()
{
    _starsTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/stars.png");
    _cometaTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/cometa.png");
    _backgroundSprite = cocos2d::Sprite::create("PNG/background.png");
    _backgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
    _moonSprite = cocos2d::Sprite::create("PNG/moon.png");
    // _moonSprite = cocos2d::Sprite::create();
    // _moonSprite->setTexture(_cometaTexture);
    // _moonSprite->setTextureRect(cocos2d::Rect(0,0,18,143));
    _moonSprite->setAnchorPoint(cocos2d::Vec2(0,0));
    _starsMasSprites = new cocos2d::Sprite* [2];
    for(int i = 0;i<2;i++)
    {
        _starsMasSprites[i] = cocos2d::Sprite::create();
        _starsMasSprites[i]->setTexture(_starsTexture);
        _starsMasSprites[i]->setTextureRect(cocos2d::Rect(0,0,1058,1880));
        _starsMasSprites[i]->setAnchorPoint(cocos2d::Vec2(0,0));
        _starsMasSprites[i]->setPosition(cocos2d::Vec2(0,0 + 1920*i));
    }
    _backgroundSprite->setPosition(cocos2d::Vec2(0,0));
    _moonSprite->setPosition(cocos2d::Vec2(0,0));
    setupComets();
}

void Background::update(cocos2d::Scene *scene)
{
    updateStars();
    updateComets(scene);
    //_moonSprite->runAction(cocos2d::MoveBy::create(1,cocos2d::Vec2(0,0.5)));
}

void Background::addToScene(cocos2d::Scene *scene)
{
    scene->addChild(_backgroundSprite);
    for(int i=0;i<2;i++)
    {
        scene->addChild(_starsMasSprites[i]);
    }
    for(unsigned int i=0;i<_cometaVectorSprites.size();i++)
    {
        scene->addChild(_cometaVectorSprites[i]);
    }
    //scene->addChild(_moonSprite);
}

void Background::updateComets(cocos2d::Scene *scene)
{
    removeComets(scene);
    //create new comets
    if(_iterOfNumberForCallCreateComets>=_numberForCallCreateComets)
    {
        //srand(time(0));
        createComets();
        _numberForCallCreateComets = rand()%30+30;
        _iterOfNumberForCallCreateComets=-1;
        scene->addChild(_cometaVectorSprites[_cometaVectorSprites.size()-1]);
    }
    ++_iterOfNumberForCallCreateComets;
}

void Background::createComets()
{
    cocos2d::Vec2 cometsPosition;
    int rotation;
    cocos2d::Sprite* cometa;
    int speed = rand()%1800+1800;
    //srand(time(0));
    cometa = cocos2d::Sprite::create();
    cometa->setTexture(_cometaTexture);
    cometa->setTextureRect(cocos2d::Rect(0,0,18,143));
    int opacity;
    opacity = rand()%200+55;
    switch (rand()%4)
    {
    case 0:
        cometsPosition.x=-142;
        //cometsPosition.x=142;
        cometsPosition.y = rand()%1920;
        //srand(time(0));
        rotation = rand()%178;
        if (rotation<90)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(speed,tan((90-rotation)*PI/180)*speed)));
        }
        else
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(speed,-tan((rotation-90)*PI/180)*speed)));
        }
        break;
    case 1:
        cometsPosition.x=1222;
        //cometsPosition.x=222;
        cometsPosition.y = rand()%1920;
        //srand(time(0));
        rotation = -rand()%178;
        if (rotation<-90)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-speed,tan((90-abs(rotation))*PI/180)*speed)));
        }
        else
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-speed,-tan((abs(rotation)-90)*PI/180)*speed)));
        }
        break;
    case 2:
        cometsPosition.x= rand()%1080;
        cometsPosition.y = -142;
        //cometsPosition.y = 142;
        rotation = rand()%178-86;
        if (rotation<0)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-tan(abs(rotation)*PI/180)*speed,speed)));
        }
        else
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(tan(rotation*PI/180)*speed,speed)));
        }
        break;
    case 3:
        cometsPosition.x= rand()%1080;
        cometsPosition.y = 2063;
        //cometsPosition.y = 1000;
        //srand(time(0));
        rotation = rand()%178+91;
        if (rotation<270)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(tan((180-rotation)*PI/180)*speed,-speed)));
        }
        else
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-tan((rotation-180)*PI/180)*speed,-speed)));
        }
        break;
    }
    cometa->setPosition(cometsPosition);
    cometa->setRotation(rotation);
    _cometaVectorSprites.push_back(cometa);
    cometa->setOpacity(opacity);
}
void Background::updateStars()
{
    for(int i=0;i<2;i++)
    {
        _starsMasSprites[i]->runAction(cocos2d::MoveBy::create(0.1,cocos2d::Vec2(0,-5)));
        if(_starsMasSprites[i]->getPositionY()<=-1920)
        {
            _starsMasSprites[i]->setPosition(cocos2d::Vec2(0,1920));
        }
    }
}
Background::~Background()
{
    delete _starsMasSprites;
}

void Background::setupComets()
{
    srand(time(0));
    int numberOfComets = rand()%15+10;
    cocos2d::Vec2 cometsPosition;
    int rotation;
    cocos2d::Sprite* cometa;
    int speed;
    int opacity;
    for(int i=0;i<numberOfComets;i++)
    {
        opacity = rand()%200+55;
        speed = rand()%1000+700;
        cometa = cocos2d::Sprite::create();
        cometa->setTexture(_cometaTexture);
        cometa->setTextureRect(cocos2d::Rect(0,0,18,143));
        cometsPosition.x=rand()%1080;
        cometsPosition.y = rand()%1920;
        rotation = rand()%360;
        if (rotation<90)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(speed,tan((90-rotation)*PI/180)*speed)));
        }
        if (rotation>=90&&rotation<180)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(speed,-tan((rotation-90)*PI/180)*speed)));
        }
        if (rotation>=180&&rotation<270)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-tan((rotation-180)*PI/180)*speed,-speed)));
        }
        if (rotation>=270&&rotation<360)
        {
            cometa->runAction(cocos2d::MoveBy::create(50,cocos2d::Vec2(-speed,tan((rotation-270)*PI/180)*speed)));
        }
        cometa->setPosition(cometsPosition);
        cometa->setOpacity(opacity);
        cometa->setRotation(rotation);
        _cometaVectorSprites.push_back(cometa);
    }
}

void Background::removeComets(cocos2d::Scene *scene)
{
    cocos2d::Vec2 cometasPosition;
    for(unsigned int i=0;i<_cometaVectorSprites.size();i++)
    {
        cometasPosition = _cometaVectorSprites[i]->getPosition();
        if(cometasPosition.x>1223||cometasPosition.x<-143||cometasPosition.y>2063||cometasPosition.y<-143)
        {
            scene->removeChild(_cometaVectorSprites[i]);
            _cometaVectorSprites.erase(_cometaVectorSprites.begin()+i);
            --i;
        }
    }
}

