#include "defenderrocket.h"

DefenderRocket::DefenderRocket()
{
    _redSprite=cocos2d::Sprite::create("RocketsCustomize/Defender/Red.png");
    _blueSprite=cocos2d::Sprite::create("RocketsCustomize/Defender/Blue.png");
    _greenSprite=cocos2d::Sprite::create("RocketsCustomize/Defender/Green.png");
    _yellowSprite=cocos2d::Sprite::create("RocketsCustomize/Defender/Yellow.png");
    _mainSprite=_greenSprite;
}
