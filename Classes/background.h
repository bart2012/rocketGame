#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <cocos2d.h>
#include <vector>
#include "planet.h"
class Background
{
public:
    Background(int *complexity,int *speedMultiplier);
    ~Background();
    void addToScene(cocos2d::Scene *scene);
    void update();
//private:
    cocos2d::Sprite *_backgroundSprite;
    cocos2d::Texture2D *_starsTexture;
    cocos2d::Sprite **_starsMasSprites;
    cocos2d::Texture2D *_cometaTexture;
    cocos2d::Sprite *_moonSprite;
    Planet *_planet;
    void createComets();
    void updateComets();
    void updateStars();
    void removeComets();
    void setupComets();
    cocos2d::Layer *_layer;
    std::vector<cocos2d::Sprite*> _cometaVectorSprites;
    int _numberForCallCreateComets{0};
    int _iterOfNumberForCallCreateComets{0};
    int *_complexity;
    int *_speedMultiplier;
    Planet *planet() const;
};

#endif // BACKGROUND_H
