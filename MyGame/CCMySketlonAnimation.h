//
//  CCMySketlonAnimation.h
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#ifndef MyGame_CCMySketlonAnimation_h
#define MyGame_CCMySketlonAnimation_h
#include "spine-cocos2dx.h"
#include "CCInteractiveObj.h"
#include "CCPoolObj.h"
using namespace spine;
class CCMySketlonAnimation:public CCSkeletonAnimation,public CCInteractiveObj
{
public:
    CCMySketlonAnimation(const char* skeletonDataFile, const char* atlasFile,float scale=1);
    ~CCMySketlonAnimation();
    virtual void setInteractive(bool value);
    virtual bool getInteractive();
    
    virtual void setCollision(float value);
    virtual float getCollision();
    
    virtual void setDistance(float value);
    virtual float getDistance();
    
    virtual void setType(int type);
    virtual int getType();
    virtual void setIdle(bool value);
    virtual bool getIdle();

    static CCMySketlonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile,float scale=1);
protected:
    float mCollision;
    float mDistance;
    bool mInteractive;
    bool mIdle;
    bool mType;
};

#endif
