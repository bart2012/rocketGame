#ifndef PLAYER_H
#define PLAYER_H
#include <cocos2d.h>
#include <string>
#include <mutex>

class Player
{
public:
    Player();
    ~Player();
    void addToScene(cocos2d::Scene *scene);
    void moveLeft();
    void moveRight();
    void moveEnd();
    // private:
    cocos2d::Sprite *_sprite;
    cocos2d::PhysicsBody *_physicsBody;
    std::string name = "player";
    std::mutex moveMutex;
    int _speed = 150;
    int _angularSpeed = 2;
    cocos2d::RotateTo *_rotateTo0Angul;
};

#endif // PLAYER_H
