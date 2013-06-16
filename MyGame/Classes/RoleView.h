#ifndef __ROLEVIEW_SCENE_H__
#define __ROLEVIEW_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class CCRoleView:public CCSprite,public CCTargetedTouchDelegate
{
public:
	

	CCRoleView();
	~CCRoleView();
    bool isIdle;
    bool isActive;
    int type;
    int uid;
    int dis;
    bool collision;
    int  interactive;
	void addMovie(std::string name,CCArray* spriteFrames);
	void playMovie(std::string name,bool repeat=true);
	void setSpeed(float delay);
	void virtual onEnter();
    
    
	//CC_SYNTHESIZE_RETAIN(CCRoleView*,param,idle);
	
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool init();
	CREATE_FUNC(CCRoleView);
protected:
    std::string m_currentMovie;
	float m_speed;
	CCRepeatForever* m_rep;
	CCSpriteFrameCache *m_cache;
	CCAnimate *ani;
	bool m_isIdle;
	void m_play(std::string name);

	std::map <std::string,CCAnimate*> m_map;
	CC_SYNTHESIZE(bool,param,Idle);

};

class CCRoleCache:public CCObject
{

private :
	static CCRoleCache *_instance;
	
	CCRoleCache();
public:
	~CCRoleCache();
	static CCRoleCache* getInstance();
	void initWithNum(int num);
	void addRoleView(CCRoleView* role);
	CCRoleView* getRole();
	bool init();

protected:
	int m_total;
	CCArray* m_cache;
	
};
#endif