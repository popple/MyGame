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
struct PPitem
{
    string name;
    string rule;
    int interactive;
    //power 0 直接静止 ＋增加力量 －减少力量
    float power;
    int collision;
    CCPoint *anchorPoint;
    string initFrame;
    vector<PPMovies *> *resource;
};
struct PPMap
{
    string name;
    string desctript;
    int width;
    int height;
    vector<PPitem *> *items;
};

#endif
