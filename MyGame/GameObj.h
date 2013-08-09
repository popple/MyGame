//
//  GameObj.h
//  MyGame
//
//  Created by popplecui on 7/3/13.
//
//

#ifndef MyGame_GameObj_h
#define MyGame_GameObj_h
#include "cocos2d.h"
#include "vector"
#include "map"
#include "RoleView.h"
#include "spine-cocos2dx.h"
#include "MyGame.h"
#include "AnimationEventListener.h"
USING_NS_CC;
using namespace spine;
using namespace std;


class GameObj:public CCNode
{
public:
    float collision;
    float width,height;
    bool isInteractive;
    bool isActive;
    float power;
    CCNode* Objectview;
    GameObj(CCSpriteFrame* spriteFrame);
    GameObj(CCDictionary* movies);
    GameObj(string spineFile);

    static GameObj* create(CCSpriteFrame* spriteFrame);
    static GameObj* create(CCDictionary* movies);
    static GameObj* create(string spineFile);
    
    void play(string name,bool repeat);
    void gotoAndStop(int frame);
    int getType();
    void setType(EViewType value);
    void setIdle(bool value);
    bool delRole(GameObj*rv);
    
    
    bool getIdle();
    CCRect getRect();
    float getInstance();
    void setInstance(float value);
    
    void setLabel(string value);
    virtual void update(float d);
    void addEventListener(AnimationEventListener* listener);
    bool init();
protected:
    CCSprite* mSprite;
    CCRoleView* mRole;
    CCSkeletonAnimation* mSkeletonRole;
    
    AnimationEventListener* _listener;
    
    CCScheduler*sc;
    CCSpriteFrame* mSpriteData;
    CCDictionary* mRoleViewData;
    string mSkeltonName;
    bool mIdle;
    
    bool mInteractive;
    CCLabelTTF* label;
    EViewType mType;
private:
    float _instance;
};

#endif
