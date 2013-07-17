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
USING_NS_CC;
using namespace spine;
using namespace std;

class GameObj:public CCNode
{
public:
    GameObj(CCArray*);
    GameObj(CCDictionary*);
    GameObj(string fname);

    static GameObj* create(CCArray*);
    static GameObj* create(CCDictionary*);
    static GameObj* create(string fname);
    void init(int frame);
    void init(string name,bool repeat);
    void play(string name,bool repeat);
    void gotoAndStop(int frame);
    int getType();
    void setType(int value);
    void setIdle(bool value);
    
    
    bool getIdle();
    float getInstance();
    float getCollision();
    bool getInteractive();
protected:
    CCSprite* mSprite;
    CCRoleView* mRole;
    CCSkeletonAnimation* mSkeletonRole;
    
    CCArray* mSpriteData;
    CCDictionary* mRoleViewData;
    string mJsonName;
    bool mIdle;
    float mCollision;
    
    int mType;
};

#endif
