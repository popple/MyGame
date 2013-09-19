//
//  MyTestAppDelegate.cpp
//  MyTest
//
//  Created by popplecui on 5/21/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "CCBReader.h"
#include "CCNodeLoaderLibrary.h"
#include "MainScene.h"

#include "MainSceneLoader.h"
USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;
AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136,640, kResolutionFixedWidth);
       // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();
    
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLoader::loader());
    
    CCBReader* cb=new CCBReader(ccNodeLoaderLibrary);
    cb->autorelease();
    cb->retain();
    pScene=cb->createSceneWithNodeGraphFromFile("MainScene.ccbi");
    pScene->retain();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
