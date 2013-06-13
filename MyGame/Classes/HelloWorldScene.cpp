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
HelloWorld::HelloWorld():t(0),tDa(1),radius(45*3.14/180),power(20),dir(1)
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
        
        //CCSprite * test =CCSprite::create("HelloWorld.png",CCRectMake(0,0,1600,100000));
       
        //bg->setContentSize(CCSizeMake(1136,10000));
        //bg->setPosition(ccp(100, 0));
       // bg->setAnchorPoint(ccp(-.5,-.5));
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
    
    dis=sin(radius)*dis;
    if(dis<0)dir=-1;
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
    //this->setTouchEnabled(true);
    
    
    
    role = CCSkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas");
   
	role->setMix("walk", "jump", 0.2f);
	role->setMix("jump", "walk", 0.4f);
    
	role->setAnimation("walk", true);
    role->setTag(1000);
	// This shows how to setup animations to play back to back.
	//skeletonNode->addAnimation("jump", true);
	//skeletonNode->addAnimation("walk", true);
	//skeletonNode->addAnimation("jump", true);
    
	role->timeScale = 1.0f;
	role->debugBones = true;
    startY=role->getPositionY();
//	skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1),
//                                                                       CCFadeIn::create(1),
//                                                                       CCDelayTime::create(5),
//                                                                       NULL)));
    
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
    
    
    
    
    engine=PPEngine::create();
    engine->retain();
    engine->initWithMapFile("newMap.txt", this);
    
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("role.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items.plist");
    CCSpriteFrame * initFrame=getSpriteFrameByName("attack1_0.png");
    
    
    //role=CCRoleView::create();
    //role->type=1000;
    //role->initWithSpriteFrame(initFrame);
    role->setAnchorPoint(CCPointMake(.5f,.258f));
    
    
    role->runAction(CCRepeatForever::create(CCRotateBy::create(1.75f,720)));
    role->setZOrder(0);
    
   
    
    CCFollow *ff=CCFollow::create(role);

    this->runAction(ff);
    //CCMoveBy *mb=CCMoveBy::create(1,CCPointMake(1*100, 0));
   // CCRepeatForever *rep=CCRepeatForever::create(mb);
    
    
    //role->runAction(rep);
    
    this->addChild(role);

   
    this->schedule(schedule_selector(HelloWorld::update),600/1000);
    //role->runAction(CCRepeatForever::create(CCCallFunc::create(this, callfunc_selector(HelloWorld::enterFrame))));
    //this->setVertexZ(-100);
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
   
    
    //bg->setStartColor(tc);
    //bg->setEndColor(tc);
    bg->setColor(tc);
	engine->update(role->getPositionX(), role->getPositionY(),radius,bingo);
    
//    if(bingo)
//    {
//        
//        CCLog("%f_______________",radius*180/3.14);
//        power-=10;
//        if(power<0)power=0;
//    }
    //radius=atan2f(1,1);
    if(bingo||role->getPositionY()<0)
    {
        role->stopAllActions();
        role->setPositionY(0);
        t=0;
        dir=1;
        power/=1.2;
        startY=0;
        power=-power;
        
        if(radius<0)radius=-radius;
       // CCRepeatForever::create(CCRotateBy::create(1,30));
        role->runAction(CCRepeatForever::create(CCRotateBy::create(radius*180/3.14f,power*800)));
       // skeletonNode->runAction(CCRepeatForever::create(CCRotateBy::create(radius*180/3.14f,power*800)));
        this->schedule(schedule_selector(HelloWorld::update),500/1000);
        //CCDirector::sharedDirector()->getScheduler()->setTimeScale(.2f);
        //if(power<0)power=0;
        //radius=45*3.14/180;
    }
    
    float ty=dir*power*t*sin(radius)-.098*t*t/2;
    float tx=role->getPositionX()+abs(int(power*cos(radius)));
    role->setPositionX(tx);
    role->setPositionY(ty+startY);
    
   // skeletonNode->setPosition(ccp(tx,ty));
    
    CCString *tr=CCString::createWithFormat("%d米",int(role->getPositionY()/100));
    fenshu->setString(tr->getCString());
    fenshu->setPosition(role->getPosition());
    //float winHeight=CCDirector::sharedDirector()->getWinSize().height;
    
    //float ny=-role->getPositionY()-winHeight;
    //bg->setPositionY(ny);
    t+=tDa;
};
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
};

