#include "rocketbase.h"

RocketBase::RocketBase()
{
}

 RocketBase::RocketColor RocketBase::getColor() const{
   return _color;
}
 void RocketBase::setColor(RocketColor color){
     _color=color;

     _mainSprite=(color==RED)?_redSprite:(color==BLUE)?
                                  _blueSprite:(color==GREEN)?_greenSprite:_yellowSprite;
 }
 cocos2d::Sprite* RocketBase::getSprite(){
     return _mainSprite;
 }
