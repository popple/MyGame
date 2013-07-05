//
//  CCPoolObj.h
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#ifndef MyGame_CCPoolObj_h
#define MyGame_CCPoolObj_h
#include "cocos2d.h"
USING_NS_CC;
class CCPoolObj:public CCObject
{
public:
    virtual void setType(int type)=0;
    virtual int getType()=0;
    virtual void setIdle(bool value)=0;
    virtual bool getIdle()=0;
};

#endif
