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
#include "SpringObject.h"
#include "CCJump.h"
#include "CCSkeletonAnimation.h"
using namespace spine;


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
        layer->belongScene(scene);
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
};
HelloWorld::HelloWorld(){};
HelloWorld::~HelloWorld(){};
void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
};
void HelloWorld::belongScene(cocos2d::CCScene *scene)
{
    _scene=scene;
    _scene->retain();
    
    if(mSky->getParent()!=_scene)
    {
        _scene->addChild(mSky);
    }
    if(mBackGround->getParent()!=_scene)
    {
        _scene->addChild(mBackGround);
    }
    
}
void HelloWorld::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
};

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    _lastPoint=pTouch->getLocation();
    return  true;
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    _nowPoint=pTouch->getLocation();
    float tpx=_nowPoint.x-_lastPoint.x;
    float tpy=_nowPoint.y-_lastPoint.y;
    float dis=ccpDistance(_lastPoint,_nowPoint);
    int angle=int(atan2f(tpy, tpx)*180/3.14);
    //反作用力
    if(tpy<0)dis=-dis;
    CCLog("%f____%f",dis,angle);
    
    mRole->setRotation(360-angle+90);
    mRole->setAnimation("fly",false);
    //mRole->timeScale=.5f;
    CCJump* jp=(CCJump*)mRole->getActionByTag(1000);
    jp->initWithParam(abs(angle),dis,.98f,mRole->getPositionY());
    jp->setAllowRot(0);
    if(tm)tm->release();
    tm=CCTimer::timerWithTarget(this, schedule_selector(HelloWorld::timeOut));
    tm->setInterval(.6f);
    tm->retain();
}
void HelloWorld::timeOut(float d)
{
    CCJump* jp=(CCJump*)mRole->getActionByTag(1000);
    if(jp)
    {
        jp->setAllowRot(1);
        tm->release();
        tm=NULL;
    }
    
}

void HelloWorld::onJump(int state)
{
    if(state==1)
    {
        //do sth;
        CCLog("over,do sth");
        mRole->setAnimation("run",true);
    }
}
void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
};

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    //创建主角
    mRole = CCSkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas");
    mRole->setAnimation("idle",true);
    //mRole->set
    mRole->timeScale=.3f;
    mRole->setTag(1000);
    mRole->retain();
   // mRole->setType;
    mRole->setPosition(ccp(0,0));
    CCFollow *follow=CCFollow::create(mRole);
    this->runAction(follow);
    
    
    
    this->addChild(mRole);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items.plist");
    //初始化背景层
    mBackGround=CCParallaxNode::create();
    
    
    mBackGround->retain();
    mSky=CCLayerColor::create(ccc4(80,120,250,255));
    mSky->retain();
    //
    engine=PPEngine::create();
    engine->retain();
    engine->initWithMapFile("newMap.json",this);
    this->schedule(schedule_selector(HelloWorld::update), 60/1000);
    
       
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(.2f);
    
    
    
    CCJump* jp=CCJump::create(30, 100, .98f);
    jp->startWithTarget(mRole);
    jp->setTag(1000);
    mRole->runAction(jp);
    
 
    //makeAction();
    return true;
};

void HelloWorld::update(float dt)
{
    CCLog("%s,%f",mRole->states[0]->animation->name,mRole->states[0]->animation->duration);
//    if(mRole->getPositionY()<=0)
//    {
//        CCJump* tm= (CCJump*)mRole->getActionByTag(1000);
//        tm->initWithParam(30, 20);
//    }
    //mRole->setPositionX(sObject->x+mRole->getPositionX());
    //mRole->setPositionY(sObject->y);
    engine->update(mRole->getPositionX(), mRole->getPositionY(), _angle,_bingo);
    
};

