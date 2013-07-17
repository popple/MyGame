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
#include "CCSkeletonAnimation.h"
#include "MyGame.h"

USING_NS_CC;
using namespace std;



class PPUnitPool:public CCObject
{
public:
    PPUnitPool():total(250){};
    ~PPUnitPool(){};
    int total;
    //按坐标给出显示对象，如果对象已存在则忽略本次请求
    CCInteractiveObj *getUnitByKey(string key,TypeKey typeKey)
    {
        int a;
        CCInteractiveObj* tmp;
        
        map<string, CCInteractiveObj*>::iterator it;
        
       
        //如果对象已经存在于字典，则直接返回...
        it=(&m_map)->find(key);
        if(it==(&m_map)->end())
        {
            return NULL;
        }
        
        
        //清除字典中已经死去的对象--------------.
       
        CCInteractiveObj*rv;
        
        

        //CCLog("%f__%d",m/total,m);
        it=(&m_map)->begin();
        while(it!=(&m_map)->end())
        {
            rv=it->second;
            if(rv->getIdle())
            {
                (&m_map)->erase(it);
            }
        }
        
        //寻找对象池中处于闲散状态的对象，并初始化输出。。
        map<TypeKey,vector<CCInteractiveObj*> *>::iterator itObj;
        itObj=(&objectMap)->find(typeKey);
        
        vector<CCInteractiveObj*>* cache=itObj->second;
        
        
        bool isFind=false;
        for(a=0;a<cache->size();a++)
        {
            CCInteractiveObj* tem= cache->at(a);
            if(tem&&tem->getIdle())
            {
                
                (&m_map)->insert(make_pair(typeKey.name,tmp));
                tmp->setIdle(false);
                isFind=true;
                return tmp;
            }
        }
        if(!isFind)
        {
            switch (typeKey.type)
            {
                case IMAGE:
                    
                    break;
                    
                case SKELTON:
                    break;
            }
        }
        return NULL;
    };
    bool init()
    {
        
        return true;
    }
    CREATE_FUNC(PPUnitPool);
protected:
    map<string, CCInteractiveObj*>  m_map;
    
    map<TypeKey,vector<CCInteractiveObj*> *>objectMap;
};


#endif