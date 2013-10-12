//
//  MovieEndAction.cpp
//  MyGame
//
//  Created by popplecui on 8/12/13.
//
//
#include "spine-cocos2dx.h"
#include "MovieEndAction.h"
using namespace spine;

void MovieEndAction::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
};

void MovieEndAction::step(float dt)
{
    CCSkeletonAnimation *st=(CCSkeletonAnimation*)m_pTarget;
    float t=st->states[0]->time;
    float dur=st->states[0]->animation->duration;
    string name=st->states[0]->animation->name;
    if(t>=dur)
    {
        if(strcmp(name.c_str(), m_watch_movies.c_str())==0)
        {
            mIsDone=true;
        }
        else
        {
            mIsDone=false;
        }
    }
};
bool MovieEndAction::isDone()
{
    return false;
}
MovieEndAction::~MovieEndAction(){};
MovieEndAction::MovieEndAction(string movie)
{
    mIsDone=false;
    m_watch_movies=movie;
};
MovieEndAction* MovieEndAction::create(string movie)
{
    return new MovieEndAction(movie);
    
};