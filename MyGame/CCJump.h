//
//  CCJump.h
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#ifndef MyGame_CCJump_h
#define MyGame_CCJump_h
#include "cocos2d.h"
USING_NS_CC;
class CC_DLL CCJump : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithParam(float angle, float power,float g=.98f,float yPosition=0,float decrease=.9f);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual bool isDone();
    virtual void step(float dt);
    void setListener(CCJumpListener* listener);
    void setDecrease(float d);
    void setAngle(float d);
    void setPower(float d);
    void setGravity(float d);
    void reset();
    void setAllowRot(int d);
public:
    /** creates the action */
    static CCJump* create(float angle, float power,float g=.98f,float yPosition=0,float decrease=.9f);
protected:
    float mAngle;
    float mPower;
    float mG;
    float mXPower;
    float mYPower;
    float mOrginY;
    float mDecrease;
    bool mChanged;
    float mRotate;
    float mRemT;
    float deltaT;
    CCJumpListener* mListener;
    int allowRot;
    float remX,rotate;
    CCRotateBy* rotBy;
};
#endif
