#include "RoleView.h"
#include "tools.h"

CCRoleCache* CCRoleCache::_instance = NULL;

CCRoleView::CCRoleView():ani(NULL),m_speed(30.0f/1000)
{
	m_cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	m_rep=CCRepeatForever::create(CCActionInterval::create(.1f));
	m_rep->retain();
};
CCRoleView::~CCRoleView()
{

};

void CCRoleView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

};

void CCRoleView::ccTouchEnded(CCTouch* touch, CCEvent* event){};
void CCRoleView::onEnter()
{
	CCSprite::onEnter();
	
	
};


bool CCRoleView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	
	//this->setPosition(touch->getLocation());
	return true;
}

void CCRoleView::addMovie(std::string name,CCArray* spriteFrames)
{
    std::map<std::string,CCAnimate*> ::iterator tmp=m_map.find(name);
	
	if(tmp==m_map.end())
	{
		CCAnimation *ani=CCAnimation::createWithSpriteFrames(spriteFrames,m_speed);
		CCAnimate *amt=CCAnimate::create(ani);
        
		amt->retain();
		
		m_map.insert(std::map<std::string,CCAnimate*> :: value_type(name,amt));
	}
};
void CCRoleView::playMovie(std::string name,bool repeat)
{
	std::map<std::string,CCAnimate*> ::iterator it=m_map.find(name);
	
	if(it!=m_map.end())
	{
		m_currentMovie=name;
		
		
		m_rep->initWithAction(it->second);
		this->stopAction(m_rep);
		this->runAction(m_rep);
	}
	
};

void CCRoleView::setSpeed(float delay)
{
	m_speed=delay;
	std::map<std::string,CCAnimate*> ::iterator it=m_map.find(m_currentMovie);
	if(it!=m_map.end())
	{
		it->second->update(m_speed);
	}
};

bool CCRoleView::init()
{
	if(CCSprite::init())
	{

		return true;
	}
	return false;
};


CCRoleCache::CCRoleCache():m_cache(NULL)
{

};
CCRoleCache::~CCRoleCache(){};
void CCRoleCache::initWithNum(int num)
{
	m_cache=CCArray::createWithCapacity(num);
	
	m_cache->retain();
};
void CCRoleCache::addRoleView(CCRoleView* role)
{
	if(m_cache)
	{
		m_cache->addObject(role);
	}
}
CCRoleCache* CCRoleCache::getInstance()
{
	if(_instance==NULL)
	{
		_instance=new CCRoleCache();
		if(_instance&&_instance->init())
		{
	        _instance->autorelease();
			_instance->retain();
		}
		else
		{
			delete _instance;
			return NULL;
		}
	}
	return _instance;
};

bool CCRoleCache::init(){return true;};
CCRoleView* CCRoleCache::getRole()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_cache,obj)
	{
		CCRoleView*tmp=(CCRoleView*)(obj);
		if(tmp->getIdle())
		{
			//tmp->setIdle(false);
			return tmp;
		}
	}
	return NULL;
};