#include "gamescene.h"
#include "doublenumberssupport.h"
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <string>
//#include <cocos/audio/android/audio.h>
#include <AudioEngine.h>
#include "doublescore.h"
#include "speed.h"
#include "shield.h"
#include<ccRandom.h>

extern cocos2d::Vec2 sizeScene;

cocos2d::Scene *GameScene::createScene()
{
    auto scene = createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -98.f));
    scene->getPhysicsWorld()->setSpeed(1);
    auto layer = GameScene::create();
    scene->addChild(layer);
    //scene->getPhysicsWorld()->setDebugDrawMask(1);
    return scene;
}


void GameScene::createDownBarrier()
{
    PhysicsBody *_barrierPhysicsBody = PhysicsBody::create();
    _downBarrier = Node::create();
    _barrierPhysicsBody->setDynamic(false);
    _barrierPhysicsBody->addShape(PhysicsShapeBox::create(Size(sizeScene.x,1),
                                                          PHYSICSSHAPE_MATERIAL_DEFAULT,
                                                          Vec2(sizeScene.x/2, -400)));
    _barrierPhysicsBody->setName("downBarrier");
    _barrierPhysicsBody->setContactTestBitmask(1);
    _downBarrier->addComponent(_barrierPhysicsBody);
    addChild(_downBarrier);
}

Player& GameScene::player()
{
    return _player;
}

void GameScene::createBarrier()
{
    PhysicsBody *_barrierPhysicsBody = PhysicsBody::create();
    _barrier = Node::create();
    _barrierPhysicsBody->setDynamic(false);
    _barrierPhysicsBody->addShape(PhysicsShapeBox::create(Size(1, sizeScene.y),
                                                          PHYSICSSHAPE_MATERIAL_DEFAULT,
                                                          Vec2(sizeScene.x - 1, sizeScene.y / 2)));
    _barrierPhysicsBody->addShape(PhysicsShapeBox::create(Size(1, sizeScene.y),
                                                          PHYSICSSHAPE_MATERIAL_DEFAULT,
                                                          Vec2(0, sizeScene.y / 2)));
    _barrierPhysicsBody->setName("barrier");
    _barrierPhysicsBody->setContactTestBitmask(1);
    _barrier->addComponent(_barrierPhysicsBody);
    addChild(_barrier);
}

void GameScene::initScore()
{
    _complexity = 1;
    _score = 0;
    _scoreLabel = cocos2d::Label::createWithTTF("Store:0","fonts/3953.ttf",80);
    _scoreLabel->setPosition(cocos2d::Vec2(0,sizeScene.y-225));
    _scoreLabel->setTextColor(cocos2d::Color4B(200,200,200,200));
    _scoreLabel->setAnchorPoint(cocos2d::Vec2(0,0));
    this->addChild(_scoreLabel);
    std::thread storeThread([&](){
        while(true)
        {
            if(_complexity==-1)
            {
                return;
            }
            _pauseMutex.lock();
            _score++;
            _scoreLabel->setString((std::string)"Score:"+std::to_string(_score));
            _pauseMutex.unlock();
            usleep((1000000 - 1000*_complexity)/_scoreMultiplier);
            if (_score/10>_complexity&&_complexity<99)
                _complexity+=1;
        }
    });
    storeThread.detach();

}

bool GameScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    schedule(CC_SCHEDULE_SELECTOR(GameScene::update));
    EventListenerPhysicsContact *contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    EventListenerTouchOneByOne *touchLister = EventListenerTouchOneByOne::create();
    touchLister->onTouchBegan = [&](Touch *touch, Event *event) {

        CCLOG("1!!!");
        void (Player::*move)();
        if (touch->getLocation().x < sizeScene.x / 2)
        {
            move = &Player::moveLeft;
        }
        else
        {
            move = &Player::moveRight;
        }
        std::thread movePlayerThread([&, move] {
            CCLOG("move");

            (_player.*move)();
            return;
        });
        movePlayerThread.detach();
        return true;
    };
    touchLister->onTouchEnded = [&](Touch *touch, Event *event)
    {
        if (!DoubleCompare::fuzzyIsNull(_player._physicsBody->getVelocity().x, 1))
        {
            CCLOG("moveEnd!!!");
            std::thread movePlayerEndThread([&] { _player.moveEnd(); });
            movePlayerEndThread.detach();
        }
        return true;
    };
    touchLister->setSwallowTouches(true);
    _background = new Background(&_complexity,&_speedMultiplier);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchLister, this);
    //startGame();
    _background->addToScene(this);
    _player.addToScene(this);
    _meteorites.addToScene(this);
    _coin.addToScene(this);
    _pauseButton = ui::Button::create("PNG/pauseButton.png");
    _pauseButton->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type==ui::Widget::TouchEventType::ENDED)
        {
            AudioEngine::play2d("Sound/click.mp3");

            pause();
            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
            _pauseMenu = new PauseMenu(this);
            _pauseMutex.lock();
            _pauseMenu->show();
            _coin.pause();
            _meteorites.pause();
            if(_booster!=nullptr)
                _booster->pause();
        }

        return true;
    });
    _pauseButton->setAnchorPoint(Vec2(0,0));
    _pauseButton->setPosition(Vec2(30,sizeScene.y-120));
    addChild(_pauseButton);
    initScore();
    //createBarrier();
    createDownBarrier();
    //initBooster();
    iterGerateBooster = random(500,1000);
    return true;
}

void GameScene::update(float)
{
    _background->update();
    _coin.update();
    _meteorites.update();
    generateBooster();
}
void GameScene::endGame()
{
    AudioEngine::play2d("lose.mp3");
    if (!DoubleCompare::fuzzyIsNull(_player._physicsBody->getVelocity().x, 1)&&_player._rotateTo0Angul->isDone())
    {
        _player.moveEnd();
    }
    //закинути кількість монет в головне меню
    delete _booster;
    _loseMenu = new LoseMenu(this);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    this->pause();
    _complexity=-1;
    _loseMenu->show();
    _meteorites.deleteAll();
    _coin.deleteAll();
}


void GameScene::generateBooster()
{
    iterGerateBooster--;
    if (iterGerateBooster<=0)
    {
        switch (random(1,3))
        {
        case 1: _booster = new DoubleScore(this);
            break;
        case 2: _booster = new Shield(this);
            break;
        case 3: _booster = new SpeedUp(this);
            break;
        }
        iterGerateBooster = random(1000,2000);
    }
}


int GameScene::speedMultiplier() const
{
    return _speedMultiplier;
}

void GameScene::setSpeedMultiplier(int speedMultiplier)
{
    _speedMultiplier = speedMultiplier;
}

int GameScene::scoreMultiplier() const
{
    return _scoreMultiplier;
}

void GameScene::setScoreMultiplier(int scoreMultiplier)
{
    _scoreMultiplier = scoreMultiplier;
}

bool GameScene::protect() const
{
    return _protect;
}

void GameScene::setProtect(bool protect)
{
    _protect = protect;
}
bool GameScene::onContactBegin(PhysicsContact &contact)
{
    if ((contact.getShapeA()->getBody()->getName() == "player"
         && contact.getShapeB()->getBody()->getName() == "meteorite")
            || (contact.getShapeB()->getBody()->getName() == "player"
                && contact.getShapeA()->getBody()->getName() == "meteorite"))
    {
        if(!_protect)
        {

            endGame();
        }
        else
        {
            if(contact.getShapeB()->getBody()->getName() == "meteorite")
                _meteorites.remove(contact.getShapeB()->getBody());
            else
                _meteorites.remove(contact.getShapeA()->getBody());

            //_protect = false;
        }

        return false;
    }
    if ((contact.getShapeA()->getBody()->getName() == "player"
         && contact.getShapeB()->getBody()->getName() == "barrier")
            || (contact.getShapeB()->getBody()->getName() == "player"
                && contact.getShapeA()->getBody()->getName() == "barrier"))
    {
        std::thread movePlayerEndThread([&] {
            //_player._sprite->runAction(RotateTo::create(0.3,-_player._physicsBody->getRotation()));
            _player._physicsBody->setVelocity(Vec2(-_player._physicsBody->getVelocity().x, 0));
            // usleep(300000);
            _player.moveEnd();
        });
        movePlayerEndThread.detach();
        return false;
    }
    if ((contact.getShapeA()->getBody()->getName() == "player"
         && contact.getShapeB()->getBody()->getName() == "booster")
            || (contact.getShapeB()->getBody()->getName() == "player"
                && contact.getShapeA()->getBody()->getName() == "booster"))
    {
        AudioEngine::play2d("Sound/coin.mp3");
        std::thread movePlayerEndThread([&] {
            _booster->start();
            delete _booster;
            _booster=nullptr;
        });
        movePlayerEndThread.detach();
        return false;
    }
    if ((contact.getShapeA()->getBody()->getName() == "downBarrier"
         && contact.getShapeB()->getBody()->getName() == "booster")
            || (contact.getShapeB()->getBody()->getName() == "downBarrier"
                && contact.getShapeA()->getBody()->getName() == "booster"))
    {
        removeChild(_booster->sprite());
        delete _booster;
        _booster = nullptr;
        return false;
    }
    if (contact.getShapeA()->getBody()->getName() == "player"
            && contact.getShapeB()->getBody()->getName() == "coin")
    {
        AudioEngine::play2d("Sound/coin.mp3");
        _coin.remove(contact.getShapeB()->getBody());
        return false;
    }
    if (contact.getShapeB()->getBody()->getName() == "player"
            && contact.getShapeA()->getBody()->getName() == "coin")
    {
        AudioEngine::play2d("Sound/coin.mp3");
        _coin.remove(contact.getShapeA()->getBody());
        return false;
    }
    return true;

}

void GameScene::continueGame()
{
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    this->resume();
    delete _pauseMenu;
    _pauseMutex.unlock();
    _coin.resume();
    _meteorites.resume();
    if(_booster!=nullptr)
        _booster->resume();
}


void GameScene::restartGame()
{
    _coin.setCountCoin(0);
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    this->resume();
    this->removeChild(_scoreLabel);
    _complexity = 1;
    initScore();
    _player._sprite->setPosition(cocos2d::Vec2(540, 400));
    delete _loseMenu;
    if (_booster!=nullptr)
    {
        delete _booster;
        _booster = nullptr;
    }
}
