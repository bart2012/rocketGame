#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <cocos2d.h>
#include <vector>
class Background
{
public:
    Background();
    ~Background();
    void addToScene(cocos2d::Scene *scene);
    void update(cocos2d::Scene *scene);
private:
    cocos2d::Sprite *_backgroundSprite;
    cocos2d::Texture2D *_starsTexture;
    cocos2d::Sprite **_starsMasSprites;
    cocos2d::Texture2D *_cometaTexture;
    cocos2d::Sprite *_moonSprite;
    void createComets();
    void updateComets(cocos2d::Scene *scene);
    void updateStars();
    void removeComets(cocos2d::Scene *scene);
    void setupComets();
    std::vector<cocos2d::Sprite*> _cometaVectorSprites;
    int _numberForCallCreateComets{0};
    int _iterOfNumberForCallCreateComets{0};
};

#endif // BACKGROUND_H
