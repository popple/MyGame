//
//  ccUVAction.h
//  MyGame
//
//  Created by popplecui on 9/3/13.
//
//

#ifndef MyGame_ccUVAction_h
#define MyGame_ccUVAction_h

#include "cocos2d.h"
USING_NS_CC;
class CC_DLL ccUVAction : public CCActionInterval
{
public:
        /** initializes the action */
    bool initWithParam(float uspd,float vspd);
    
    
    virtual void startWithTarget(CCNode *pTarget);

    

    virtual bool isDone();
    virtual void step(float dt);

    
    
    
   
    /** creates the action */
    static ccUVAction* create(float uspd,float vspd);
    
    
    
private:
    float _uspd;
    float _vspd;
};

#endif
