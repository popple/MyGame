//
//  CCMySketlonAnimation.cpp
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#include "CCMySketlonAnimation.h"
void CCMySketlonAnimation::setInteractive(bool value)
{
    mInteractive=value;
};
bool CCMySketlonAnimation::getInteractive()
{
    return mInteractive;
};
void CCMySketlonAnimation::setType(int type)
{
    mType=type;
}
int CCMySketlonAnimation::getType()
{
    return mType;
}
void CCMySketlonAnimation::setIdle(bool value)
{
    mIdle=value;
}
bool CCMySketlonAnimation::getIdle()
{
    return mIdle;
}
void CCMySketlonAnimation::setCollision(float value)
{
    
};
float CCMySketlonAnimation::getCollision()
{
    return mCollision;
};

CCMySketlonAnimation::CCMySketlonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale):CCSkeletonAnimation(skeletonDataFile, atlasFile, scale)
{
   
	//addAnimationState();
}
CCMySketlonAnimation::~CCMySketlonAnimation()
{
    
}

CCMySketlonAnimation* CCMySketlonAnimation::createWithFile (const char* skeletonDataFile, const char* atlasFile,float scale)
{
    CCMySketlonAnimation* node = new CCMySketlonAnimation (skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;

};
void CCMySketlonAnimation::setDistance(float value)
{
    mDistance=value;
};
float CCMySketlonAnimation::getDistance()
{
    return mDistance;
};