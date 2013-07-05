//
//  PPAutoPool.h
//  MyTest
//
//  Created by popplecui on 5/23/13.
//
//

#ifndef MyTest_PPUnitPool_h
#define MyTest_PPUnitPool_h
#include "cocos2d.h"
#include "string.h"
#include "PPMapData.h"
#include "CCInteractiveObj.h"
USING_NS_CC;
using namespace std;



class PPUnitPool:public CCObject
{
public:
    PPUnitPool():total(250){};
    ~PPUnitPool(){};
    int total;
    //按坐标给出显示对象，如果对象已存在则忽略本次请求
    CCInteractiveObj *getUnitByKey(string key)
    {
        int a;
        CCInteractiveObj* tmp;
        
        //如果对象已经存在于字典，则直接返回...
        
        if(m_map->objectForKey(key))
        {
            return NULL;
        }
        
        //清除字典中已经死去的对象--------------.
        CCDictElement* oe;
        CCInteractiveObj*rv;
        
        
        //        int m=0;
        //        for(a=0;a<total;a++)
        //        {
        //            tmp=(CCRoleView*)(m_objects->objectAtIndex(a));
        //            if(tmp&&tmp->isIdle==false)
        //            {
        //                m++;
        //
        //            }
        //        }
        //CCLog("%f__%d",m/total,m);
        
        CCDICT_FOREACH(m_map,oe)
        {
            rv=(CCInteractiveObj*)(oe->getObject());
            if(rv->getIdle())
            {
                m_map->removeObjectForKey(oe->getStrKey());
            }
            
        }
        
        //寻找对象池中处于闲散状态的对象，并初始化输出。。
        
        for(a=0;a<total;a++)
        {
            tmp=(CCInteractiveObj*)(m_objects->objectAtIndex(a));
            if(tmp&&tmp->getIdle())
            {
                
                m_map->setObject(tmp,key);
                tmp->setIdle(false);
                return tmp;
            }
        }
        
        
        
        return NULL;
    };
    bool init()
    {
        m_map=CCDictionary::create();
        m_map->retain();
        m_objects=CCArray::createWithCapacity(total);
        m_objects->retain();
        
        int a;CCInteractiveObj*tmp;
        for(a=0;a<total;a++)
        {
            tmp=CCRoleView::create();
            
            tmp->setIdle(true);
            
            m_objects->addObject(tmp);
        }
        return true;
    }
    CREATE_FUNC(PPUnitPool);
protected:
    CCDictionary * m_map;
    CCArray* m_objects;
    
};


#endif