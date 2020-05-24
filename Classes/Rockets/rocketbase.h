#ifndef ROCKETBASE_H
#define ROCKETBASE_H
#include "cocos2d.h"

class RocketBase
{
public:
    enum RocketColor{
        RED=0,
        BLUE=1,
        GREEN=2,
        YELLOW=3
    };

    RocketBase();

    RocketColor getColor()const;
    void setColor(RocketColor);
    cocos2d::Sprite* getSprite();



    protected:
    RocketColor _color = GREEN;

    cocos2d::Sprite* _mainSprite;
    cocos2d::Sprite*  _redSprite;
    cocos2d::Sprite*  _blueSprite;
    cocos2d::Sprite*  _greenSprite;
    cocos2d::Sprite*  _yellowSprite;

};

#endif // ROCKETBASE_H
