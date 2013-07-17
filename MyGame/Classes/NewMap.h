//
//  NewMap.h
//  MyTest
//
//  Created by popplecui on 6/5/13.
//
//

#ifndef MyTest_NewMap_h
#define MyTest_NewMap_h

struct PPMovies
{
    string name;
    string rule;
    int from;
    int to;
    
};
struct PPViewProto
{
    string name;
    string type;
    string idle;
    string resource;
    float anchorX;
    float anchorY;
    float width;
    float height;
    unsigned int buildNum;
};

struct PPLayout
{
    string rule;
    string condition;

    
    float width;
    float height;
    
    float layoutWidth;
    float layoutHeight;
    
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
    string viewType;
    PPViewProto *viewProto;
    PPLayout layout;
    PPLogic logic;
    
};
struct PPMap
{
    string name;
    string desctript;
    int width;
    int height;
    
    map<string, PPViewProto> viewProto;
    vector<PPitem> items;
    vector<PPitem>  background;
};

#endif
