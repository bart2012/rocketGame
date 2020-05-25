#include "customizescene.h"

extern MenuScene *mainMenu;

CustomizeScene::CustomizeScene()
{
    _backgroundSprite = cocos2d::Sprite::create("customize/bg.png");
    _backgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
}
cocos2d::Scene* CustomizeScene::createScene(){
    return CustomizeScene::create();
}
bool CustomizeScene::init(){
    if ( !Scene::init() )
    {
        return false;
    }
    short width=1080;short height=1920;
    schedule(CC_SCHEDULE_SELECTOR(CustomizeScene::update));
     this->addChild(_backgroundSprite);

    auto coinsItem=cocos2d::MenuItemImage::create("startmenu/coins.png","startmenu/coins.png"
                                                   ,CC_CALLBACK_0(TopBarButtons::menuCoinsClicked,this));
    auto storeItem=cocos2d::MenuItemImage::create("startmenu/store.png","startmenu/store.png"
                                                   ,CC_CALLBACK_0(TopBarButtons::menuStoreClicked,this));
    auto backItem=cocos2d::MenuItemImage::create("setting/back.png","setting/back.png"
                                                   ,CC_CALLBACK_1(CustomizeScene::backButtonClicked,this));

    backItem->setPosition(cocos2d::Point(100,height-100));
    coinsItem->setPosition(cocos2d::Point(width/ 2,height-100));
    storeItem->setPosition(cocos2d::Point(width-100,height-100));

    _topBarMenu = cocos2d::Menu::create(backItem,coinsItem,storeItem,NULL);
    _topBarMenu->setPosition(cocos2d::Point(0,0));
    this->addChild(_topBarMenu);

    //-----------------------------------------------
   auto _rocketPlatform= cocos2d::Sprite::create("customize/Group.png");
   _rocketPlatform->setPosition(cocos2d::Point(width/2,
                                    _rocketPlatform->getBoundingBox().size.height/2+270));
   this->addChild(_rocketPlatform);
   //------------------------------------------------

 mainMenu->_rocket->getSprite()->setPosition(cocos2d::Vec2(1080/2,
                                         mainMenu->_rocket->getSprite()->getBoundingBox().size.height/2+470));
 this->addChild(mainMenu->_rocket->getSprite());


   //----------------------------------------------
  _bottomBarMenu = cocos2d::Node::create();
  auto bottomBg = cocos2d::Sprite::create("customize/color_bg.png");
  bottomBg->setPosition(cocos2d::Vec2(width/2,bottomBg->getBoundingBox().size.height/2));
  _bottomBarMenu->addChild(bottomBg);

  _colors= new cocos2d::ui::Button* [4];
  for (int i=0;i<4;i++){
  _colors[i] = cocos2d::ui::Button::create(std::string("customize/Ellipse")+std::to_string(i)+".png",std::string("customize/Ellipse")+std::to_string(i)+".png");
  _colors[i]->setPosition(cocos2d::Vec2(_colors[i]->getBoundingBox().size.width/2+132+i*218,
                                        _colors[i]->getBoundingBox().size.height/2+32));
  _colors[i]->addClickEventListener(CC_CALLBACK_1(CustomizeScene::changeColor,this,i));
   _bottomBarMenu->addChild(_colors[i]);
  }
  _active= cocos2d::Sprite::create("customize/active.png");
  _active->setPosition(cocos2d::Point(_active->getBoundingBox().size.width/2+132+mainMenu->_rocket->getColor()*218,
                                      _active->getBoundingBox().size.height/2+32));
  _active->setLocalZOrder(10);
   _bottomBarMenu->addChild(_active);
   this->addChild(_bottomBarMenu);
  //---------------------------------------------
  auto colorChoose=cocos2d::ui::Button::create("customize/Color_choose.png","customize/Color_choose.png");
  auto rocketChoose=cocos2d::ui::Button::create("customize/Rocket_choose.png","customize/Rocket_choose.png");

  colorChoose->setPosition(cocos2d::Point(width/8, height/2+colorChoose->getBoundingBox().size.height));
  rocketChoose->setPosition(cocos2d::Point(width/8,height/2-rocketChoose->getBoundingBox().size.height/2));

  rocketChoose->addClickEventListener(CC_CALLBACK_1(CustomizeScene::replaseBottomMenu,this,true));
  colorChoose->addClickEventListener(CC_CALLBACK_1(CustomizeScene::replaseBottomMenu,this,false));
  this->addChild(colorChoose);
  this->addChild(rocketChoose);

    return true;
}

void CustomizeScene::changeColor(cocos2d::Ref *,int i){
    this->removeChild(mainMenu->_rocket->getSprite());
    mainMenu->_rocket->setColor(RocketBase::RocketColor(i));
    mainMenu->_rocket->getSprite()->setPosition(cocos2d::Vec2(1080/2,
                                            mainMenu->_rocket->getSprite()->getBoundingBox().size.height/2+470));
    this->addChild(mainMenu->_rocket->getSprite());
    //----------------------------------------------
    _active->runAction(cocos2d::MoveTo::create(0.1,cocos2d::Point(_active->getBoundingBox().size.width/2+132+i*218,
                                        _active->getBoundingBox().size.height/2+32)));

}
void CustomizeScene::changeRocket(cocos2d::Ref *, int i){
    this->removeChild(mainMenu->_rocket->getSprite());
    RocketBase *newRocket;
    switch (i) {
    case 0:newRocket= new ArchiWRocket();
        newRocket->setType(RocketBase::Type::ArchiW);
        break;
    case 1:newRocket= new BulletRocket();
        newRocket->setType(RocketBase::Type::Defender);
        break;
    case 2:newRocket= new DefenderRocket();
        newRocket->setType(RocketBase::Type::Bullet);
        break;
    }
    newRocket->setColor(mainMenu->_rocket->getColor());
    delete mainMenu->_rocket;
    mainMenu->_rocket=newRocket;
    mainMenu->_rocket->getSprite()->setPosition(cocos2d::Vec2(1080/2,
                                                mainMenu->_rocket->getSprite()->getBoundingBox().size.height/2+470));
    _active->runAction(cocos2d::MoveTo::create(0.1,cocos2d::Point(_active->getBoundingBox().size.width/2+132+i*290,
                                        _active->getBoundingBox().size.height/2+32)));
    this->addChild(mainMenu->_rocket->getSprite());
}
void CustomizeScene::backButtonClicked(cocos2d::Ref *){
    CCLOG("BACk");
    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInL::create(0.6,(cocos2d::Scene*)mainMenu));
}
void CustomizeScene::replaseBottomMenu(cocos2d::Ref*, bool type){
    if(_bottomBarMenuStutusPrevious==type)return;

        short height=1080;
        auto delay = cocos2d::DelayTime::create(0.3);

        auto seq = cocos2d::Sequence::create(cocos2d::MoveTo::create(0.0,cocos2d::Point(0,-250)), delay,
                                             cocos2d::MoveTo::create(0.1,cocos2d::Point(0,0)), nullptr);
            _bottomBarMenu->runAction(seq);



        if (type){

            for(int i=0;i<4;i++)
            _bottomBarMenu->removeChild(_colors[i]);
            _rockets=new cocos2d::ui::Button* [4];
            for (int i=0;i<3;i++){
               _rockets[i] = cocos2d::ui::Button::create(std::string("customize/Frame")+std::to_string(i)+".png",std::string("customize/Frame")+std::to_string(i)+".png");
               _rockets[i]->setPosition(cocos2d::Vec2(_rockets[i]->getBoundingBox().size.width/2+132+i*290,
                                                       _rockets[i]->getBoundingBox().size.height/2+32));
               _rockets[i]->addClickEventListener(CC_CALLBACK_1(CustomizeScene::changeRocket,this,i));
               _bottomBarMenu->addChild(_rockets[i]);
            }

             _active->setPosition(cocos2d::Point(_active->getBoundingBox().size.width/2+132+0*290,
                                                 _active->getBoundingBox().size.height/2+32));

        }
        else{
            for(int i=0;i<3;i++)
            _bottomBarMenu->removeChild(_rockets[i]);
            for(int i=0;i<4;i++){
                    _colors[i] = cocos2d::ui::Button::create(std::string("customize/Ellipse")+std::to_string(i)+".png",std::string("customize/Ellipse")+std::to_string(i)+".png");
                    _colors[i]->setPosition(cocos2d::Vec2(_colors[i]->getBoundingBox().size.width/2+132+i*218,
                                                         _colors[i]->getBoundingBox().size.height/2+32));
                    _colors[i]->addClickEventListener(CC_CALLBACK_1(CustomizeScene::changeColor,this,i));
                    _bottomBarMenu->addChild(_colors[i]);
            }
                    _active->setPosition(cocos2d::Point(_active->getBoundingBox().size.width/2+132+mainMenu->_rocket->getColor()*218,
                                                        _active->getBoundingBox().size.height/2+32));

        }
        _bottomBarMenuStutusPrevious=type;


}

CustomizeScene::~CustomizeScene()
{

}
