//
//  MapData.h
//  MyTest
//
//  Created by popplecui on 5/21/13.
//
//

#ifndef MyTest_MapData_h
#define MyTest_MapData_h
#include "string.h"
#include "vector.h"
#include "map.h"
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

struct MovieDec
{
    string name;
    string rule;
    unsigned from;
    unsigned to;
};
//define position
struct PPUnit
{
    int x,y;
    int type;
    //string->CCArray
    string initFrame;
    vector<MovieDec> actions;
    string getKey()
    {
        CCString *tmp=CCString::createWithFormat("%d_%d_%d",type,x,y);
        return tmp->getCString();
    }
public:
    PPUnit(int x,int y)
    {
        this->x=x;
        this->y=y;              
    };
    PPUnit(){};
};

//define layer 每一层有自己的单元格大小
struct PPLayerData
{
    string name;
    //宽高表示单元格大小
    int perX;
    int perY;
    string type;
    int abX,abY;
    int maxPerX,maxPerY;
    map<string,PPUnit> data;
public:
    PPLayerData(){};
    
    CCSprite *sp;
    
};

//map
struct MapData
{
    string name;
    vector<PPLayerData> data;
public:
    MapData(){};
    MapData(string name,vector<PPLayerData> data)
    {
        this->name=name;
        this->data=data;
    };
};
#endif


