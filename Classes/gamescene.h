#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <cocos2d.h>
#include "background.h"
#include "player.h"
class GameScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
private:
    void update(float);
    Background _background;
    Player _player;
};


#endif // GAMESCENE_H
