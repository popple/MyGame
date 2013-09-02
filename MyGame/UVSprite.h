//
//  UVSprite.h
//  MyGame
//
//  Created by popplecui on 8/26/13.
//
//

#ifndef MyGame_UVSprite_h
#define MyGame_UVSprite_h
#include "cocos2d.h"
USING_NS_CC;
class UVSprite:public CCSprite
{
public:
    virtual void setTextureCoords(CCRect rect);
   

static UVSprite* create(const char *pszFileName);
static UVSprite* createWithTexture(CCTexture2D *pTexture);
};

#endif
