//
//  ccUVAction.cpp
//  MyGame
//
//  Created by popplecui on 9/3/13.
//
//

#include "ccUVAction.h"
ccUVAction* ccUVAction::create(float uspd,float vspd)
{
    ccUVAction* tem=new ccUVAction();
    if(tem&&tem->initWithParam(uspd,vspd))
    {
        tem->autorelease();
        return tem;
    }
    return NULL;
}
bool ccUVAction::initWithParam(float uspd, float vspd)
{
    _uspd=uspd;
    _vspd=vspd;
    return true;
}
void ccUVAction::step(float dt)
{
    CCSprite* sp=(CCSprite*)m_pTarget;
    
    CCRect rect= sp->getTextureRect();
    
    
    
    
    float ox=_uspd*dt;
    float oy=_vspd*dt;
    
    int tx=rect.origin.x+ox;
    int ty=rect.origin.y+oy;
    
    
    //int rx=tx%((int)rect.size.width);
    //int ry=ty%((int)rect.size.height);
    if(tx>128)
    {
        rect.origin.x=rect.origin.x-128+ox;
    }
    else
    {
        rect.origin.x+=ox;
    }
    if(ty>128)
    {
        rect.origin.y=rect.origin.y-128+oy;
    }
    else
    {
        rect.origin.y+=oy;
    }
    sp->setTextureRect(rect);
}
void ccUVAction::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
  
    
    
}
bool ccUVAction::isDone()
{
    return false;
}