//
//  SpringObject.h
//  MyGame
//
//  Created by popplecui on 6/26/13.
//
//

#ifndef MyGame_SpringObject_h
#define MyGame_SpringObject_h
#include "CCSkeletonAnimation.h"
#include "cocos2d.h"


class SpringObject:public CCNode
{
private:
    int _power;
    int _dir;
    float _t;
    float _tida;
    float _radius;
    float _g;
    float _xPower;
    float _yPower;
    
public:
    float x,y;
    SpringObject():_tida(.2),_t(0),_g(.098),_dir(1),x(0),y(0)
    {
        
    }
    bool init()
    {
        
        return true;
    }
    void setPower(int power)
    {
        _power=power;
        _xPower=_power*cos(_radius);
        _yPower=_power*sin(_radius);
    }
    void setRadius(float radius)
    {
        _radius=radius*3.14/180;
        _xPower=_power*cos(_radius);
        _yPower=_power*sin(_radius);
    }
    void start()
    {
        this->schedule(schedule_selector(SpringObject::update),60/1000);
    }
    void update()
    {
        
        y=_dir*_yPower*_t-_g*_t*_t/2;
        x=_xPower;
        
        
        
        _t+=_tida;
    }
    CREATE_FUNC(SpringObject);
};

#endif
