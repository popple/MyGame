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
struct PPView
{
    string type;
    string init;
    string resource;
    float anchorX;
    float anchorY;
    float width;
    float height;
    float verticleZ;
    float depth;
};
struct PPLayout
{
    string rule;
    string condition;

    
    float width;
    float height;
    
    float layoutWidth;
    float layoutHeight;
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
    PPView view;
    PPLayout layout;
    PPLogic logic;
    
};
struct PPMap
{
    string name;
    string desctript;
    int width;
    int height;
    vector<PPitem> items;
    vector<PPitem>  ground;
};

#endif
