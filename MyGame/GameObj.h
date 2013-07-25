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
USING_NS_CC;
using namespace spine;
using namespace std;


class GameObj:public CCNode
{
public:
    float width,height;
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
    
    
    bool getIdle();
    float getInstance();
    void setInstance(float value);
    float getCollision();
    bool getInteractive();
    void setInteractive(bool value);
    
    bool init();
protected:
    CCSprite* mSprite;
    CCRoleView* mRole;
    CCSkeletonAnimation* mSkeletonRole;
    
    CCSpriteFrame* mSpriteData;
    CCDictionary* mRoleViewData;
    string mSkeltonName;
    bool mIdle;
    float mCollision;
    bool mInteractive;
    EViewType mType;
private:
    float _instance;
};

#endif
