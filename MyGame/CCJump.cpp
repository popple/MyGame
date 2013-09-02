//
//  CCJump.cpp
//  MyGame
//
//  Created by popplecui on 7/1/13.
//
//

#include "CCJump.h"

void CCJump::setListener(cocos2d::CCJumpListener *listener)
{
    _listener=listener;
}
CCJump* CCJump::create(float g)
{
    
    
    CCJump *pJumpBy = new CCJump;
    pJumpBy->initWithParam(g);
    pJumpBy->autorelease();
    
    return pJumpBy;
}

void CCJump::step(float dt)
{
    _times++;
    _totalTime+=dt;
    
    dt=_totalTime/_times;
    _et=dt;
    if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += dt*20;
    }
    this->update(m_elapsed);
     
    //m_elapsed += dt;
}
bool CCJump::initWithParam(float g)
{
    _times=0;
    _totalTime=0;
    enableRotation=0;
    this->g=g;
    CCActionInterval::initWithDuration(10);
    return true;
}


void CCJump::jump()
{
    power<0?_direct=-1:_direct=1;
    
    _start=false;
    m_bFirstTick=true;
    
    _remYPosition=m_pTarget->getPositionY();
    _remXPosition=m_pTarget->getPositionX();
    _remAngle=m_pTarget->getRotation();
    float jd=angle*3.14/180;
    _xPower=abs(power)*cos(jd);
    _yPower=abs(power*sin(jd))*_direct;
    power*=.95;
}

void CCJump::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _floorPosY=_remYPosition=pTarget->getPositionY();
}
bool CCJump::isDone()
{
    return false;
}

void CCJump::update(float t)
{
   // CCLog("%f",t);
    
    
    

    float ty=_yPower*t-g*t*t/2+_remYPosition;
    float tx=_xPower*.8*t+_remXPosition;
    
    
    int ta=_et*(90-angle)*abs(power)*.1*enableRotation;
    m_pTarget->setRotation(ta+m_pTarget->getRotation());
    m_pTarget->setPosition(tx, ty);
    if(m_pTarget->getPositionY()<=_floorPosY&&_start)
    {
        if(power<.1)m_pTarget->setPositionY(_floorPosY);
       // m_pTarget->setPositionY(_remYPosition);
        power=abs(power);
        jump();
        
        return;
    }
    _start=true;
}

