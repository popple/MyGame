#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "RoleView.h"
#include "PPEngine.h"
#include <spine/spine-cocos2dx.h>
#include "SimpleAudioEngine.h"

struct BgColor
{
    ccColor3B color1=ccc3(3,20,0);
    ccColor3B color2=ccc3(80,120,250);
    ccColor3B color3=ccc3(0,0,0);
    
    
};
class HelloWorld : public cocos2d::CCLayer
{
public:
    float t;
    float tDa;
    float radius;
    int power;
    BgColor bgColor;
    CCLabelTTF *fenshu;
    static CCLayerColor *bg;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    PPEngine *engine;
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void update(float dt);
	void enterFrame(CCObject* obj);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
protected:
    CCRoleView* role;
};
#endif