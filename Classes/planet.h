#ifndef PLANET_H
#define PLANET_H
#include <cocos2d.h>
#include <vector>
class Planet
{
public:
    Planet(int *complexity);
    ~Planet();
    void addToScene(cocos2d::Scene *scene);
    void start();
private:
    cocos2d::Layer *_layer;
    std::vector<cocos2d::Sprite*> _planetArray;
    int _numberForGenerate { 120 };
    int _iterOfNumberForGenerate{ 0 };
    int *_complexity;
};

#endif // PLANET_H
