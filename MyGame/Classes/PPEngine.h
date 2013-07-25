//
//  PPEngine.h
//  MyTest
//
//  Created by popplecui on 5/24/13.
//
//

#ifndef MyTest_PPEngine_h
#define MyTest_PPEngine_h

typedef float roleX;
typedef float roleY;
#include "cocos2d.h"
//#include "PPMapData.h"
#include "RoleView.h"
#include "Json.h"
#include "value.h"
#include "reader.h"
#include "writer.h"
#include "PPUnitPool.h"
#include "global.h"
#include "spine-cocos2dx.h"
#include "NewMap.h"
#include "calc_expr.h"
#include "CCInteractiveObj.h"
#include "GameObj.h"
using namespace spine;



//extern bool CalcExpr(const std::string & expr, int a1, int a2, Token & result);

class PPEngine:public CCObject
{
protected:
    //MapData m_mapData;
    PPMap *m_mapData;
    float personX,personY;
    CCSize screenSize;
    CCLayer *container;
    int remDis;
public:
    
    PPEngine()
    {
    };
    ~PPEngine(){};
    
    bool init()
    {
        screenSize=CCDirector::sharedDirector()->getWinSizeInPixels();
        m_mapData=new PPMap;
        pool=PPUnitPool::create();
        pool->retain();
        return true;
    };
    void initWithMapFile(string fname,CCLayer* layer)
    {
        
        this->container=layer;
        
        CCFileUtils*ft=CCFileUtils::sharedFileUtils();
        //
        //const char*  s=ft->fullPathForFilename("test.txt").c_str();
        //CCLog("%s",s);
        unsigned long a=0;
        
        unsigned char* data =ft->getFileData(fname.c_str(), "r",&a);
        
        string k=(char *)data;
        //CCLog("%s",k.c_str());
        
        JsonCPP::Value root;
        //声明Reader对象
        JsonCPP::Reader reader;
        //解析json文档
        
        reader.parse((char*)data,root);
        
        buildStruct1(root);
    };
    void buildStruct1(JsonCPP::Value root)
    {
        
        m_mapData->name=root["name"].asString();
        m_mapData->desctript=root["descript"].asString();
        m_mapData->width=root["width"].asInt();
        m_mapData->height=root["height"].asInt();
        //m_mapData->items=new vector<PPitem>;
        JsonCPP::Value views=root["views"];
        JsonCPP::Value items=root["items"];
        JsonCPP::Value backgrounds=root["background"];
        
        m_mapData->views=getViews(views);
        m_mapData->items=getItems(items);
        
        procces(true);
    }
   
    vector<PPitem> getItems(JsonCPP::Value value)
    {
        int step;
        int size=value.size();
        vector<PPitem> data;
        for(step=0;step<size;step++)
        {
            PPitem ppitem;
            JsonCPP::Value item=value[step];
            
            ppitem.name=item["name"].asString();
            ppitem.isGround=item["isGround"].asBool();
            ppitem.anchorX=atof(item["anchorX"].asString().c_str());
            ppitem.anchorY=atof(item["anchorY"].asString().c_str());
            ppitem.width=item["width"].asUInt();
            ppitem.height=item["height"].asUInt();
            
            ppitem.view=m_mapData->views.findObj(ppitem.name);
            
            JsonCPP::Value layout=item["layout"];
            ppitem.layout.rule=layout["rule"].asString();
            ppitem.layout.condition=layout["condition"].asString();
            ppitem.layout.width=atof(layout["width"].asString().c_str());
            ppitem.layout.height=atof(layout["height"].asString().c_str());
            ppitem.layout.verticleZ=atof(layout["vewticleZ"].asString().c_str());
            ppitem.layout.depth=atof(layout["depth"].asString().c_str());
            
            JsonCPP::Value logic=item["logic"];
            ppitem.logic.collision=logic["collision"].asInt();
            ppitem.logic.isInteractive=logic["isInteractive"].asBool();
            ppitem.logic.power=atof(logic["power"].asString().c_str());
            
            data.push_back(ppitem);
        }
        return data;
    }
    PPViews getViews(JsonCPP::Value value)
    {
        PPViews view;
        JsonCPP::Value skeltons=value["skelton"];
        JsonCPP::Value roleviews=value["roleview"];
        JsonCPP::Value images=value["image"];
        
        int step,a;
        int size=skeltons.size();
        JsonCPP::Value item;
        GameObj*obj;
        
        for(step=0;step<size;step++)
        {
            item=skeltons[step];
            STSkelton skelton;
            skelton.name=item["name"].asString();
            skelton.cacheNumber=item["cacheNumber"].asUInt();
            skelton.resource=item["resource"].asString();
            skelton.type=SKELTON;
            view.skeltons.insert(pair<string, STSkelton>(skelton.name,skelton));
            
            for(a=0;a<skelton.cacheNumber;a++)
            {
                obj=GameObj::create(skelton.resource);
                
                pool->addGameObject(skelton.getKey(), obj);
            }
           
            
            
            
        }
        size=roleviews.size();
        for(step=0;step<size;step++)
        {
            item=roleviews[step];
            STRoleView rolevew;
            rolevew.name=item["name"].asString();
            rolevew.cacheNumber=item["cacheNumber"].asInt();
            rolevew.type=ROLEVIEW;
            
            JsonCPP::Value movies=item["movies"];
            int a;
            int mSize=movies.size();
            
            
            CCArray*mov;
            for(a=0;a<mSize;a++)
            {
                JsonCPP::Value mItem=movies[a];
                PPMovie iMovie;
                iMovie.name=mItem["name"].asString();
                iMovie.rule=mItem["rule"].asString();
                iMovie.from=mItem["from"].asUInt();
                iMovie.to=mItem["to"].asUInt();
                
                mov=getSpriteFrameByBat(iMovie.rule, iMovie.from, iMovie.to);
               
                
                rolevew.movies->setObject(mov, iMovie.name);
               
            }
            
           
            
            for(a=0;a<rolevew.cacheNumber;a++)
            {
                obj=GameObj::create(rolevew.movies);
                
                pool->addGameObject(rolevew.getKey(), obj);
            }
            
                      
            view.roleviews.insert(pair<string, STRoleView>(rolevew.name,rolevew));
            
            
            
           
        }
        
        size=images.size();
        for(step=0;step<size;step++)
        {
            item=images[step];
            STImage image;
            image.name=item["name"].asString();
            image.cacheNumber=item["cacheNumber"].asUInt();
            image.spriteFrame=item["spriteFrame"].asString();
            image.type=IMAGE;
            
          
            
                       
            for(a=0;a<image.cacheNumber;a++)
            {
                obj=GameObj::create(image.spriteFrame);
                pool->addGameObject(image.getKey(),obj);
            }
            
            
            view.images.insert(pair<string, STImage>(image.name,image));
        }
        return view;
    }
    
    void update(roleX x,roleY y,float &radius,bool &bingo)
    {
        personX=x;
        personY=y;
        
        //CCLog("开始装载地图");
        
        CCObject* obj;
        GameObj* role;
        
        CCARRAY_FOREACH(container->getChildren(), obj)
        {
            role=(GameObj*)(obj);
            //如果是自己不处理
            if(role->getType()==1000)
            {
                continue;
            };
            CCPoint t1(role->getPositionX(),role->getPositionY());
            CCPoint t2(x,y);
            
            float tx=powf((t1.x-t2.x), 2);
            float ty=powf((t1.y-t2.y),2);
            int dis=abs(int(ceil(sqrt(tx+ty))));
            CCSize scz=role->getContentSize();
            if(dis-role->getInstance() >0&&dis>(screenSize.width+scz.width))
            {
                role->setIdle(true);
                //role->setVisible(false);
                
                //CCLog("物体被消灭");
            }
            role->setInstance(dis);
            if(dis<role->getCollision()&&role->getInteractive()==true)
            {
                //命中目标
                bingo=true;
               
                radius=(x-role->getPositionX())/role->getCollision()*90*3.14/180;
                if(radius<0)radius=-radius;
                CCLog("碰撞角度%f___%d",radius*180/3.14,role->getTag());
                role->play("idle", true);
                //role->setVisible(false);
               // CCLog("物体被命中");
            }
           //-----------------从这里继续开始....
        }
       // procces(true);
        procces();
    };
    CREATE_FUNC(PPEngine);
protected:
    PPUnitPool* pool;
private:
    
    void procces(bool init=false)
    {
                
        int a,b;
        int n,len=m_mapData->items.size();
        //PPitem item=m_mapData->items;
        
        //map<string, PPViewProto>::iterator it;
        for(n=0;n<len;n++)
        {
            PPitem &item=m_mapData->items[n];
            
            int w=item.width;
            int h=item.height;
            
            //        string type=layer.type;
            //        string name=layer.name;
            //取得目标所在坐标映射空间
            int px=int(personX/w);
            int py=int(personY/h);
            
            //取得最大屏幕覆盖区域
            int saveX=ceil((screenSize.width/2+item.layout.width)/w);
            int saveY=ceil((screenSize.height/2+item.layout.height)/h);
            
            int startX=px-saveX;
            int startY=py-saveY;
            
            int stopX=px+saveX;
            int stopY=py+saveY;

            
           
            if(init)
            {
                for (a=startX; a<=stopX;a++)
                {
                    for(b=startY;b<=stopY;b++)
                    {
                        getPosition(a,b,px,py,item);
                        //CCLOG("%d__%d",a,b);
                    }
                }
            }
            else 
            {
                if(item.isGround)
                {
                    for(a=startY;a<stopY;a++)
                    {
                        getPosition(stopX,a,px,py,item);
                        //CCLog("%d___%d____%s_____坐标扫瞄",a,stopY,name.c_str());
                    }
                    for(a=startX;a<=stopX;a++)
                    {
                        getPosition(a,startY,px,py,item);
    
                    }

                }
                else
                {
                    a=rand()%(stopX-startX)+startX;
                    getPosition(a,stopY,px,py,item);
                    //                //取上方横条
                    //                for(a=startX;a<=stopX;a++)
                    //                {
                    //                    getPosition(a,stopY,&item);
                    //                    //CCLog("%d___%d____%s_____坐标扫瞄",a,stopY,name.c_str());
                    //
                    //                }
                    //取右边竖条
                    a=rand()%(stopY-startY)+startY;
                    getPosition(stopX,a,px,py,item);
                    //                for(a=startY;a<stopY;a++)
                    //                {
                    //                    getPosition(stopX,a,&item);
                    //                    //CCLog("%d___%d____%s_____坐标扫瞄",a,stopY,name.c_str());
                    //                }
                    //取下方横条
                    a=rand()%(stopX-startX)+startX;
                    getPosition(a,startY,px,py,item);
                    //                for(a=startX;a<=stopX;a++)
                    //                {
                    //                    getPosition(a,startY,&item);
                    //                    
                    //                }

                }
            }
        }
    };
    void getPosition(int x,int y,int bx,int by,PPitem& item)
    {

        Token result;

        
        string key=CCString::createWithFormat("%d_%d_%d_%d",bx,by,x,y)->getCString();
        
      
       
        bool rex=CalcExpr(item.layout.rule, x, y, result)&&result.value.b;
        if(true)
        {
            GameObj* obj=pool->getUnitByKey(key, item.getKey());
            
            if(obj)
            {
                if(obj->getParent()!=container)
                {
                    container->addChild(obj);
                }
                obj->setVisible(true);
                obj->setPosition(ccp(x*item.width, y*item.height));
            }
            
                       
        }
                
    }
};

#endif
