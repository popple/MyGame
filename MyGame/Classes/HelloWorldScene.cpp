#include "HelloWorldScene.h"
#include "String.h"
#include "stdlib.h"
//#include "tools.h"
USING_NS_CC;

#include "RoleView.h"
#include "PPMapData.h"
#include "PPUnitPool.h"
#include "PPEngine.h"
#include "Json.h"
#include "value.h"
#include "reader.h"
#include "writer.h"
#include "global.h"
#include "Trigger.h"
#include "spine-cocos2dx.h"
using namespace spine;
CCLayerColor *HelloWorld::bg=NULL;
HelloWorld::HelloWorld():t(0),tDa(1),radius(45*3.14/180),power(0),dir(1)
{
	
}
HelloWorld::~HelloWorld(){}
CCScene* HelloWorld::scene()
{
    
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        
        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
       
        CC_BREAK_IF(!layer);
        bg=CCLayerColor::create(ccc4(3,20,0,255));
        
        scene->addChild(bg);
       // scene->addChild(test);
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
};
void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
};
void HelloWorld::onExit()
{
    CCLayer::onExit();
};

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
   // power+=10;
    
};
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    p2=pTouch->getLocation();
    t=0;
    startY=role->getPositionY();
    float tx=powf((p2.x-p1.x),2);
    float ty=powf((p2.y-p1.y),2);
    
    int dis=int(ceil(sqrt(tx+ty)));
    radius=atan2f(p2.y-p1.y, p2.x-p1.x);
    
    if(radius>0)
    {
        dir=1;
        
    }else{
        dir=-1;
        //p1=p2;
    }
    if(radius<0)radius=-radius;
//    dis=sin(radius)*dis;
//    if(dis<0)dir=-1;
    power=dis/5;
    role->stopAllActions();
    role->runAction(CCRepeatForever::create(CCRotateBy::create(abs(int(radius*180/3.14f)),power*600)));
    CCLog("%d__%f",dis,radius*180/3.14);
}
void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
};
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    p1=pTouch->getLocation();
   // power+=10;
    return true;
   
};
// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    
    role = CCSkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas");
   
	role->setMix("walk", "jump", 0.2f);
	role->setMix("jump", "walk", 0.4f);
    
	role->setAnimation("walk", true);
    role->setTag(1000);
    
	role->timeScale = 1.0f;
	role->debugBones = true;
    startY=role->getPositionY();

    
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	role->setPosition(ccp(windowSize.width / 2, 20));
    role->setScale(.6f);
	//addChild(role);

    role->retain();
    
    
    fenshu=CCTextFieldTTF::create();
    fenshu->retain();
    CCSize win=CCDirector::sharedDirector()->getWinSize();
    fenshu->setPosition(CCPointMake(win.width/2,win.height/2));
    fenshu->setFontSize(100);
    fenshu->setOpacity(40);
    this->addChild(fenshu,1000);
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items.plist");

    
    engine=PPEngine::create();
    engine->retain();
    engine->initWithMapFile("newMap.json", this);
    
    
        

    role->setAnchorPoint(CCPointMake(.5f,.258f));
    //role->setPosition(ccp(500,0));
    
    //role->runAction(CCRepeatForever::create(CCRotateBy::create(1.75f,720)));
    role->setZOrder(0);
    
   
    
    CCFollow *ff=CCFollow::create(role);

    this->runAction(ff);

    this->addChild(role);

    
    this->schedule(schedule_selector(HelloWorld::update),600/1000);
       return true;
};
void HelloWorld::enterFrame(cocos2d::CCObject *obj)
{
    
};
void HelloWorld::update(float dt)
{
    
    bool bingo=false;
    this->sortAllChildren();
    
    float p=1-role->getPositionY()/100000.0;
    
    
    ccColor3B tc=ccc3(255,0,0);
    
    if(p<0)p=0;
        tc.r=(bgColor.color2.r-bgColor.color1.r)*p;
        tc.g=(bgColor.color2.g-bgColor.color1.g)*p;
        tc.b=(bgColor.color2.b-bgColor.color1.b)*p;
   

    bg->setColor(tc);
	engine->update(role->getPositionX(), role->getPositionY(),radius,bingo);

    if(bingo||role->getPositionY()<0)
    {
        role->stopAllActions();
        role->setPositionY(0);
        t=0;
        dir=1;
        power/=1.2;
        startY=0;
        //power=abs(power);
        
        //if(radius<0)radius=-radius;
       
        role->runAction(CCRepeatForever::create(CCRotateBy::create(radius*180/3.14f,power*800)));
       
        this->schedule(schedule_selector(HelloWorld::update),500/1000);
       
    }
    
    float ty=dir*power*t*sin(radius)-.098*t*t/2;
    float tx=role->getPositionX()+abs(int(power*cos(radius)));
    role->setPositionX(tx);
    role->setPositionY(ty+startY);
       
    CCString *tr=CCString::createWithFormat("%d米",int(role->getPositionX()/100));
    fenshu->setString(tr->getCString());
    fenshu->setPosition(role->getPosition());
        t+=tDa;
};
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
};

