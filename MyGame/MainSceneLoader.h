//
//  MainSceneLoader.h
//  MyGame
//
//  Created by popplecui on 9/16/13.
//
//

#ifndef __MyGame__MainSceneLoader__
#define __MyGame__MainSceneLoader__

#include <iostream>
#include"cocos2d.h"
#include "CCLayerLoader.h"
using namespace cocos2d;
using namespace cocos2d::extension;


class MainSceneLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};
#endif /* defined(__MyGame__MainSceneLoader__) */
