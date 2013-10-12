#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "RoleView.h"
#include "PPEngine.h"
#include <spine/spine-cocos2dx.h>
#include "SimpleAudioEngine.h"
#include "spine-cocos2dx.h"

#include "GameObj.h"

typedef int motionType;

class HelloWorld : public cocos2d::CCLayer,CCJumpListener
{
private:
    CCPoint _lastPoint;
    CCPoint _nowPoint;
    CCScene* _scene;
    float _tick;
    float _tStep;
    float _collisionRadius;
    int _direct;
    float _startY;
    
    bool _bingo;
    float _angle;
    
    GameObj* _collistionObj;
public:
    
    virtual void onJump(int state);
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
  
    
    static cocos2d::CCScene* scene();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    // optional
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    void makeAction();
    void check(CCNode*sender,void*data);
	void update(float dt);
    void timeOut(float d);
    void watchRole(float d);
    HelloWorld();
    ~HelloWorld();
    
    void delay();
    void onMovieEnd(CCNode* target);
    void belongScene(CCScene* scene);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
protected:
    CCTimer *tm;
    motionType mType;
    int mPower;
    int angle;
    float speed;
    
    
    CCSkeletonAnimation * mRole;
    //天空层
    CCLayerColor *mSky;
    //背景层
    CCParallaxNode* mBackGround;
    //引擎
    PPEngine* engine;
    bool slowy;
    
    
    
};
#endif