#include "bulletrocket.h"

BulletRocket::BulletRocket()
{
    _redSprite=cocos2d::Sprite::create("RocketsCustomize/Bullet/Red.png");
    _blueSprite=cocos2d::Sprite::create("RocketsCustomize/Bullet/Blue.png");
    _greenSprite=cocos2d::Sprite::create("RocketsCustomize/Bullet/Green.png");
    _yellowSprite=cocos2d::Sprite::create("RocketsCustomize/Bullet/Yellow.png");
    _mainSprite=_greenSprite;
    _redSprite->retain();
    _blueSprite->retain();
    _greenSprite->retain();
    _yellowSprite->retain();
    _type = Type::Bullet;

}
