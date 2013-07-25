//
//  NewMap.h
//  MyTest
//
//  Created by popplecui on 6/5/13.
//
//

#ifndef MyTest_NewMap_h
#define MyTest_NewMap_h

struct PPMovie
{
    string name;
    string rule;
    int from;
    int to;
    
};
struct STObject
{
    string name;
    EViewType type;
    unsigned cacheNumber;
    
    TypeKey getKey()
    {
        TypeKey key;
        key.name=name;
        key.type=type;
        return key;
    }
};
struct STImage:STObject {
    
    string spriteFrame;
    
    
};

struct STSkelton:STObject
{
    
    string resource;
    
};
struct STRoleView:STObject
{
    CCDictionary*movies;
public:
    STRoleView()
    {
        movies=CCDictionary::create();
        movies->retain();
    };
    
    
};
struct PPLayout
{
    string rule;
    string condition;

    
    float width;
    float height;

    
    float verticleZ;
    float depth;
};

struct PPLogic
{
    float collision;
    float power;
    bool isInteractive;
};
struct PPitem
{
    string name;
    bool isGround;
    float anchorX;
    float anchorY;
    float width;
    float height;
    
    PPLayout layout;
    PPLogic logic;
    
    STObject view;
    TypeKey getKey()
    {
        TypeKey key;
        
        key.name=name;
        key.type=view.type;
        return key;
    }
};
struct PPViews
{
    map<string,STImage> images;
    map<string,STSkelton> skeltons;
    map<string,STRoleView> roleviews;
    STObject findObj(string type)
    {
        
        map<string, STImage>::iterator it=images.find(type);
        if(it!=images.end())
        {
            return it->second;
        }
        
        map<string, STRoleView>::iterator it1=roleviews.find(type);
        if(it1!=roleviews.end())
        {
            return it1->second;
        }
        map<string, STSkelton>::iterator it2=skeltons.find(type);
        if(it2!=skeltons.end())
        {
            return it2->second;
        }
    }
};
struct PPMap
{
    string name;
    string desctript;
    int width;
    int height;
    
    
    PPViews views;
    vector<PPitem> items;
    vector<PPitem>  background;
};

#endif
