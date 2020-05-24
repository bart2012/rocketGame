#ifndef SHIELD_H
#define SHIELD_H
#include "booster.h"


class Shield : public Booster
{
public:
    Shield(void *gameScene);
    void start();
    ~Shield();
private:
    //cocos2d::Sprite *_protectRocket;
};

#endif // SHIELD_H
