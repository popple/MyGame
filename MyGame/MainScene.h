//
//  MainScene.h
//  MyGame
//
//  Created by popplecui on 9/16/13.
//
//

#ifndef MyGame_MainScene_h
#define MyGame_MainScene_h
#include "cocos2d.h"
#include "CCBSelectorResolver.h"
#include "CCBMemberVariableAssigner.h"
#include "CCNodeLoaderListener.h"
#include "CCNodeLoader.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class MainScene:public CCLayer,
                public CCBSelectorResolver,
                public CCBMemberVariableAssigner,
                public CCNodeLoaderListener
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    MainScene();
    virtual ~MainScene();
    
    
        
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    void startGame();
    void about();
private:
    CCSprite* bg;
};

#endif
