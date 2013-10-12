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

#include "CCSkeletonAnimation.h"
#include "MyGame.h"
#include "GameObj.h"
USING_NS_CC;
using namespace std;



class PPUnitPool:public CCObject
{
public:
    PPUnitPool()
    {
        
    };
    ~PPUnitPool(){};
    
    //按坐标给出显示对象，如果对象已存在则忽略本次请求
    GameObj *getUnitByKey(string key,TypeKey typeKey)
    {
        int a;
        GameObj* tmp;
        
        map<string, GameObj*>::iterator it;
        
       
        //如果对象已经存在于字典，则直接返回...
        it=(&m_map)->find(key);
        if(it!=(&m_map)->end())
        {
            //CCLog("请求key:%s存在",key.c_str());
            return NULL;
        }
        
        
        //清除字典中已经死去的对象--------------.
       
      
        it=(&m_map)->begin();


        for(;it!=(&m_map)->end();)
        {
            if((it->second)->getIdle())
                
            {
                //满足删除条件，删除当前结点，并指向下面一个结点
                (&m_map)->erase(it++);
            }
            else
            {
                //条件不满足，指向下面一个结点
                it++;
            }
        }
        //CCLog("%f__%d",m/total,m);
                
        //寻找对象池中处于闲散状态的对象，并初始化输出。。
        map<TypeKey,vector<GameObj*> >::iterator itObj;
        itObj=objectMap.find(typeKey);
        
        vector<GameObj*> cache=itObj->second;
        
        
        
        for(a=0;a<cache.size();a++)
        {
            tmp= cache.at(a);
            if(tmp&&tmp->getIdle())
            {
                
                (&m_map)->insert(make_pair(key,tmp));
                
                tmp->setIdle(false);
                //CCLog("返回key%s",key.c_str());
                return tmp;
            }
            //CCLog("%s",typeKey.name.c_str());
        }
        return NULL;
    };
    bool init()
    {
        
        return true;
    }
    void addGameObject(TypeKey key,GameObj*obj)
    {
        if(obj)
        {
            
            map<TypeKey,vector<GameObj*> >::iterator itObj;
            itObj=objectMap.find(key);
            if(itObj!=objectMap.end())
            {
                obj->retain();
                itObj->second.push_back(obj);
            }
            else
            {
                vector<GameObj*> container;
                obj->retain();
                container.push_back(obj);
                objectMap.insert(make_pair(key,container));
                
                
            }
            
        }
        //itObj->second.push_back(obj);
    }
    map<string,GameObj*>& getMap()
    {
        return m_map;
    }
    CREATE_FUNC(PPUnitPool);
protected:
    map<string, GameObj*>  m_map;
    
    map<TypeKey,vector<GameObj*> >objectMap;
};


#endif