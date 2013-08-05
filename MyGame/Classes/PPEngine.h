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
#include "string"
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
    
    CCRect objectRect;
    //判断角色上下方向;
    bool roleDirect;
    //判断物件是否远离角色
    bool direct;
    CCRect rect;
public:
    CCRect screenRect;
    float camOffsetX,camOffsetY;
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
        personX=personY=0;
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
       
        camOffsetX=atof(root["camOffsetX"].asString().c_str());
        camOffsetY=atof(root["camOffsetY"].asString().c_str());
        
        camOffsetX=camOffsetX*screenRect.size.width;
        camOffsetY=camOffsetY*screenRect.size.height;
        //m_mapData->items=new vector<PPitem>;
        JsonCPP::Value views=root["views"];
        JsonCPP::Value items=root["items"];
        JsonCPP::Value backgrounds=root["background"];
        JsonCPP::Value textures=root["textures"];
        
        getTextures(textures);
        m_mapData->views=getViews(views);
        m_mapData->items=getItems(items);
        
        
        procces(true);
    }
    
    void getTextures(JsonCPP::Value value)
    {
        int step;
        int size=value.size();
        for(step=0;step<size;step++)
        {
            JsonCPP::Value item=value[step];
            string path=item["path"].asString();
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("items.plist");
        }
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
            string sframe=item["spriteFrame"].asString();
            image.type=IMAGE;
            
            CCSpriteFrame* frame=getSpriteFrameByName(sframe);
            image.spriteFrame=frame;
            
                       
            for(a=0;a<image.cacheNumber;a++)
            {
                obj=GameObj::create(image.spriteFrame);
                pool->addGameObject(image.getKey(),obj);
            }
            
            
            view.images.insert(pair<string, STImage>(image.name,image));
        }
        return view;
    }
    
    void update(roleX x,roleY y,float &radius,bool &bingo,GameObj* cobj)
    {
        rect.origin.x=x;
        rect.origin.y=y;
        rect.size.width=screenSize.width;
        rect.size.height=screenSize.height;
        bingo=false;
        if(y-personY>0)
        {
            roleDirect=true;
        }
        else
        {
            roleDirect=false;
        }
        personX=x;
        personY=y;
        
        screenRect.origin.x=x-CCDirector::sharedDirector()->getWinSize().width/2;
        screenRect.origin.y=y+CCDirector::sharedDirector()->getWinSize().height/2;
        screenRect.size=CCDirector::sharedDirector()->getWinSize();
        //CCLog("开始装载地图");
        
        CCObject* obj;
        CCNode* object;
        GameObj* role;
        map<string, GameObj*>&objContainer=pool->getMap();
        
        map<string, GameObj*>::iterator it=objContainer.begin();
        
        while(it!=objContainer.end())
        
        {
            role=it->second;
            
            //如果是自己不处理
           
            
            CCPoint t1(role->Objectview->getPositionX(),role->Objectview->getPositionY());
            CCPoint t2(x,y);
            
            float tx=powf((t1.x-t2.x), 2);
            float ty=powf((t1.y-t2.y),2);
            int dis=abs(int(ceil(sqrt(tx+ty))));
            
            //如果目标正在远离角色，且大于一定范围则释放对象。
            direct=dis-role->getInstance() >0;
            //CCSize scz=role->getContentSize();
            if(dis>1000)
            {
                role->setIdle(true);
                
                //role->setVisible(false);
                
                CCLog("物体被释放");
            }
            role->setInstance(dis);
            
            
            
            
            if(dis<role->collision&&role->isInteractive==true)
            {
                //命中目标
                bingo=true;
                cobj=role;
                radius=(x-role->getPositionX())/role->collision*90*3.14/180;
                if(radius<0)radius=-radius;
                CCLog("碰撞角度%f___%d",radius,role->getTag());
                role->play("idle", true);
                //role->setVisible(false);
               // CCLog("物体被命中");
            }
           //-----------------从这里继续开始....
            it++;
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
        CCLog("role direct%b",roleDirect);
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
            int saveY=ceil((screenSize.height*.7+item.layout.height)/h);
            
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
                    if(roleDirect)
                    {
                        a=rand()%(stopX-startX)+startX;
                        getPosition(a,stopY,px,py,item);
                    }
                    else
                    {
                        a=rand()%(stopX-startX)+startX;
                        getPosition(a,startY,px,py,item);
                    }

                    a=rand()%(stopY-startY)+startY;
                    getPosition(stopX,a,px,py,item);

                }
            }
        }
    };
    void getPosition(int x,int y,int bx,int by,PPitem& item)
    {

        Token result;

        
        string key=CCString::createWithFormat("%d_%d_%d_%d",x,y,bx,by)->getCString();
        
      
       
        bool rex=CalcExpr(item.layout.rule, x, y, result)&&result.value.b;
        if(rex)
        {
            GameObj* obj=pool->getUnitByKey(key, item.getKey());
            if(obj)
            {
                if(obj->Objectview->getParent()!=container)
                {
                    container->addChild(obj->Objectview);
                }
               
                obj->Objectview->setPosition(ccp(x*item.width, y*item.height));
                obj->collision=item.logic.collision;
                obj->isInteractive=item.logic.isInteractive;
                obj->power=item.logic.power;
            }
            
                       
        }
                
    }
};

#endif
