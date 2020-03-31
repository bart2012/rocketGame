#include "gamescene.h"
cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}
bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //cocos2d::EventListenerCustom *l = cocos2d::EventListenerCustom::create();
    schedule(CC_SCHEDULE_SELECTOR(GameScene::update));
    _background.addToScene(this);
    _player.addToScene(this);
    //auto q = cocos2d::EventListenerTouchOneByOne::create();
    //q->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event){
//cocos2d::Director::getInstance()->getTextureCache()->removeTexture(_t);
//_t = cocos2d::Director::getInstance()->getTextureCache()->addImage("PNG/coin.png");
//cocos2d::Director::getInstance()->pause();
     //   a();
     //   return true; // if you are consuming it
    //};
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(q, this);
    return true;
}

void GameScene::update(float)
{
    _background.update(this);
}
