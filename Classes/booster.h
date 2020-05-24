#ifndef BOOSTER_H
#define BOOSTER_H
#include <cocos2d.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
class Booster
{
public:
    Booster(void *gameScene);
    virtual ~Booster();
    void spawn();
    virtual void start();
    cocos2d::Sprite *sprite() const;
    void pause();
    void resume();
protected:
    cocos2d::Sprite *_sprite;
    cocos2d::PhysicsBody *_physicsBody{nullptr};
    void *_gameScene;
};

#endif // BOOSTER_H
