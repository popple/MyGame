//
//  AnimationEventListener.h
//  MyGame
//
//  Created by popplecui on 8/9/13.
//
//

#ifndef MyGame_AnimationEventListener_h
#define MyGame_AnimationEventListener_h
#include "CCSkeletonAnimation.h"
#include "stdcheaders.h"
using namespace std;
class AnimationEventListener
{
public:
    void onPlayEvent(spine::CCSkeletonAnimation *target, string name);
};

#endif
