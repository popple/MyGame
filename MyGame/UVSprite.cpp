//
//  UVSprite.cpp
//  MyGame
//
//  Created by popplecui on 8/26/13.
//
//

#include "UVSprite.h"
void UVSprite::setTextureCoords(CCRect rect)
{
    rect.origin.x=50;
   // glSampleCoverage(<#GLclampf value#>, <#GLboolean invert#>)
    CCSprite::setTextureCoords(rect);
    //setTextureCoords(CCRectMake(rand()*10, rand()*10, 100, 100));
    
  //  CCTexture2D *t2d;
    //t2d->setTexParameters(<#ccTexParams *texParams#>)
}
UVSprite* UVSprite::createWithTexture(cocos2d::CCTexture2D *pTexture)
{
    UVSprite *pobSprite = new UVSprite();
    
    if (pobSprite && pobSprite->createWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;

}
UVSprite* UVSprite::create(const char *pszFileName)
{
    UVSprite *pobSprite = new UVSprite();
    
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}