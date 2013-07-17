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
        JsonCPP::Value items=root["items"];
        JsonCPP::Value grounds=root["background"];
        JsonCPP::Value viewProtos=root["views"];
        
        int a,len=items.size();
        
        
        
        JsonCPP::Value tmp;
        
        
        len=viewProtos.size();
        for(a=0;a<len;a++)
        {
            tmp=viewProtos[a];
            string name=tmp["name"].asString();
            (&m_mapData->viewProto)->insert(make_pair(name, getProtos(tmp)));
        }
        
        
        
        for(a=0;a<len;a++)
        {
            tmp=items[a];
            m_mapData->items.push_back(getData(tmp));
        }
        
        len=grounds.size();
        for(a=0;a<len;a++)
        {
            tmp=grounds[a];
            m_mapData->background.push_back(getData(tmp));
        }
        
        
        procces(true);
    }
    PPViewProto getProtos(JsonCPP::Value value)
    {
        
        PPViewProto vp;
        vp.name=value["name"].asString();
        vp.idle=value["idle"].asString();
        vp.resource=value["resource"].asString();
        vp.type=value["type"].asString();
        vp.width=atof(value["width"].asString().c_str());
        vp.height=atof(value["height"].asString().c_str());
        vp.buildNum=value["buildNum"].asUInt();
        vp.anchorX=atof(value["anchorX"].asString().c_str());
        vp.anchorY=atof(value["anchorY"].asString().c_str());
        return vp;
    }
    PPitem getData(JsonCPP::Value& tmp)
    {
        
        PPitem item;
        
        JsonCPP::Value jlayout=tmp["layout"];
        JsonCPP::Value jlogic=tmp["logic"];
        
       // PPView& view=item.view;
        
        PPLayout& layout=item.layout;
        PPLogic& logic=item.logic;
        
        item.viewType=tmp["viewType"].asString();
        item.name=tmp["name"].asString();
        item.isGround=tmp["isGround"].asBool();
        
        
        map<string, PPViewProto>::iterator it;
        it=m_mapData->viewProto.find(item.viewType);
        item.viewProto=&it->second;
        
        layout.condition=jlayout["condition"].asString();
        layout.rule =jlayout["rule"].asString();
        layout.width=atof(jlayout["width"].asString().c_str());
        layout.height=atof(jlayout["height"].asString().c_str());
        layout.depth=atof(jlayout["depth"].asString().c_str());
        layout.verticleZ=atof(jlayout["verticleZ"].asString().c_str());
        // getVALUE(item.layout,layout,"widht","int");
        logic.isInteractive=jlogic["interactive"].asBool();
        logic.collision=jlogic["collision"].asInt();
        logic.power=atof(jlogic["power"].asString().c_str());
        
        
        return item;
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
                role->setVisible(false);
                
                //CCLog("物体被消灭");
            }
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
        
        map<string, PPViewProto>::iterator it;
        for(n=0;n<len;n++)
        {
            PPitem &item=m_mapData->items[n];
            it=m_mapData->viewProto.find(item.viewType);
            PPViewProto &viewPro=it->second ;
            int w=viewPro.width;
            int h=viewPro.height;
            
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

        bool rex=CalcExpr(item.layout.rule, x, y, result)&&result.value.b;
        if(rex)
        {
            string key=CCString::createWithFormat("%d_%d_%d_%d_%d_%d",item.viewProto->width,item.viewProto->height,bx,by,x,y)->getCString();
            CCLog("%s",key.c_str());
        }
                
    }
};

#endif
