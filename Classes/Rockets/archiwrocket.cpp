#include "archiwrocket.h"
ArchiWRocket::ArchiWRocket()
{
    _redSprite=cocos2d::Sprite::create("RocketsCustomize/ArchiW/Red.png");
    _blueSprite=cocos2d::Sprite::create("RocketsCustomize/ArchiW/Blue.png");
    _greenSprite=cocos2d::Sprite::create("RocketsCustomize/ArchiW/Green.png");
    _yellowSprite=cocos2d::Sprite::create("RocketsCustomize/ArchiW/Yellow.png");
    _mainSprite=_greenSprite;
    _redSprite->retain();
    _blueSprite->retain();
    _greenSprite->retain();
    _yellowSprite->retain();
    _type = Type::ArchiW;
}
