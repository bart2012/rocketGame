#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "background.h"
#include "losemenu.h"
#include "meteorites.h"
#include "player.h"
#include <cocos2d.h>
#include "coin.h"
#include <cocos/ui/CocosGUI.h>
#include <planet.h>
#include "booster.h"
#include "pausemenu.h"
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void restartGame();
    void continueGame();
    bool protect() const;
    void setProtect(bool protect);

    int scoreMultiplier() const;
    void setScoreMultiplier(int scoreMultiplier);

    int speedMultiplier() const;
    void setSpeedMultiplier(int speedMultiplier);

    Player& player() ;

private:
    void createBarrier();
    void initScore();
    void update(float);
    bool onContactBegin(PhysicsContact &contact);
    void endGame();
    void createDownBarrier();
    void generateBooster();
    Background *_background;
    Player _player;
    Meteorites _meteorites;
    Coin _coin;
    Node *_barrier;
    Node *_downBarrier;
    Label *_scoreLabel;
    LoseMenu *_loseMenu;
    int _score{ 0 };
    int _complexity{ 1 };
    ui::Button *_pauseButton;
    bool _protect {false};
    int _scoreMultiplier{1};
    int _speedMultiplier{1};
    Booster *_booster{nullptr};
    int iterGerateBooster{120};
    PauseMenu *_pauseMenu;
    std::mutex _pauseMutex;
};

#endif // GAMESCENE_H
