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

    enum Type{ArchiW,Bullet,Defender};

    RocketBase();
    virtual ~RocketBase();
    RocketColor getColor()const;
    void setColor(RocketColor);
    cocos2d::Sprite* getSprite();



    Type getType() const;

    void setType(const Type &type);

protected:
    RocketColor _color = GREEN;
    Type _type;
    cocos2d::Sprite* _mainSprite;
    cocos2d::Sprite*  _redSprite;
    cocos2d::Sprite*  _blueSprite;
    cocos2d::Sprite*  _greenSprite;
    cocos2d::Sprite*  _yellowSprite;

};

#endif // ROCKETBASE_H
