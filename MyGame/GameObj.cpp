//
//  GameObj.cpp
//  MyGame
//
//  Created by popplecui on 7/3/13.
//
//

//class MyClass
//{
//public:
//    void* operator new(unsigned long size)
//    {
//        void* ret = ::new(size);
//        memset(ret , 0 , size);
//        return ret;
//    }
//};

#include "GameObj.h"
GameObj::GameObj(CCSpriteFrame*frame):mSpriteData(NULL),mSkeletonRole(NULL),mSprite(NULL),mIdle(true)
{
    if(mSprite==NULL)
    {
        mType=IMAGE;
        mSpriteData=frame;
        frame->retain();
        
    }
}
bool GameObj::getIdle()
{
    return mIdle;
}
int GameObj::getType()
{
    return mType;
}
float GameObj::getInstance()
{
    return _instance;
}
void GameObj::setInstance(float value)
{
    _instance=value;
}
float GameObj::getCollision()
{
    return mCollision;
}
void GameObj::setType(EViewType value)
{
    mType=value;
}
bool GameObj::getInteractive()
{
    return mInteractive;
}
GameObj::GameObj(CCDictionary* data):mSpriteData(NULL),mSkeletonRole(NULL),mSprite(NULL),mIdle(true)
{
    if(mRole==NULL)
    {
        mType=ROLEVIEW;
        data->retain();
        mRoleViewData=data;
                
    }
}
bool GameObj::init()
{
    switch (mType)
    {
        case IMAGE:
        {
            mSprite=CCSprite::createWithSpriteFrame(mSpriteData);
            this->addChild(mSprite);
            width=mSprite->getContentSize().width;
            height=mSprite->getContentSize().height;
            break;
        }
        case ROLEVIEW:
        {
            mRole=CCRoleView::create();
            this->addChild(mRole);
            CCDictElement* ele;
            
            CCDICT_FOREACH(mRoleViewData, ele)
            {
                mRole->addMovie(ele->getStrKey(), (CCArray*)ele->getObject());
            }

            break;
        }
        case SKELTON:
        {
            CCString* tem=CCString::createWithFormat("%s.json",mSkeltonName.c_str());
            CCString* tem1=CCString::createWithFormat("%s.atlas",mSkeltonName.c_str());
            mSkeletonRole=CCSkeletonAnimation::createWithFile(tem->getCString(),tem1->getCString());
            
            width=mSkeletonRole->getContentSize().width;
            height=mSkeletonRole->getContentSize().height;
            this->addChild(mSkeletonRole);
            break;
        }
    }

    return true;
}
GameObj::GameObj(string fname):mSpriteData(NULL),mSkeletonRole(NULL),mSprite(NULL),mIdle(true)
{
    if(mSkeletonRole==NULL)
    {
        mType=SKELTON;
        mSkeltonName=fname;
    }
       
}

GameObj* GameObj::create(CCSpriteFrame* frame)
{
    CCAssert(frame==NULL, "无效的CCSpriteFrame");
    GameObj* obj=new GameObj(frame);
    if(obj&&obj->init())
    {
        obj->autorelease();
        return obj;
    }
    return NULL;
}
GameObj* GameObj::create(CCDictionary*data)
{
    CCAssert(data!=NULL, "无效的RoleView初始化动画数据");
    GameObj* obj=new GameObj(data);
    if(obj&&obj->init())
    {
        obj->autorelease();
        return obj;
    }
    return NULL;

}
GameObj* GameObj::create(string fname)
{
    CCAssert(fname.length()!=0, "无效的骨骼文件名");
    GameObj* obj=new GameObj(fname);
    if(obj&&obj->init())
    {
        obj->autorelease();
        return obj;
    }
    return NULL;

}

void GameObj::setIdle(bool value)
{
    mIdle=value;
    
}
void GameObj::play(string name,bool repeat)
{
    
}
void GameObj::gotoAndStop(int frame)
{
    
}