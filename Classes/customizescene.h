#ifndef CUSTOMIZESCENE_H
#define CUSTOMIZESCENE_H
#include <unistd.h>
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "menuscene.h"
#include "topbarbuttons.h"
#include "Rockets/rocketbase.h"
#include "Rockets/archiwrocket.h"
#include "Rockets/bulletrocket.h"
#include "Rockets/defenderrocket.h"

class CustomizeScene:public cocos2d::Scene
{
public:
    CustomizeScene();
    ~CustomizeScene();

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CustomizeScene);
    private:
     RocketBase *_rocket;
     cocos2d::Sprite *_backgroundSprite;
     cocos2d::Sprite *_active;
     cocos2d::Menu *_topBarMenu;
     cocos2d::Node *_bottomBarMenu;
     cocos2d::ui::Button** _colors;
     cocos2d::ui::Button** _rockets;    
     bool _bottomBarMenuStutusPrevious=false;


     void menuCoinsClicked(cocos2d::Ref *);
     void menuStoreClicked(cocos2d::Ref *);
     void backButtonClicked(cocos2d::Ref *);
     void changeColor(cocos2d::Ref *,int);
     void changeRocket(cocos2d::Ref *,int);
     void replaseBottomMenu(cocos2d::Ref*,bool);
};

#endif // CUSTOMIZESCENE_H
