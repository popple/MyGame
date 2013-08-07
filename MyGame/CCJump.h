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
    float g;
    float power;
    int enableRotation;
    float angle;
    /** initializes the action */
    bool initWithParam(float g);
    
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    
    virtual bool isDone();
    virtual void step(float dt);
    void setListener(CCJumpListener* listener);

    
    
    void jump();
    /** creates the action */
    static CCJump* create(float g=.98f);


    
private:
    float _xPower,_yPower;
    float _times;
    float _totalTime;
    float _remYPosition;
    float _remXPosition;
    float _floorPosY;
    float _remAngle;
    bool _start;
    int _direct;
    CCJumpListener* _listener;
};
#endif
