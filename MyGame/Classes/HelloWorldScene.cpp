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
#include "MovieEndAction.h"
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
HelloWorld::HelloWorld():tm(NULL){};
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
    float dis=ccpDistance(_lastPoint,_nowPoint)*.5;
    int angle=int(atan2f(tpy, tpx)*180/3.14);
    //反作用力
    if(tpy<0)dis=-dis;
    //CCLog("%f____%f",dis,angle);
    
    mRole->setRotation(360-angle+90);
    mRole->setAnimation("fly",false);
    //mRole->timeScale=.5f;
    CCJump* jp=(CCJump*)mRole->getActionByTag(1000);
    jp->power=dis;
    jp->angle=angle;
    jp->enableRotation=0;
    jp->jump();
    
    
}
void HelloWorld::timeOut(float d)
{
    CCJump* jp=(CCJump*)mRole->getActionByTag(1000);
    if(jp)
    {
       
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
    
    
    engine=PPEngine::create();
    engine->retain();
    engine->initWithMapFile("newMap.json",this);
    //创建主角
    mRole = CCSkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas");
    
    
    mRole->setAnimation("idle",true);
    
    mRole->setMix("idle", "fly",.1f);
    mRole->setMix("fly", "rotation",.1f);
    mRole->setMix("rotation", "fly",.1f);
    
    mRole->setMix("idle", "beHit",.1f);
     mRole->setMix("beHit", "idle",.1f);
    //mRole->set
    mRole->timeScale=1.5f;
    mRole->setTag(1000);
    mRole->retain();
   // mRole->setType;
    mRole->setPosition(ccp(0,0));
       
    
    
    this->addChild(mRole);
    
    
    
    //初始化背景层
    mBackGround=CCParallaxNode::create();
    
    
    mBackGround->retain();
    mSky=CCLayerColor::create(ccc4(80,120,250,255));
    mSky->retain();
    //
    
    this->schedule(schedule_selector(HelloWorld::update), 60/1000);
    
    //this->runAction(CCSequence::create(MovieEndAction::create("idle"),CCCallFuncN::create(mRole, SEL_CallFuncN(HelloWorld::movieEnd) )));
    //mRole->schedule(schedule_selector(HelloWorld::watchRole), 60/1000);
    //
        
    
   // CCSprite * sp=CCSprite::create("Icon.png", CCRectMake(0, 0, 200, 200));
    //sp->setContentSize(CCSizeMake(600,600));
    
    //mRole->addChild(sp);
    //GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT
    
    
    //test=UVSprite::create("Icon.png");
    //test->setContentSize(CCSizeMake(400,200));
    //this->addChild(test);
    CCJump* jp=CCJump::create(.98f);
    jp->startWithTarget(mRole);
    jp->setTag(1000);
    mRole->runAction(jp);
    
    jp->angle=30;
    jp->power=20;
    jp->jump();
    //makeAction();
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(.1);
    
    tm=CCTimer::timerWithTarget(this, schedule_selector(HelloWorld::delay),.1);
    tm->retain();
    slowy=false;
    return true;
};
void HelloWorld::onMovieEnd(cocos2d::CCNode *target)
{
    CCLog("get"); 
    CCSkeletonAnimation *mov= (CCSkeletonAnimation*)((GameObj*)target)->Objectview;
    string name=mov->states[0]->animation->name;
    
    if(strcmp(name.c_str(), "beHit")==0)
    {
        mov->setAnimation("idle", true);
    }
    target->unscheduleAllSelectors();
}
void HelloWorld::delay()
{
   //CCDirector::sharedDirector()->getScheduler()->setTimeScale(1);
    CCLog("huanyuan");
    //tm->release();
    slowy=false;
}
void HelloWorld::update(float dt)
{
   
    
    //test->setTextureCoords(CCRectMake(rand()*100, rand()*100, 20, 290));
    float t=mRole->states[0]->time;
    float s=mRole->states[0]->animation->duration;
    string name=mRole->states[0]->animation->name;
    if(t>=s&&strcmp(name.c_str(), "fly")==0)
    {
       // CCLog("动作播放完毕%s",name.c_str());
        CCJump*jp=(CCJump*)mRole->getActionByTag(1000);
        mRole->setAnimation("rotation",false);
        jp->enableRotation=1;
        //_listener->onPlayEvent(mSkeletonRole, name);
    }

    
    this->setPosition(CCPointMake(-mRole->getPositionX()+engine->camOffsetX,-mRole->getPositionY()+engine->camOffsetY));

    
    engine->update(mRole->getPositionX(), mRole->getPositionY());
    if(engine->re.isCollision)
    {
        CCJump *jp=(CCJump*)mRole->getActionByTag(1000);
        if(jp->power<0)jp->power=-jp->power;
        jp->angle= engine->re.radius;
        jp->jump();
        (engine->re.target)->play("beHit",false);
        engine->re.target->addEventListener(this,callfuncN_selector(HelloWorld::onMovieEnd));
        jp->power*=engine->re.target->power;
        
        
      //  CCDirector::sharedDirector()->getScheduler()->setTimeScale(.01);
        
        //tm->retain();
        slowy=true;
        //_collistionObj->Objectview->setActionManager(cocos2d::CCActionManager *actionManager)
        //CCCallFuncN::create(this,ca)
        CCLog("kaishi减速");
    }
    if(slowy)
    tm->update(dt);
};

