#ifndef COIN_H
#define COIN_H
#include <cocos2d.h>
#include <vector>
class Coin
{
public:
    Coin();
    void update();
    void generate();
    void remove();
    void remove(cocos2d::PhysicsBody *body);
    void addToScene(cocos2d::Scene *scene);
    void deleteAll();
    int countCoin() const;
    void setCountCoin(int countCoin);
    void pause();
    void resume();
private:
    cocos2d::Layer *_layer;
    cocos2d::Texture2D *_coinTexture;
    std::vector<cocos2d::Sprite *> _coinsArray;
    cocos2d::Rect _rect;
    int _numberForGenerate;
    int _iterOfNumberForGenerate{ 0 };
    cocos2d::Sprite *_coinCountSprite;
    cocos2d::Label *_coinCountLabel;
    int _countCoin {0};
    double mass{1700};
};

#endif // COIN_H
