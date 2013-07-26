//
//  CCJump.cpp
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#include "CCJump.h"
void CCJump::setDecrease(float d)
{
    mDecrease=d;
}
void CCJump::setAngle(float d)
{
    mAngle=d;
    mChanged=true;
}
void CCJump::setPower(float d)
{
    mPower=d;
    mChanged=true;
}
void CCJump::setGravity(float d)
{
    mG=d;
}


void CCJump::setListener(cocos2d::CCJumpListener *listener)
{
    mListener=listener;
}
CCJump* CCJump::create(float angle,float power,float g,float yPosition,float decrease)
{
    
    CCJump *pJumpBy = new CCJump;
    pJumpBy->initWithParam(angle,power,g,yPosition,decrease);
    pJumpBy->autorelease();
    
    return pJumpBy;
}
void CCJump::step(float dt)
{
    if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += dt*10;
    }
    this->update(m_elapsed);
    //m_elapsed += dt;
}
bool CCJump::initWithParam(float angle,float power,float g,float yPosition,float decrease)
{
    allowRot=1;
    mListener=NULL;
    mDecrease=decrease;
    CCActionInterval::initWithDuration(10);
    mOrginY=yPosition;
    mDecrease=decrease;
    mG=g;
    mPower=power;
    mAngle=angle;
    
    mChanged=true;
    
    
    return true;
}
void CCJump::setAllowRot(int d)
{
    rotate=m_pTarget->getRotation();
    allowRot=d;
}
CCObject* CCJump::copyWithZone(CCZone *pZone)
{
    mRemT=0;
    deltaT=0;
    CCZone* pNewZone = NULL;
    CCJump* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCJump*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCJump();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithParam(mAngle,mPower, mG,mOrginY);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJump::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    mOrginY=pTarget->getPositionY();
    //m_previousPos = m_startPosition = pTarget->getPosition();
    // rotBy=CCRotateBy::create(100/mPower,mAngle);
    
    //m_pTarget->runAction(CCRepeatForever::create(rotBy));
}
bool CCJump::isDone()
{
    return false;
}
void CCJump::reset()
{
    m_elapsed=0;
    
    float rt=mAngle*3.14/180;
    mXPower=mPower*cos(rt);
    mYPower=mPower*sin(rt);
    
    
    mRotate=abs(mXPower)/10;
    mPower*=mDecrease;
    mChanged=false;
    remX=m_pTarget->getPositionX();
    rotate=m_pTarget->getRotation();
    
    if(mPower<1&&mListener!=NULL)
    {
        mListener->onJump(1);
    }
}

void CCJump::update(float t)
{
    // parabolic jump (since v0.8.2)
    if(mRemT!=0)
        deltaT=t-mRemT;
    mRemT=t;
    if (m_pTarget)
    {
        CCLog("%f______",t);
        if(mChanged)
        {
            reset();
        }
        
        float ty=mYPower*t-mG*t*t/2+mOrginY;
        float tx=abs(mXPower*.8)*m_elapsed+remX;
        
        if(ty<0)
        {
            ty=0;
            // mChanged=true;
            mOrginY=0;
            mPower=abs(mPower);
            
            
            reset();
            
        }
        // CCLog("time%f",ty);
        
        
        
        
        m_pTarget->setPosition(ccp(tx,ty));
        m_pTarget->setRotation(mRotate*deltaT*3*allowRot+m_pTarget->getRotation());
        
    }
}

CCActionInterval* CCJump::reverse(void)
{
    return CCJump::create(-mAngle, -mPower,mG);
}