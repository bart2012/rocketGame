#include "menuscene.h"
MenuScene::MenuScene(){
_backgroundSprite = cocos2d::Sprite::create("startmenu/bg.png");
_backgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
}
cocos2d::Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
     short width=1080;short height=1920;
    schedule(CC_SCHEDULE_SELECTOR(MenuScene::update));
    this->addChild(_backgroundSprite);


    auto settingItem=cocos2d::MenuItemImage::create("startmenu/setting.png","startmenu/setting.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuSettingClicked,this));
    auto coinsItem=cocos2d::MenuItemImage::create("startmenu/coins.png","startmenu/coins.png"
                                                   ,CC_CALLBACK_0(TopBarButtons::menuCoinsClicked,this));
    auto storeItem=cocos2d::MenuItemImage::create("startmenu/store.png","startmenu/store.png"
                                                   ,CC_CALLBACK_0(TopBarButtons::menuStoreClicked,this));
    auto playItem=cocos2d::MenuItemImage::create("startmenu/buttonstart.png","startmenu/buttonstart_clicked.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuStartClicked,this));
    auto customizeItem=cocos2d::MenuItemImage::create("startmenu/buttoncustomize.png","startmenu/buttoncustomize_clicked.png"
                                                   ,CC_CALLBACK_1(MenuScene::menuCustomizeClicked,this));

    settingItem->setPosition(cocos2d::Point(100,height-100));
    coinsItem->setPosition(cocos2d::Point(width/ 2,height-100));
    storeItem->setPosition(cocos2d::Point(width-100,height-100));
    playItem->setPosition(cocos2d::Point(width/2,615));
    customizeItem->setPosition(cocos2d::Point(width/ 2,320));

    menu = cocos2d::Menu::create(settingItem,coinsItem,storeItem,playItem,customizeItem,NULL);
    menu->setPosition(cocos2d::Point(0,0));
    this->addChild(menu);

    return true;
}

void MenuScene::menuSettingClicked(cocos2d::Ref * ){
 CCLOG("Settings");short width=1080;short height=1920;
  menu->setEnabled(false);
  auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](cocos2d::Touch* touch,cocos2d::Event* event){
            //if(!backgroundSprite->getBoundingBox().containsPoint(this->convertToNodeSpace( touch->getLocation() )))
              this->backButtonClicked(this);
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

 _settingsMenu = cocos2d::Node::create();
 auto backgroundSprite = cocos2d::Sprite::create("setting/settings_bg.png");
 auto backButton=cocos2d::ui::Button::create("setting/back.png","setting/back.png");
 backButton->addClickEventListener( CC_CALLBACK_1(MenuScene::backButtonClicked,this));
 auto musicCheckbox = cocos2d::ui::CheckBox::create( "setting/music off.png","setting/music active.png");
 musicCheckbox->setSelected(true);
 musicCheckbox->addEventListener(musicCheckboxClicked);
 auto soundCheckbox = cocos2d::ui::CheckBox::create("setting/sound off.png","setting/sound active.png");
 soundCheckbox->setSelected(true);
 soundCheckbox->addEventListener(soundCheckboxCliced);

 backgroundSprite->setPosition(cocos2d::Point(width/2,height));
 backButton->setPosition(cocos2d::Point(width/2-backgroundSprite->getBoundingBox().size.width/3
                                        ,height+backgroundSprite->getBoundingBox().size.height/3));
 musicCheckbox->setPosition(cocos2d::Point(width/2+backgroundSprite->getBoundingBox().size.width/4
                                           ,height-backgroundSprite->getBoundingBox().size.height/8));
 soundCheckbox->setPosition(cocos2d::Point(width/2-backgroundSprite->getBoundingBox().size.width/4
                                           ,height-backgroundSprite->getBoundingBox().size.height/8));
 _settingsMenu->addChild(backgroundSprite);
 _settingsMenu->addChild(backButton);
 _settingsMenu->addChild(musicCheckbox);
 _settingsMenu->addChild(soundCheckbox);
 this->addChild(_settingsMenu);
 auto moveTo = cocos2d::MoveTo::create(0.5,cocos2d::Point(0,-height/2));
 _settingsMenu->runAction(moveTo);


}

void MenuScene::menuStartClicked(cocos2d::Ref * ){
cocos2d::Scene *scene = GameScene::createScene();
cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInB::create(1, scene) );

}
void MenuScene::menuCustomizeClicked(cocos2d::Ref * ){
 CCLOG("Customize");
 cocos2d::Scene *scene = CustomizeScene::createScene();
 cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInR::create(0.6,scene));
}
void MenuScene::backButtonClicked(cocos2d::Ref *){
 CCLOG("Back");
short height=1920;
 auto moveTo = cocos2d::MoveTo::create(0.3,cocos2d::Point(0,height/2));
 _settingsMenu->runAction(moveTo);

 menu->setEnabled(true);
}
void MenuScene::musicCheckboxClicked(cocos2d::ui::CheckBox::Ref*, cocos2d::ui::CheckBox::EventType type ){
    switch(type){
        case cocos2d::ui::CheckBox::EventType::SELECTED:
          CCLOG("MUSIC ON");
        break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
        CCLOG("MUSIC OFF");
      break;
    }
}
void MenuScene::soundCheckboxCliced(cocos2d::ui::CheckBox::Ref* , cocos2d::ui::CheckBox::EventType type ){
    switch(type){
        case cocos2d::ui::CheckBox::EventType::SELECTED:
          CCLOG("SOUND ON");
        break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
        CCLOG("SOUND OFF");
      break;
    }
}
MenuScene::~MenuScene(){

}


