//
//  MainScene.cpp
//  MyGame
//
//  Created by popplecui on 9/16/13.
//
//

#include "MainScene.h"
#include "HelloWorldScene.h"
#include "ccUVAction.h"
MainScene::MainScene()
{
    CCLOG("build");
}
MainScene::~MainScene()
{
    
}
SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "startGame", MainScene::startGame);
    return NULL;
}
void MainScene::startGame()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
void MainScene::about(){}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

bool MainScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "bg", CCSprite *, this->bg);
   
   // CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", CCLabelTTF *, this->mTestTitleLabelTTF);
    return false;
}
bool MainScene::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue){return true;}
void MainScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CCLOG("loaded");
    CCSize v=CCDirector::sharedDirector()->getWinSizeInPixels();
//    CCRect t;
//    t.size=CCSizeMake(600,400);
//    
//   // this->bg->initWithFile("blood.png", t);
//    this->bg->setContentSize(t.size);
//    //this->bg->setAnchorPoint(CCPointMake(0, 0));
//    ccTexParams pm={GL_LINEAR, GL_LINEAR, GL_REPEAT,GL_REPEAT};
//    this->bg->getTexture()->setTexParameters(&pm);
//    
//    
//   // this->bg->setTextureRect(t);
//    ccUVAction* uva=ccUVAction::create(50,50);
//    this->bg->runAction(uva);

    
    
    CCSprite*tt=CCSprite::create("Blood.png");
    tt->retain();
    tt->setAnchorPoint(CCPointMake(0, 0));
    ccTexParams pm={GL_LINEAR, GL_LINEAR, GL_REPEAT,GL_REPEAT};
    tt->getTexture()->setTexParameters(&pm);
    tt->setTextureRect(CCRectMake(0,0,v.width,v.height));
    ccUVAction* uva=ccUVAction::create(100,100);
    tt->runAction(uva);
    this->addChild(tt,-1);
    
}