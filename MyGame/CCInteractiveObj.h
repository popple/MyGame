//
//  CCInteractiveObj.h
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#ifndef MyGame_CCInteractiveObj_h
#define MyGame_CCInteractiveObj_h
#include "cocos2d.h"
USING_NS_CC;
class CCInteractiveObj:public CCNode
{
public:
    virtual void setInteractive(bool value)=0;
    virtual bool getInteractive()=0;
    
    virtual void setCollision(float value)=0;
    virtual float getCollision()=0;
    
    virtual void setDistance(float value)=0;
    virtual float getDistance()=0;
    
    virtual void setTypes(int type)=0;
    virtual int getTypes()=0;
    virtual void setIdle(bool value)=0;
    virtual bool getIdle()=0;
   
    
};


#endif
