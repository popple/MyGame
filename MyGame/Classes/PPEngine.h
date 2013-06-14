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
public:
    
    PPEngine(){};
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
        m_mapData->items=new vector<PPitem*>;
        JsonCPP::Value items=root["items"];
        int a,len=items.size();
        for(a=0;a<len;a++)
        {
            PPitem *item=new PPitem;
            JsonCPP::Value tmp=items[a];
            
            item->name=tmp["name"].asString();
            item->rule=tmp["rule"].asString();
            item->interactive=tmp["interactive"].asInt();
            item->collision=tmp["collision"].asInt();
            item->power=tmp["power"].asInt();
            item->depth=tmp["depth"].asInt();
            JsonCPP::Value p=tmp["anchorPoint"];
            item->x=tmp["x"].asString();
            item->y=tmp["y"].asString();
            item->randomZ=tmp["randomZ"].asInt();
            item->anchorPoint=new CCPoint(atof(p["x"].asString().c_str()),atof(p["y"].asString().c_str()));
            
            item->initFrame=tmp["initFrame"].asString();
            item->resource=new vector<PPMovies*>;
            JsonCPP::Value resources=tmp["resource"];
            
            int b,len1=resources.size();
            for(b=0;b<len1;b++)
            {
                PPMovies *mov=new PPMovies;
                JsonCPP::Value jItem=resources[b];
                mov->name=jItem["name"].asString();
                mov->rule=jItem["rule"].asString();
                mov->from=jItem["from"].asInt();
                mov->to=jItem["to"].asInt();
                item->resource->push_back(mov);
            }
            m_mapData->items->push_back(item);
        }
    }
//    void buildStruct(Json::Value root)
//    {
//       
//        m_mapData.name=root["name"].asString();
//        
//        Json::Value data=root["data"];
//        int a,len=root["data"].size();
//        
//        
//        for(a=0;a<len;a++)
//        {
//            Json::Value tmp=data[a];
//            PPLayerData layer;
//            layer.name=tmp["name"].asString();
//            layer.perX=tmp["perX"].asInt();
//            layer.perY=tmp["perY"].asInt();
//            layer.abX=tmp["abX"].asInt();
//            layer.abY=tmp["abY"].asInt();
//            layer.maxPerX=tmp["maxPerX"].asInt();
//            layer.maxPerY=tmp["maxPerY"].asInt();
//            layer.type=tmp["type"].asString();
//            
//            
//            Json::Value PPunits=tmp["data"];
//            
//            Json::Value::Members member_list = PPunits.getMemberNames();
//            Json::Value::Members::iterator it = member_list.begin();
//            for ( Json::Value::Members::iterator it = member_list.begin(); it != member_list.end();++it)
//            {
//                //const std::string &name = *it;
//                Json::Value jsonUnit=PPunits[*it];
//                
//                PPUnit ppUnit;
//                ppUnit.x=jsonUnit["x"].asInt();
//                ppUnit.y=jsonUnit["y"].asInt();
//                ppUnit.type=jsonUnit["type"].asInt();
//                ppUnit.initFrame=jsonUnit["initFrame"].asString();
//                
//                Json::Value movData=jsonUnit["action"];
//                int x,xlen=movData.size();
//                
//                for(x=0;x<xlen;x++)
//                {
//                    Json::Value movUnit=movData[x];
//                    MovieDec movDec;
//                    movDec.name=movUnit["name"].asString();
//                    movDec.rule=movUnit["rule"].asString();
//                    movDec.from=movUnit["from"].asInt();
//                    movDec.to=movUnit["to"].asInt();
//                    ppUnit.actions.push_back(movDec);
//                }
//
//                //CCLog("_____________%s",(string)(*it));
//                layer.data[*it]=ppUnit;
//                //int retInt = strcmp(t.c_str(), "-29_16");
//                //layer.data["-29_16"]=ppUnit;
//                
//                //printValueTree( fout, value[name], path + suffix + name );
//            }
//            m_mapData.data.push_back(layer);
//        }
//                
//    }
    void update(roleX x,roleY y,float &radius,bool &bingo)
    {
        personX=x;
        personY=y;
        
        //CCLog("开始装载地图");
        
        CCObject* obj;
        CCRoleView* role;
        
        CCARRAY_FOREACH(container->getChildren(), obj)
        {
            role=(CCRoleView*)(obj);
            //如果是自己不处理
            if(role->getTag()==1000)
            {
                continue;
            };
            CCPoint t1(role->getPositionX(),role->getPositionY());
            CCPoint t2(x,y);
            
            float tx=powf((t1.x-t2.x), 2);
            float ty=powf((t1.y-t2.y),2);
            int dis=abs(int(ceil(sqrt(tx+ty))));
            
            if(dis>max(screenSize.width, screenSize.height))
            {
                role->isIdle=true;
                role->isActive=false;
                role->setVisible(false);
                
                //CCLog("物体被消灭");
            }
            if(dis<role->collision&&role->interactive==0)
            {
                //命中目标
                bingo=true;
                role->isActive=false;
                radius=(x-role->getPositionX())/role->collision*90*3.14/180;
                if(radius<0)radius=-radius;
                CCLog("碰撞角度%f___%d",radius*180/3.14,role->uid);
                role->playMovie("attack");
                //role->setVisible(false);
               // CCLog("物体被命中");
            }
           //-----------------从这里继续开始....
        }
        
        procces();
    };
    CREATE_FUNC(PPEngine);
protected:
    PPUnitPool* pool;
private:
    
    void procces()
    {
        int w=m_mapData->width;
        int h=m_mapData->height;
        
//        string type=layer.type;
//        string name=layer.name;
        //取得目标所在坐标映射空间
        int px=int(personX/w);
        int py=int(personY/h);
        
        //取得最大屏幕覆盖区域
        int saveX=ceil(screenSize.width/2/w)+2;
        int saveY=ceil(screenSize.height/2/h)+2;
        
        int startX=px-saveX;
        int startY=py-saveY;
        
        int stopX=px+saveX;
        int stopY=py+saveY;
        
        int a;
                //取上方横条
//        for(a=startX;a<=stopX;a++)
//        {
//            getPosition(a,stopY);
//            //CCLog("%d___%d____%s_____坐标扫瞄",a,stopY,name.c_str());
//            
//        }
//        //取右边竖条
//        for(a=startY;a<stopY;a++)
//        {
//            getPosition(stopX,a);
//            //CCLog("%d___%d____%s_____坐标扫瞄",a,stopY,name.c_str());
//            
//        }
//        //取下方横条
//        for(a=startX;a<stopX;a++)
//        {
//            getPosition(a,startY);
//            
//        }
        
        getPosition(px,py);
    };
    void getPosition(int x,int y)
    {
        int a,len=m_mapData->items->size();
        for(a=0;a<len;a++)
        {
            
            PPitem* item= (*m_mapData->items)[a];
            Token resultX;
            Token resultY;
            int rex=CalcExpr(item->x, x, y, resultX);
            int rey=CalcExpr(item->y, x,y, resultY);
            if(!rex||!rey)return;
            
            
            if(true)
            {
                string key=CCString::createWithFormat("%d_%d",x,y)->getCString();
                
                CCRoleView* role=pool->getUnitByKey(key);
                if(role)
                {
                    initView(item,role);
                    role->setPositionX(x*m_mapData->width);
                    role->setPositionY(y*m_mapData->height);
                    role->interactive=item->interactive;
                    role->setAnchorPoint(ccp(item->anchorPoint->x,item->anchorPoint->y));
                    
                    
                    int rnd=rand()%300-rand()%100;
                    if(item->randomZ==1)
                    {
                         role->setVertexZ(rnd);
                         
                    }
                    role->setZOrder(item->depth);
                    if(item->interactive==1)
                    {
                        role->playMovie("stand");
                    }
                    if(role->getParent()!=container)
                    {
                        container->addChild(role);
                    }
                    role->setVisible(true);
                }
            }
            
        }
//        bool conditions=false;
//        
//        conditions=(y==0);
//        //CCLog("%d__%d",x,y);
//        if(conditions)
//        {
//            CCRoleView* role;
//            
//            int sclX=int(x/layer.maxPerX);
//            int sclY=int(y/layer.maxPerY);
//            
//            int tx=x-sclX*layer.maxPerX;
//            int ty=y-sclY*layer.maxPerY;
//            
//            //CCLog("%d______%d",tx,ty);
//            string key=CCString::createWithFormat("%d_%d",tx,ty)->getCString();
//
//            
//            map<string,PPUnit>::iterator it=layer.data.begin();
//            
//            
//            for(it;it!=layer.data.end();it++)
//            {
//                
//                layer.data[*it];
//            }
//            
//            layer.data.find("2_2");
//            
//
//            
//            if(it!=layer.data.end())
//            {
//                
//                
//                int sx=(*it).second.x*sclX;
//                int sy=(*it).second.y*sclY;
//                //找到对应坐标数据
//                role=pool->getUnitByKey(key);
//                if(role)
//                {
//                    role->setPositionX(x*layer.abX);
//                    role->setPositionY(y*layer.abY);
//                    //role->initWithSpriteFrame();
//                    
//                    initView((*it).second,role);
//                    role->setAnchorPoint(CCPointMake(.5f,.258f));
//                    role->isIdle=false;
//                    role->isActive=true;
//                    role->setVisible(true);
//                    role->playMovie("stand");
//                    if(role->getParent()!=container)
//                    {
//                        container->addChild(role);
//                        //role->playMovie("attack");
//                    }
//                    
//                }
//            }
//        }
    }
    CCArray* initView(PPitem *unitP,CCRoleView* role)
    {
        string initfstr=unitP->initFrame;
        CCSpriteFrame* initFrame=getSpriteFrameByName(initfstr.c_str());
        if(initFrame!=NULL)
        role->initWithSpriteFrame(initFrame);
        
        
        string name;string rule;int from;int to;
        
        vector<PPMovies*>::iterator it=unitP->resource->begin();
        
        for(;it!=unitP->resource->end();it++)
        {
            name=(*it)->name;
            rule=(*it)->rule;
            from=(*it)->from;
            to=(*it)->to;
            
            CCArray*frames=getSpriteFrameByBat(rule,from,to);
            role->addMovie(name.c_str(),frames);
            
        }
        
        return NULL;
    }
};

#endif
