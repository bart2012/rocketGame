#ifndef METEORITES_H
#define METEORITES_H
#include "physicsbodyloader/PhysicsShapeCache.h"
#include <cocos2d.h>
#include <string>
#include <vector>

class Meteorites
{
public:
    Meteorites();
    ~Meteorites();
    void update();
    void addToScene(cocos2d::Scene *scene);
    void deleteAll();
    void remove(cocos2d::PhysicsBody *body);
    void pause();
    void resume();
private:
    cocos2d::Layer *_layer;
    cocos2d::Texture2D **_meteoriteTexture;
    std::vector<cocos2d::Sprite *> _meteoritesVector;
    int _numberForGenerate{ 120 };
    int _iterOfNumberForGenerate{ 0 };
    int speed{ 100 };

    std::string name = "meteorite";
    void generate();
    void remove();
    double mass{1};
};

#endif // METEORITES_H
