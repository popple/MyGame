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
GameObj::GameObj(CCArray*data):mRole(NULL),mSkeletonRole(NULL),mSprite(NULL)
{
    if(mSprite==NULL)
    {
        mType=1;
        mSpriteData=data;
        
        mSprite=CCSprite::createWithSpriteFrame((CCSpriteFrame*)data->objectAtIndex(0));
        this->addChild(mSprite);
    }
}
GameObj::GameObj(CCDictionary* data):mRole(NULL),mSkeletonRole(NULL),mSprite(NULL)
{
    if(mRole==NULL)
    {
        mType=2;
        mRoleViewData=data;
        mRole=CCRoleView::create();
        this->addChild(mRole);
        CCDictElement* ele;
        
        CCDICT_FOREACH(mRoleViewData, ele)
        {
            mRole->addMovie(ele->getStrKey(), (CCArray*)ele->getObject());
        }
        
    }
}
GameObj::GameObj(string fname):mRole(NULL),mSkeletonRole(NULL),mSprite(NULL)
{
    if(mSkeletonRole==NULL)
    {
        mType=3;
        CCString* tem=CCString::createWithFormat("%s.json",fname.c_str());
        CCString* tem1=CCString::createWithFormat("%s.altlas",fname.c_str());
        mSkeletonRole=CCSkeletonAnimation::createWithFile(tem->getCString(),tem1->getCString());
        this->addChild(mSkeletonRole);
    }
       
}

GameObj* GameObj::create(CCArray* data)
{
    return NULL;
}
GameObj* GameObj::create(CCDictionary*data)
{
    return NULL;
}
GameObj* GameObj::create(string fname)
{
    return NULL;
}
void GameObj::init(int frame)
{
    CCSpriteFrame* tem=(CCSpriteFrame*)mSpriteData->objectAtIndex(frame);
    if(tem!=NULL)
    mSprite->initWithSpriteFrame(tem);
}
void GameObj::init(string name,bool repeat)
{
    if(mType==2)
    {
        mRole->playMovie(name);
    }
    else if(mType==3)
    {
        mSkeletonRole->setAnimation(name.c_str(),repeat);
    }
}
void GameObj::setIdle(bool value)
{

}
void GameObj::play(string name,bool repeat)
{
    
}
void GameObj::gotoAndStop(int frame)
{
    
}